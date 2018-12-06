#include "ShaderParamater.h"
#include "Shader.h"

using namespace MyDirectX11;

ShaderParamater::ShaderParamater(ID3D11Buffer* pParamaterBuffer) {

	this->pParamaterBuffer_ = pParamaterBuffer;

}

ShaderParamater::~ShaderParamater() {



}

void ShaderParamater::SetParamaterToShader(CVertexShader* pVertexShader,ID3D11DeviceContext* pDeviceContext) {

	pVertexShader->SetParamater(this,pDeviceContext);

}

void ShaderParamater::SetParamaterToShader(CPixelShader* pPixelShader, ID3D11DeviceContext* pDeviceContext) {

	pPixelShader->SetParamater(this, pDeviceContext);

}

void ShaderParamater::SetValues(void* paramater, ID3D11DeviceContext* pDeviceContext) {

	pDeviceContext->UpdateSubresource(this->pParamaterBuffer_, 0, NULL, paramater, 0, 0);

}