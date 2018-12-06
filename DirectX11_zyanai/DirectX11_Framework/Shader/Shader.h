#pragma once
#include <d3d11.h>

namespace MyDirectX11 {

	class ShaderParamater;

	class CVertexShader final{

	public:

		CVertexShader(ID3D11VertexShader* pVertexShader, ID3D11InputLayout* pInputLayout = nullptr);
		~CVertexShader();

		void SetThisShader(ID3D11DeviceContext* pDeviceContext);
		static void SetParamater(ShaderParamater* pShaderParamater, ID3D11DeviceContext* pDeviceContext);
		
		ID3D11VertexShader* GetShader() { return this->pVertexShader_; }
		ID3D11InputLayout* GetInputLayout() { return this->pInputLayout_; }

	private:

		ID3D11VertexShader* pVertexShader_;
		ID3D11InputLayout* pInputLayout_;

	};

	class CPixelShader final {

	public:

		CPixelShader(ID3D11PixelShader* pPixelShader, ID3D11InputLayout* pInputLayout = nullptr);
		~CPixelShader();

		void SetThisShader(ID3D11DeviceContext* pDeviceContext);
		static void SetParamater(ShaderParamater* pShaderParamater, ID3D11DeviceContext* pDeviceContext);

		ID3D11PixelShader* GetShader() { return this->pPixelShader_; }
		ID3D11InputLayout* GetInputLayout() { return this->pInputLayout_; }

	private:

		ID3D11PixelShader* pPixelShader_;
		ID3D11InputLayout* pInputLayout_;

	};

}