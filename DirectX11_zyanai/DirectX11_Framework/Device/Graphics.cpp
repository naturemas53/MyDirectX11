#include "Graphics.h"
#include "../Device/Device.h"

#include "../VertexBuffer/VertexBuffer.h"
#include "../Shader/Shader.h"
#include "../Shader/ShaderParamater.h"

#include <atltypes.h>
#include <DirectXMath.h>

using namespace MyDirectX11;

Graphics::Graphics() {



}

Graphics::~Graphics() {



}

bool Graphics::Initialize() {
	
	ID3D11Device* pDevice = DX11_DEVICE.GetDevice();
	ID3D11DeviceContext* pDeviceContext = DX11_DEVICE.GetDeviceContext();
	IDXGISwapChain* pSwapChain = DX11_DEVICE.GetSwapChain();

	ID3D11Texture2D* pBackBuffer;
	//そのスワップチェインのバックバッファ取得
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	//そのバックバッファから描画ターゲット生成
	pDevice->CreateRenderTargetView(pBackBuffer,NULL,&this->pRenderTargetView_);
	pBackBuffer->Release();

	D3D11_TEXTURE2D_DESC txDesc;
	ZeroMemory(&txDesc, sizeof(txDesc));
	txDesc.Width = 1280;
	txDesc.Height = 720;
	txDesc.MipLevels = 1;
	txDesc.ArraySize = 1;
	txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	txDesc.SampleDesc.Count = 1;
	txDesc.SampleDesc.Quality = 0;
	txDesc.Usage = D3D11_USAGE_DEFAULT;
	txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	txDesc.CPUAccessFlags = 0;
	txDesc.MiscFlags = 0;
	pDevice->CreateTexture2D(&txDesc, NULL, &this->pDepthStencil_);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.Format = txDesc.Format;
	dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsDesc.Texture2D.MipSlice = 0;
	pDevice->CreateDepthStencilView(this->pDepthStencil_, &dsDesc, &this->pDepthStencilView_);

	//struct Vertex {
	//	float pos[3];
	//	float col[4];
	//};

	//Vertex g_VertexList[]{
	//		{ { -0.5f,  0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
	//		{ {  0.5f, -0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
	//		{ { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
	//};

	//D3D11_BUFFER_DESC bufferDesc;
	//bufferDesc.ByteWidth = sizeof(Vertex) * 3;
	//bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bufferDesc.CPUAccessFlags = 0;
	//bufferDesc.MiscFlags = 0;
	//bufferDesc.StructureByteStride = 0;

	//D3D11_SUBRESOURCE_DATA subResourceData;
	//subResourceData.pSysMem = g_VertexList;
	//subResourceData.SysMemPitch = 0;
	//subResourceData.SysMemSlicePitch = 0;

	//pDevice->CreateBuffer(&bufferDesc, &subResourceData, &this->pVertexBuffer_);

	//D3D11_INPUT_ELEMENT_DESC g_VertexDesc[]{
	//{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//};

	//pDevice->CreateInputLayout(g_VertexDesc, ARRAYSIZE(g_VertexDesc),
	//						   g_vs_main, sizeof(g_vs_main),
	//						   &this->pInputLayout_);

	//pDevice->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, &this->pVertexShader_);

	//pDevice->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, &this->pPixelShader_);
	
	HWND hwnd = DX11_DEVICE.GetHWnd();
	CRect rect;
	::GetClientRect(hwnd, &rect);
	this->viewport_.TopLeftX = 0;
	this->viewport_.TopLeftY = 0;
	this->viewport_.Width = (FLOAT)rect.Width();
	this->viewport_.Height = (FLOAT)rect.Height();
	this->viewport_.MinDepth = 0.0f;
	this->viewport_.MaxDepth = 1.0f;

	pDeviceContext->RSSetViewports(1,&this->viewport_);

	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return true;

}

