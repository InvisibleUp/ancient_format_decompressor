/* Copyright (C) Teemu Suutari */

#include <string.h>

#include "NONEDecompressor.hpp"

bool NONEDecompressor::detectHeaderXPK(uint32_t hdr)
{
	return hdr==FourCC('NONE');
}

NONEDecompressor::NONEDecompressor(uint32_t hdr,const Buffer &packedData,std::unique_ptr<XPKDecompressor::State> &state) :
	_packedData(packedData)
{
	if (!detectHeaderXPK(hdr)) return;
	_isValid=true;
}

NONEDecompressor::~NONEDecompressor()
{
	// nothing needed
}

bool NONEDecompressor::isValid() const
{
	return _isValid;
}

bool NONEDecompressor::verifyPacked() const
{
	return _isValid;
}

bool NONEDecompressor::verifyRaw(const Buffer &rawData) const
{
	return _isValid;
}

const std::string &NONEDecompressor::getSubName() const
{
	if (!_isValid) return XPKDecompressor::getSubName();
	static std::string name="XPK-NONE: Null compressor";
	return name;
}

bool NONEDecompressor::decompress(Buffer &rawData)
{
	if (!_isValid || rawData.size()<_packedData.size()) return false;

	::memcpy(rawData.data(),_packedData.data(),_packedData.size());
	return true;
}
