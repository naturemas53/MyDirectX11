#include "Shader.h"
#include "ShaderParamater.h"

using namespace MyDirectX11;

CPixelShader::CPixelShader(ID3D11PixelShader* pVertexShader, ID3D11InputLayout* pInputLayout) {

	this->pPixelShader_ = pVertexShader;
	this->pInputLayout_ = pInputLayout;

}

CPixelShader::~CPixelShader() {



}

void CPixelShader::SetThisShader(ID3D11DeviceContext* pDeviceContext) {

	pDeviceContext->PSSetShader(this->pPixelShader_, NULL, 0);

	if (this->pInputLayout_ == nullptr) return;

	pDeviceContext->IASetInputLayout(this->pInputLayout_);

}

void CPixelShader::SetParamater(ShaderParamater* pShaderParamater, ID3D11DeviceContext* pDeviceContext) {

	ID3D11Buffer* buffer = pShaderParamater->GetBuffer();

	pDeviceContext->PSSetConstantBuffers(0, 1, &buffer);

}