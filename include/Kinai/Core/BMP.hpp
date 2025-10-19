#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/Texture.hpp"

namespace Kinai
{

class BMP
{
private:
	
public:
	BMP(const char *filepath);

	ImageFormat format() const { return _infoHeader.bitCount == 24 ? ImageFormat::BGR : ImageFormat::BGRA; }
	int width() const { return _infoHeader.width; }
	int height() const { return _infoHeader.height; }

	const uint8_t* data() const { return _data.data(); }

private:
	std::ifstream	_file;

	#pragma pack(push, 1)
	struct
	{
		uint16_t fileType;	// File type, always 4D42h ("BM")
		uint32_t fileSize;	// Size of the file in bytes
		uint16_t reserved1;	// Always 0
		uint16_t reserved2;	// Always 0
		uint32_t offsetData; // Starting position of pixel data (bytes from the beginning of the file)
	}_fileHeader;
	static_assert(sizeof(_fileHeader) == 14, "File header size is incorrect");

	struct BMPInfoHeader
	{
		uint32_t size;			// Size of this header (in bytes)
		int32_t width;			// Width of bitmap in pixels
		int32_t height;			// Height of bitmap in pixels
		uint16_t planes;			// No. of planes for the target device, this is always 1
		uint16_t bitCount;		// No. of bits per pixel
		uint32_t compression;	// 0 or 3 - uncompressed
		uint32_t sizeImage;		// 0 - for uncompressed images
		int32_t xPelsPerMeter;	// Horizontal resolution (pixels per meter)
		int32_t yPelsPerMeter;	// Vertical resolution (pixels per meter)
		uint32_t clrUsed;		// No. of colors in the color palette, or 0 to default to 2^n
		uint32_t clrImportant;	// No. of important colors used, or 0 when every color is important
	}_infoHeader;
	#pragma pack(pop)

	struct BMPColorHeader
	{
		uint32_t redMask;		// Mask identifying bits of red component
		uint32_t greenMask;		// Mask identifying bits of green component
		uint32_t blueMask;		// Mask identifying bits of blue component
		uint32_t alphaMask;		// Mask identifying bits of alpha component
		uint32_t colorSpaceType;	// Color space type
		uint32_t unused[16];	 	// Unused data for sRGB color space
	}_colorHeader;

	std::vector<uint8_t> _data;
	bool _hasColorHeader;

private:
	template <class Tp>
	void	read(Tp &data);
};

template <class Tp>
void
BMP::read(Tp &data)
{
	if (!_file.read(reinterpret_cast<char *>(&data), sizeof(Tp)))
		throw std::runtime_error("Failed to read from file");
}

} // Kinai
