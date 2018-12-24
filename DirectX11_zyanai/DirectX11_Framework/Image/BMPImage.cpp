#include "BMPImage.h"

using namespace MyDirectX11;

BMPImage::BMPImage(const BYTE* pSrcData, const int dataLength, BMPData optionData) {

	this->size_ = dataLength;

	this->pData_ = new BYTE[this->size_];

	//memcpy(this->pData_, pSrcData, sizeof(BYTE) * this->size_);

	for (int i = 0; i < dataLength; i++) {

		this->pData_[i] = pSrcData[i];

	}

	this->width_ = optionData.width;
	this->height_ = optionData.height;

}

BMPImage::~BMPImage() {

	delete[] this->pData_;

}