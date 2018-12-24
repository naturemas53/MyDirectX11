#pragma once
#include "Image.h"
#include <Windows.h>

namespace MyDirectX11{

	struct BMPData {

		int width = 0;
		int height = 0;
		int fileLength = 0;

	};

	class BMPImage final: public Image {

	public:
		BMPImage(const BYTE* pSrcData,const int dataLength,BMPData optionData);
		virtual ~BMPImage();

		virtual void* GetData()	  { return this->pData_; }
		virtual int	  GetWidth()  { return this->width_;  }
		virtual int   GetHeight() { return this->height_; }
		virtual int   GetPixelSize() { return sizeof(char) * 4; }
		virtual int   GetWidthStride() { return this->width_ * (sizeof(char) * 4); }
		virtual int   GetSize() { return this->size_; }

	private:

		BYTE* pData_;
		int	  width_;
		int   height_;
		int   size_;

	};

}