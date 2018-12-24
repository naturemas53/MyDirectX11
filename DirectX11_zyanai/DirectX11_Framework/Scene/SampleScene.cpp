#include "SampleScene.h"
#include "../Device/Device.h"
#include "../Device/Graphics.h"

#include "../Square.h"
#include "../Shader/Shader.h"
#include "../Shader/ShaderParamater.h"
#include "../Texture/Texture.h"

//#include "../../Shader/Compiled/vs_screen.h"
//#include "../../Shader/Compiled/vs_sample.h"
//#include "../../Shader/Compiled/ps_sample.h"

#include "../../Shader/Compiled/ps_enableTexture.h"
#include "../../Shader/Compiled/vs_enableTexture.h"

#include <DirectXMath.h>

using namespace MyDirectX11;

bool SampleScene::Initialize() {

	ID3D11Device* pDevice = DX11_DEVICE.GetDevice();
	ID3D11DeviceContext* pDeviceContext = DX11_DEVICE.GetDeviceContext();

	this->square_ = new Square(200.0f,200.0f);
	this->square_->Initialize(pDevice);

	this->square_->SetPosition(Vector3(10, 50, 0));

	D3D11_INPUT_ELEMENT_DESC* descs = nullptr;
	int elementCount = 0;

	VertexData::GetElementDescs(&descs,&elementCount);

	this->vertexShader_ = DX11_GRAPHIC.CreateVertexShader(const_cast<BYTE*>(g_vs_main), sizeof(g_vs_main), descs, elementCount);
	this->pixelShader_  = DX11_GRAPHIC.CreatePixelShader (const_cast<BYTE*>(g_ps_main), sizeof(g_ps_main));

	this->vertexShader_->SetThisShader(pDeviceContext);
	this->pixelShader_ ->SetThisShader(pDeviceContext);

	const float WIDTH = 1280.0f;
	const float HEIGHT = 720.0f;
	DirectX::XMFLOAT4X4 matrix( WIDTH / 2.0f,			0.0f, 0.0f, 0.0f,
										0.0f, -HEIGHT / 2.0f, 0.0f, 0.0f,
										0.0f,			0.0f, 1.0f, 0.0f,
								WIDTH / 2.0f,  HEIGHT / 2.0f, 0.0f, 1.0f);

	DirectX::XMMATRIX vpInvertMat = DirectX::XMLoadFloat4x4(&matrix);

	vpInvertMat = DirectX::XMMatrixInverse(nullptr, vpInvertMat);

	DirectX::XMFLOAT4X4 shaderMat;
	ZeroMemory(&shaderMat, sizeof(DirectX::XMFLOAT4X4));
	DirectX::XMStoreFloat4x4(&shaderMat, DirectX::XMMatrixTranspose(vpInvertMat));

	this->shaderParamater_ = DX11_GRAPHIC.CreateShaderParamater(sizeof(DirectX::XMMATRIX));

	this->shaderParamater_->SetValues(&shaderMat, pDeviceContext);

	this->shaderParamater_->SetParamaterToShader(this->vertexShader_,pDeviceContext);

	this->texture_ = DX11_GRAPHIC.CreateTexture("halohalo.bmp");
	this->texture_->AttachThisTextureToPS(pDeviceContext);



	return true;

}

void SampleScene::Finalize() {

	delete this->square_;

}

void SampleScene::Update() {

	Vector3 pos = this->square_->GetPosision();

	pos += Vector3(0.0f,0.0f,0.0f);

	this->square_->SetPosition(pos);

}

void SampleScene::Draw() {

	ID3D11DeviceContext* pDeviceContext = DX11_DEVICE.GetDeviceContext();

	this->square_->Draw(pDeviceContext);

}