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

	std::expected<bool, std::string> moveToHeaderDataUnit(fitsfile* file, int index);

	std::expected<bool, std::string> getRowCount(fitsfile* file, long& count);

	std::expected<bool, std::string> getColumnCount(fitsfile* file, int& count);

	std::expected<bool, std::string> getColumnIndex(fitsfile* file, std::string column, int& index);

	std::expected<bool, std::string> getColumnWidth(fitsfile* file, int column, int& width);

	template <typename T>
	std::expected<bool, std::string> loadColumnIntoBuffer(fitsfile* file, int column, long start, std::vector<T>& buffer, T defaultValue = 0)
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

	std::expected<bool, std::string> loadColumnIntoBuffer(fitsfile* file, int column, long start, std::vector<std::string>& buffer, std::string defaultValue = "");
};

#endif