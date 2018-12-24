#include "Texture.h"

using namespace MyDirectX11;

Texture::Texture(ID3D11Texture2D* pTexture, ID3D11ShaderResourceView* pSRV, ID3D11SamplerState* pSampler) {

	this->pTexture_ = pTexture;
	this->pSRV_ = pSRV;
	this->pSampler_ = pSampler;

}

Texture::~Texture() {



}

void Texture::AttachThisTextureToPS(ID3D11DeviceContext* pDeviceContext) {

	pDeviceContext->PSSetShaderResources(0, 1, &this->pSRV_);
	pDeviceContext->PSSetSamplers(0,1,&this->pSampler_);

}