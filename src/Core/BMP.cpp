#include "Kinai/Core/BMP.hpp"

namespace Kinai
{

BMP::BMP(const char *filepath)
	: _file(filepath, std::ios::binary),
	_fileHeader(),
	_infoHeader(),
	_colorHeader(),
	_data(),
	_hasColorHeader(false)
{
	if (!_file.is_open())
	{
		Log::Critical("Invalid filepath: {}", filepath);
	}

	// Read headers
	this->read(_fileHeader);
	if (_fileHeader.fileType != 0x4D42)
		Log::Critical("Invalid file format: {}", filepath);

	this->read(_infoHeader);

	// Optional color header
	if (_infoHeader.bitCount == 32)
	{
		this->read(_colorHeader);
		_hasColorHeader = true;
	}

	// Determine compression
	const uint32_t compression = _infoHeader.compression;

	if (compression != 0 && compression != 3)
	{
		Log::Critical("Unsupported BMP compression format: {}", compression);
	}

	const int bpp = _infoHeader.bitCount / 8;
	const int width = _infoHeader.width;
	const int height = std::abs(_infoHeader.height);
	const bool isBottomUp = (_infoHeader.height > 0);
	const int rowSize = ((width * bpp + 3) / 4) * 4;

	// Seek to pixel data
	_file.seekg(_fileHeader.offsetData, std::ios::beg);
	std::vector<uint8_t> bmpData(rowSize * height);
	_file.read(reinterpret_cast<char*>(bmpData.data()), bmpData.size());

	_data.resize(static_cast<size_t>(width) * height * bpp);

	for (int y = 0; y < height; ++y)
	{
		int srcY = isBottomUp ? (height - 1 - y) : y;
		const uint8_t* srcRow = bmpData.data() + static_cast<size_t>(srcY) * rowSize;
		uint8_t* dstRow = _data.data() + static_cast<size_t>(y) * width * bpp;
		memcpy(dstRow, srcRow, static_cast<size_t>(width) * bpp);
	}

	// Handle BI_BITFIELDS color masks (if any)
	if (compression == 3 && _infoHeader.bitCount == 32)
	{
		uint32_t redMask   = _colorHeader.redMask;
		uint32_t greenMask = _colorHeader.greenMask;
		uint32_t blueMask  = _colorHeader.blueMask;
		uint32_t alphaMask = _colorHeader.alphaMask;

		auto maskToShift = [](uint32_t mask)
		{
			if (mask == 0) return 0;
			int shift = 0;
			while ((mask & 1) == 0)
			{
				mask >>= 1;
				++shift;
			}
			return shift;
		};

		int rShift = maskToShift(redMask);
		int gShift = maskToShift(greenMask);
		int bShift = maskToShift(blueMask);
		int aShift = maskToShift(alphaMask);

		std::vector<uint8_t> converted(_data.size());

		for (size_t i = 0; i < _data.size(); i += 4)
		{
			uint32_t pixel = *reinterpret_cast<const uint32_t*>(&_data[i]);
			uint8_t r = static_cast<uint8_t>((pixel & redMask) >> rShift);
			uint8_t g = static_cast<uint8_t>((pixel & greenMask) >> gShift);
			uint8_t b = static_cast<uint8_t>((pixel & blueMask) >> bShift);
			uint8_t a = (alphaMask != 0) ? static_cast<uint8_t>((pixel & alphaMask) >> aShift) : 255;
			converted[i + 0] = b;
			converted[i + 1] = g;
			converted[i + 2] = r;
			converted[i + 3] = a;
		}
		_data.swap(converted);
	}

	Log::Trace("Loaded BMP '{}': {}x{}, {}bpp, compression={}, bottomUp={}, hasColorHeader={}",
		filepath, width, height, _infoHeader.bitCount, compression, isBottomUp, _hasColorHeader);
}

} // Kinai
