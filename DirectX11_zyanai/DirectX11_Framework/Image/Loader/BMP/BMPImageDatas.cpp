#include "BMPImageDatas.h"
#include "../../BMPImage.h"

#include <vector>
#include <list>

using namespace MyDirectX11;

BMPImageDatas::BMPImageDatas(){


}

BMPImageDatas::~BMPImageDatas(){


}

bool BMPImageDatas::ReadingData(std::ifstream& file,BMPData& data,void* outData){

	int width = data.width, height = data.height;
	int widthRivision = (width * 3) % 4;
	if (widthRivision != 0) widthRivision = 4 - widthRivision;

	struct BMPColor {

		BYTE r = 0;
		BYTE g = 0;
		BYTE b = 0;

	};

	std::list<std::vector<BMPColor> > imageData;
	std::vector<BYTE> buffer(256, 0);

	for (int i = 0; i < height ;i++) {

		std::vector<BMPColor> recordColor;

		for (int j = 0; j < width; j++) {

			file.read((char*)buffer.data(), sizeof(BYTE) * 3);

			BMPColor color;
			color.b = buffer[0];
			color.g = buffer[1];
			color.r = buffer[2];

			recordColor.push_back(color);
		
		}

		imageData.push_front(recordColor);

		file.read((char*)buffer.data(), sizeof(BYTE) * widthRivision);

	}



	BYTE* pResource = (BYTE*)outData;

	auto heightItr = imageData.begin();

	for (int i = 0; i < height; i++,heightItr++) {

		if (heightItr == imageData.end()) {
			break;
		}

		for (int j = 0; j < (*heightItr).size();j++) {

			BMPColor color = (*heightItr)[j];
			int baseIndex = width * 4 * i + j * 4;

			pResource[baseIndex + 0] = color.r;
			pResource[baseIndex + 1] = color.g;
			pResource[baseIndex + 2] = color.b;

			pResource[baseIndex + 3] = 255;

			if (color.r == 255 && color.g == 255 && color.b == 255 ) {

				pResource[baseIndex + 3] = 0;

			}

		}

	}

	return true;

}