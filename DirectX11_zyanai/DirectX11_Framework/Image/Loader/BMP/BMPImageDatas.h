#pragma once
#include <fstream>

namespace MyDirectX11 {

	struct BMPData;

	class BMPImageDatas{

	public:

		BMPImageDatas();
		~BMPImageDatas();

		virtual bool ReadingData(std::ifstream& file, BMPData& data, void* outData);

	};

}