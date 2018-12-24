#pragma once
#include <d3d11.h>
#include "../Image/Image.h"

namespace MyDirectX11 {

	class Texture final{

	public:

		Texture(ID3D11Texture2D* pTexture, ID3D11ShaderResourceView* pSRV, ID3D11SamplerState* pSampler);
		~Texture();

		void AttachThisTextureToPS( ID3D11DeviceContext* pDeviceContext );

		ID3D11Texture2D* GetTexture() { return this->pTexture_; }
		ID3D11ShaderResourceView* GetSRV() { return this->pSRV_; }
		ID3D11SamplerState* GetSamplerState() { return this->pSampler_; }

	private:

		ID3D11Texture2D* pTexture_;
		ID3D11ShaderResourceView* pSRV_;
		ID3D11SamplerState* pSampler_;

	};

}