#ifndef ATLAS_FITS_DATA_UTILITIES_H
#define ATLAS_FITS_DATA_UTILITIES_H

#include <expected>
#include <fitsio.h>
#include <format>
#include <longnam.h>
#include <memory>
#include <string>
#include <vector>

namespace AtlasFitsDataUtilities
{
	struct DestroyFitsFile
	{
		void operator()(fitsfile* file) const
		{
			fits_close_file(file, nullptr);
		}
	};

	using MemorySafeFitsFile = std::unique_ptr<fitsfile, DestroyFitsFile>;

	template<typename T> struct FitsType;

	template<> struct FitsType<double>
	{
		static constexpr int typeCode = TDOUBLE;
	};

	template<> struct FitsType<float>
	{
		static constexpr int typeCode = TFLOAT;
	};

	template<> struct FitsType<int>
	{
		static constexpr int typeCode = TINT;
	};

	template<> struct FitsType<long>
	{
		static constexpr int typeCode = TLONG;
	};

	template<> struct FitsType<short>
	{
		static constexpr int typeCode = TSHORT;
	};

	template<> struct FitsType<unsigned char>
	{
		static constexpr int typeCode = TBYTE;
	};

	std::expected<MemorySafeFitsFile, std::string> open(std::string path);

	static std::expected<bool, std::string> moveToHeaderDataUnit(fitsfile* file, int index)
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

	std::expected<bool, std::string> moveToHeaderDataUnit(MemorySafeFitsFile& file, int index);

	static std::expected<bool, std::string> getRowCount(fitsfile* file, long& count)
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

	std::expected<bool, std::string> getRowCount(MemorySafeFitsFile& file, long& count);

	static std::expected<bool, std::string> getColumnCount(fitsfile* file, int& count)
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

	std::expected<bool, std::string> getColumnCount(MemorySafeFitsFile& file, int& count);

	static std::expected<bool, std::string> getColumnIndex(fitsfile* file, std::string column, int& index)
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

	std::expected<bool, std::string> getColumnIndex(MemorySafeFitsFile& file, std::string column, int& index);

	static std::expected<bool, std::string> getColumnWidth(fitsfile* file, int column, int& width)
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

	std::expected<bool, std::string> getColumnWidth(MemorySafeFitsFile& file, int column, int& width);

	template <typename T>
	static std::expected<bool, std::string> loadColumnIntoBuffer(fitsfile* file, int column, long start, std::vector<T>& buffer, T defaultValue = 0)
	{
		int status = 0;

		long size = static_cast<long>(buffer.size());

		fits_read_col(file, FitsType<T>::typeCode, column, start, 1, size, &defaultValue, buffer.data(), nullptr, &status);

		if (status) {
			char description[FLEN_ERRMSG];

			fits_read_errmsg(description);

			std::string error = std::format("Error loading column into buffer: {} (Code: {})", description, status);

			return std::unexpected<std::string>(error);
		}

		return true;
	}

	template <typename T>
	std::expected<bool, std::string> loadColumnIntoBuffer(MemorySafeFitsFile& file, int column, long start, std::vector<T>& buffer, T defaultValue = 0)
	{
		return loadColumnIntoBuffer(file.get(), column, start, buffer, defaultValue);
	}

	static std::expected<bool, std::string> loadColumnIntoBuffer(fitsfile* file, int column, long start, std::vector<std::string>& buffer, std::string defaultValue = "")
	{
		int status = 0;

		int width = 0;

		std::expected<bool, std::string> widthResult = AtlasFitsDataUtilities::getColumnWidth(file, column, width);

		if (!widthResult.has_value()) {
			return widthResult;
		}

		long size = static_cast<long>(buffer.size());

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

	std::expected<bool, std::string> loadColumnIntoBuffer(MemorySafeFitsFile& file, int column, long start, std::vector<std::string>& buffer, std::string defaultValue = "");
};

#endif