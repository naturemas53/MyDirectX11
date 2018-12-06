#include "Shader.h"
#include "ShaderParamater.h"

using namespace MyDirectX11;

CVertexShader::CVertexShader(ID3D11VertexShader* pVertexShader , ID3D11InputLayout* pInputLayout) {

	this->pVertexShader_ = pVertexShader;
	this->pInputLayout_ = pInputLayout;

}

CVertexShader::~CVertexShader() {



}

void CVertexShader::SetThisShader(ID3D11DeviceContext* pDeviceContext) {

	pDeviceContext->VSSetShader(this->pVertexShader_, NULL , 0 );

	if (this->pInputLayout_ == nullptr) return;

	pDeviceContext->IASetInputLayout(this->pInputLayout_);

}

void CVertexShader::SetParamater(ShaderParamater* pShaderParamater, ID3D11DeviceContext* pDeviceContext) {

	ID3D11Buffer* const buffer = pShaderParamater->GetBuffer();

	pDeviceContext->VSSetConstantBuffers(0,1,&buffer);
	
}