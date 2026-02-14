#include "AtlasUtilities/AtlasFitsDataUtilities/AtlasFitsDataUtilities.h"
#include <expected>
#include <fitsio.h>
#include <format>
#include <longnam.h>
#include <string>
#include <vector>

std::expected<AtlasFitsDataUtilities::MemorySafeFitsFile, std::string> AtlasFitsDataUtilities::open(std::string path)
{
	fitsfile* filePointer = nullptr;

	int resultCode = 0;

	fits_open_file(&filePointer, path.c_str(), READONLY, &resultCode);

	if (resultCode) {
		char fitsErrorMessage[FLEN_ERRMSG];

		fits_read_errmsg(fitsErrorMessage);

		std::string error = std::format("Error opening file {}: {} (Code: {})", path, fitsErrorMessage, resultCode);

		return std::unexpected<std::string>(error);
	}

	return AtlasFitsDataUtilities::MemorySafeFitsFile(filePointer);
}

std::expected<bool, std::string> AtlasFitsDataUtilities::moveToHeaderDataUnit(AtlasFitsDataUtilities::MemorySafeFitsFile& file, int index)
{
	return AtlasFitsDataUtilities::moveToHeaderDataUnit(file.get(), index);
}

std::expected<bool, std::string> AtlasFitsDataUtilities::getRowCount(AtlasFitsDataUtilities::MemorySafeFitsFile& file, long& count)
{
	return AtlasFitsDataUtilities::getRowCount(file.get(), count);
}

std::expected<bool, std::string> AtlasFitsDataUtilities::getColumnCount(AtlasFitsDataUtilities::MemorySafeFitsFile& file, int& count)
{
	return AtlasFitsDataUtilities::getColumnCount(file.get(), count);
}

std::expected<bool, std::string> AtlasFitsDataUtilities::getColumnIndex(AtlasFitsDataUtilities::MemorySafeFitsFile& file, std::string column, int& index)
{
	return AtlasFitsDataUtilities::getColumnIndex(file.get(), column, index);
}

std::expected<bool, std::string> AtlasFitsDataUtilities::getColumnWidth(AtlasFitsDataUtilities::MemorySafeFitsFile& file, int column, int& width)
{
	return AtlasFitsDataUtilities::getColumnWidth(file.get(), column, width);
}

std::expected<bool, std::string> AtlasFitsDataUtilities::loadColumnIntoBuffer(AtlasFitsDataUtilities::MemorySafeFitsFile& file, int column, long start, std::vector<std::string>& buffer, std::string defaultValue)
{
	return AtlasFitsDataUtilities::loadColumnIntoBuffer(file.get(), column, start, buffer, defaultValue);
}
