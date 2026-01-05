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
	_file.open(filepath, std::ios::binary);
	if (!_file.is_open())
	{
		Log::Critical("Invalid filepath: {}", filepath);
	}

	_file.clear();
	// Read headers
	this->read(_fileHeader);
	if (_fileHeader.fileType != 0x4D42)
	{
		Log::Critical("Invalid file format: {}", filepath);
	}
	this->read(_infoHeader);
	if (_infoHeader.bitCount == 32)
	{
		this->read(_colorHeader);
		_hasColorHeader = true;
	}
	
	// Read data
	_file.seekg(_fileHeader.offsetData, _file.beg);
	_data.resize(_infoHeader.width * _infoHeader.height * _infoHeader.bitCount / 8);
	_file.read(reinterpret_cast<char *>(_data.data()), _data.size());
}

} // Kinai