CVertexShader* Graphics::CreateVertexShader(void* shaderCode, size_t shaderSize,
											D3D11_INPUT_ELEMENT_DESC* elementDescs, int elementDescCount) {

	ID3D11Device* pDevice = DX11_DEVICE.GetDevice();

	ID3D11VertexShader* pVertexShader = nullptr;
	pDevice->CreateVertexShader(shaderCode,shaderSize,NULL,&pVertexShader);

	ID3D11InputLayout* pInputLayout = nullptr;
	if (elementDescs != nullptr) {

		pDevice->CreateInputLayout(elementDescs,elementDescCount,shaderCode,shaderSize,&pInputLayout);

	}

	CVertexShader* vertexShader = new CVertexShader(pVertexShader,pInputLayout);

	this->vertexShaders_.push_back(vertexShader);

	return vertexShader;

}

CPixelShader* Graphics::CreatePixelShader(void* shaderCode, size_t shaderSize,
	D3D11_INPUT_ELEMENT_DESC* elementDescs, int elementDescCount) {

	ID3D11Device* pDevice = DX11_DEVICE.GetDevice();

	ID3D11PixelShader* pPixelShader = nullptr;
	pDevice->CreatePixelShader(shaderCode, shaderSize, NULL, &pPixelShader);

	ID3D11InputLayout* pInputLayout = nullptr;
	if (elementDescs != nullptr) {

		pDevice->CreateInputLayout(elementDescs, elementDescCount, shaderCode, shaderSize, &pInputLayout);

	}

	CPixelShader* pixelShader = new CPixelShader(pPixelShader, pInputLayout);

	this->pixelShaders_.push_back(pixelShader);

	return pixelShader;

}

ShaderParamater* Graphics::CreateShaderParamater(size_t paramaterSize) {

	ID3D11Device* pDevice = DX11_DEVICE.GetDevice();

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = paramaterSize;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	ID3D11Buffer* pParamaterBuffer;
	pDevice->CreateBuffer(&bufferDesc,NULL,&pParamaterBuffer);

	ShaderParamater* shaderPamarater = new ShaderParamater(pParamaterBuffer);

	this->shaderParamaters_.push_back(shaderPamarater);

	return shaderPamarater;

}

void Graphics::Release() {

	for (auto data : this->vertexBuffers_) {

		data->GetDX11Buffer()->Release();
		delete data;

	}

	this->vertexBuffers_.clear();

	for (auto data : this->vertexShaders_) {

		data->GetShader()->Release();

		if (data->GetInputLayout() != nullptr)
			data->GetInputLayout()->Release();

		delete data;

	}

	this->vertexShaders_.clear();

	for (auto data : this->pixelShaders_) {

		data->GetShader()->Release();

		if (data->GetInputLayout() != nullptr)
			data->GetInputLayout()->Release();

		delete data;

	}

	this->pixelShaders_.clear();

	for (auto data : this->shaderParamaters_) {

		data->GetBuffer()->Release();

		delete data;

	}

	this->shaderParamaters_.clear();

	SafeRelease(this->pRenderTargetView_);

	SafeRelease(this->pDepthStencilView_);
	SafeRelease(this->pDepthStencil_);

}

void Graphics::Clear() {

	ID3D11DeviceContext* pDeviceContext = DX11_DEVICE.GetDeviceContext();

	float clearColor[4] = { 0.0f, 0.2f, 0.2f, 1.0f }; //red,green,blue,alpha

	pDeviceContext->OMSetRenderTargets(1, &this->pRenderTargetView_, this->pDepthStencilView_);
	pDeviceContext->ClearRenderTargetView(this->pRenderTargetView_, clearColor);
	pDeviceContext->ClearDepthStencilView(this->pDepthStencilView_, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

}

//void Graphics::Render() {
//
//	ID3D11DeviceContext* pDeviceContext = DX11_DEVICE.GetDeviceContext();
//
//
//	UINT strides = sizeof(Vertex);
//	UINT offsets = 0;
//	pDeviceContext->IASetInputLayout(this->pInputLayout_);
//	pDeviceContext->IASetVertexBuffers(0, 1, &this->pVertexBuffer_, &strides, &offsets);
//	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//	pDeviceContext->VSSetShader(this->pVertexShader_, NULL, 0);
//	pDeviceContext->RSSetViewports(1, &this->viewport_);
//	pDeviceContext->PSSetShader(this->pPixelShader_, NULL, 0);
//
//	pDeviceContext->Draw(3, 0);
//
//}

void Graphics::ScreenSwap() {

	IDXGISwapChain* pSwapChain = DX11_DEVICE.GetSwapChain();
	pSwapChain->Present(0, 0);

}