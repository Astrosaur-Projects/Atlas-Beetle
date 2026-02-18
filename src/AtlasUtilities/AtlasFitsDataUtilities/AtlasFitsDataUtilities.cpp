#include "AtlasUtilities/AtlasFitsDataUtilities/AtlasFitsDataUtilities.h"
#include <cfitsio/fitsio.h>
#include <cfitsio/longnam.h>
#include <expected>
#include <format>
#include <string>
#include <vector>

std::expected<AtlasFitsDataUtilities::MemorySafeFitsFile, std::string> AtlasFitsDataUtilities::open(std::string path)
{
	fitsfile* filePointer = nullptr;

	int resultCode = 0;

	fits_open_file(&filePointer, path.c_str(), READONLY, &resultCode);

	if (resultCode) {
		char description[FLEN_ERRMSG];

		fits_read_errmsg(description);

		std::string error = std::format("Error opening fits file {}: {} (Code: {})", path, description, resultCode);

		return std::unexpected<std::string>(error);
	}

	return AtlasFitsDataUtilities::MemorySafeFitsFile(filePointer);
}

std::expected<bool, std::string> AtlasFitsDataUtilities::moveToHeaderDataUnit(fitsfile* file, int index)
{
	int status = 0;

	fits_movabs_hdu(file, index, nullptr, &status);

	if (status) {
		char description[FLEN_ERRMSG];

		fits_read_errmsg(description);

		std::string error = std::format("Error moving to header data unit {}: {} (Code: {})", index, description, status);

		return std::unexpected<std::string>(error);
	}

	return true;
}

std::expected<bool, std::string> AtlasFitsDataUtilities::getRowCount(fitsfile* file, long& count)
{
	int status = 0;

	fits_get_num_rows(file, &count, &status);

	if (status) {
		char description[FLEN_ERRMSG];

		fits_read_errmsg(description);

		std::string error = std::format("Error getting count of rows: {} (Code: {})", description, status);

		return std::unexpected<std::string>(error);
	}

	return true;
}

std::expected<bool, std::string> AtlasFitsDataUtilities::getColumnCount(fitsfile* file, int& count)
{
	int status = 0;

	fits_get_num_cols(file, &count, &status);

	if (status) {
		char description[FLEN_ERRMSG];

		fits_read_errmsg(description);

		std::string error = std::format("Error getting count of columns: {} (Code: {})", description, status);

		return std::unexpected<std::string>(error);
	}

	return true;
}

std::expected<bool, std::string> AtlasFitsDataUtilities::getColumnIndex(fitsfile* file, std::string column, int& index)
{
	int status = 0;

	char* columnPointer = column.data();

	fits_get_colnum(file, CASEINSEN, columnPointer, &index, &status);

	if (status) {
		char description[FLEN_ERRMSG];

		fits_read_errmsg(description);

		std::string error = std::format("Error getting index of column {}: {} (Code: {})", column, description, status);

		return std::unexpected<std::string>(error);
	}

	return index;
}

std::expected<bool, std::string> AtlasFitsDataUtilities::getColumnWidth(fitsfile* file, int column, int& width)
{
	int status = 0;

	fits_get_col_display_width(file, column, &width, &status);

	if (status) {
		char description[FLEN_ERRMSG];

		fits_read_errmsg(description);

		std::string error = std::format("Error getting width of column {}: {} (Code: {})", column, description, status);

		return std::unexpected<std::string>(error);
	}

	return true;
}

std::expected<bool, std::string> AtlasFitsDataUtilities::loadColumnIntoBuffer(fitsfile* file, int column, long start, long size, std::vector<std::string>& buffer, std::string defaultValue)
{
	int status = 0;

	int width = 0;

	std::expected<bool, std::string> widthResult = AtlasFitsDataUtilities::getColumnWidth(file, column, width);

	if (!widthResult.has_value()) {
		return widthResult;
	}

	std::vector<char> dataBlock(size * (width + 1));

	std::vector<char*> pointersBuffer(size);

	for (int i = 0; i < size; i++) {
		int pointerIndex = i * (width + 1);
		pointersBuffer[i] = &dataBlock[pointerIndex];
	}

	fits_read_col_str(file, column, start, 1, size, defaultValue.data(), pointersBuffer.data(), nullptr, &status);

	if (status) {
		char description[FLEN_ERRMSG];

		fits_read_errmsg(description);

		std::string error = std::format("Error loading column into string buffer: {} (Code: {})", description, status);

		return std::unexpected<std::string>(error);
	}

	buffer.clear();

	buffer.reserve(size);

	for (int i = 0; i < size; i++) {
		buffer.push_back(std::string(pointersBuffer[i]));
	}

	return true;
}
