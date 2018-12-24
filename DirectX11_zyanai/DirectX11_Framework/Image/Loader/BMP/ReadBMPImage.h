#pragma once
#include <Windows.h>
#include <string>

namespace MyDirectX11 {

	struct BMPData;

	class ReadBMPImage {

	public:

		ReadBMPImage();
		~ReadBMPImage();

		bool ReadImageToPath(std::string imagePath,BYTE** outData,int* outLength, BMPData& outOptionData);

	private:

		BYTE* pData_;

	};

}