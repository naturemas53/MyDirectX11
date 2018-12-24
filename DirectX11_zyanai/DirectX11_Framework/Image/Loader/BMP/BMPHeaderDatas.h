#pragma once
#include <fstream>

namespace MyDirectX11 {

	struct BMPData;

	class BMPHeaderDatas {

	public:
		BMPHeaderDatas();
		~BMPHeaderDatas();

		virtual bool ReadingData(std::ifstream& file,BMPData& data);

	};

}