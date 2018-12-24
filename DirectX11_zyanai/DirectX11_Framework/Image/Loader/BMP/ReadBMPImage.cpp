#include "ReadBMPImage.h"
#include "BMPHeaderDatas.h"
#include "BMPImageDatas.h"
#include "../../BMPImage.h"

#include <fstream>
#include <iostream>
#include <vector>

using namespace MyDirectX11;
using namespace std;

ReadBMPImage::ReadBMPImage(){

	pData_ = nullptr;

}

ReadBMPImage::~ReadBMPImage(){

	if (pData_ != nullptr) {

		delete[] pData_;

	}

}

bool ReadBMPImage::ReadImageToPath(std::string imagePath,BYTE** outData,int* outLength,BMPData& outOptionData){

	ifstream file(imagePath, ios::in | ios::binary);
	std::vector<char> buffer(256,0);

	try{

		if (!file){

			throw("\nError! -> fileMakeFailed  (ReadBMPImage)\n");

		}

		file.read(buffer.data(),sizeof(BYTE) * 2);

		if (strncmp(buffer.data(), "BM", 2) != 0){

			throw("\nError! -> NotBMPFile  (ReadBMPImage)\n");

		}

		//“Ç‚Ý”ò‚Î‚µƒ}ƒ“
		file.read(buffer.data(),sizeof(BYTE) * 12);

		BMPHeaderDatas().ReadingData(file, outOptionData);

		if (pData_ != nullptr) {

			delete[] pData_;

		}

		int size = outOptionData.width * outOptionData.height * 4;

		this->pData_ = new BYTE[size];

		BMPImageDatas().ReadingData(file, outOptionData,this->pData_);

		*outLength = size;
		*outData = this->pData_;

	}
	catch (std::string errorMessage){
		::OutputDebugStringA(errorMessage.c_str());

		file.close();

		return false;

	}

	file.close();

	return true;

}