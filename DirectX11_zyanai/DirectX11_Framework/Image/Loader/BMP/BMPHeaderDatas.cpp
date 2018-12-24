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
	//�w�b�_�T�C�Y�@�����
	file.read(buffer.data(),sizeof(BYTE) * 4);

	//�摜�T�C�Y�ǂݍ��݁@��->�����̏�
	int width = 0, height = 0;
	file.read((char*)&width, sizeof(int));
	file.read((char*)&height, sizeof(int));

	data.width = width;
	data.height = height;

	/*
	�߂�ǂ������̂ō���͈��k�`���Ƃ��c���𑜓x�Ƃ��͋C�ɂ��܂���
	�������炸
	*/
	//���Ă��Ƃŉ摜�f�[�^���̃T�C�Y�܂œǂݔ�΂�
	file.read(buffer.data(),sizeof(BYTE) * 8);

	//�f�[�^���T�C�Y�ǂݍ���
	file.read((char*)&(data.fileLength),sizeof(int));

	//�Ō�ɏ��w�b�_�����邽�߂ɔ�΂�
	file.read(buffer.data(), sizeof(BYTE) * 16);

	return true;

}