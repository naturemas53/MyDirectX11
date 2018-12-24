#include "BMPHeaderDatas.h"
#include <Windows.h>
#include "../../BMPImage.h"
#include <vector>

using namespace MyDirectX11;

BMPHeaderDatas::BMPHeaderDatas(){

}

BMPHeaderDatas::~BMPHeaderDatas(){


}

bool BMPHeaderDatas::ReadingData(std::ifstream& file,BMPData& data){

	std::vector<char> buffer(256,0);
	//ヘッダサイズ　いらね
	file.read(buffer.data(),sizeof(BYTE) * 4);

	//画像サイズ読み込み　幅->高さの順
	int width = 0, height = 0;
	file.read((char*)&width, sizeof(int));
	file.read((char*)&height, sizeof(int));

	data.width = width;
	data.height = height;

	/*
	めんどくさいので今回は圧縮形式とか縦横解像度とかは気にしません
	あしからず
	*/
	//ってことで画像データ部のサイズまで読み飛ばし
	file.read(buffer.data(),sizeof(BYTE) * 8);

	//データ部サイズ読み込み
	file.read((char*)&(data.fileLength),sizeof(int));

	//最後に情報ヘッダ抜けるために飛ばす
	file.read(buffer.data(), sizeof(BYTE) * 16);

	return true;

}