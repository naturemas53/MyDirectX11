#pragma once
#include <d3d11.h>

namespace MyDirectX11 {

	class CVertexShader;
	class CPixelShader;

	class ShaderParamater final{

	public:

		ShaderParamater(ID3D11Buffer* pParamaterBuffer);
		~ShaderParamater();

		void SetValues(void* paramater, ID3D11DeviceContext* pDeviceContext);

		void SetParamaterToShader(CVertexShader* pVertexShader,ID3D11DeviceContext* pDeviceContext);
		void SetParamaterToShader(CPixelShader* pPixelShader , ID3D11DeviceContext* pDeviceContext);

		ID3D11Buffer* GetBuffer() { return this->pParamaterBuffer_; }

	private:

		ID3D11Buffer* pParamaterBuffer_;

	};

}