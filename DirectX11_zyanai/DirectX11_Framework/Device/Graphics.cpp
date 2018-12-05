#include "Graphics.h"
#include "../Device.h"

#include "../../Shader/Compiled/vs_sample.h"
#include "../../Shader/Compiled/ps_sample.h"

#include <atltypes.h>
#include <DirectXMath.h>

using namespace MyDirectX11;

struct Vertex {
	float pos[3];
	float col[4];
};

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

	Vertex g_VertexList[]{
			{ { -0.5f,  0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ {  0.5f, -0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
			{ { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
	};

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(Vertex) * 3;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = g_VertexList;
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	pDevice->CreateBuffer(&bufferDesc, &subResourceData, &this->pVertexBuffer_);

	D3D11_INPUT_ELEMENT_DESC g_VertexDesc[]{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	pDevice->CreateInputLayout(g_VertexDesc, ARRAYSIZE(g_VertexDesc),
							   g_vs_main, sizeof(g_vs_main),
							   &this->pInputLayout_);

	pDevice->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, &this->pVertexShader_);

	pDevice->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, &this->pPixelShader_);
	
	HWND hwnd = DX11_DEVICE.GetHWnd();
	CRect rect;
	::GetClientRect(hwnd, &rect);
	this->viewport_.TopLeftX = 0;
	this->viewport_.TopLeftY = 0;
	this->viewport_.Width = (FLOAT)rect.Width();
	this->viewport_.Height = (FLOAT)rect.Height();
	this->viewport_.MinDepth = 0.0f;
	this->viewport_.MaxDepth = 1.0f;

	return true;

}


void Graphics::Release() {

	SafeRelease(this->pRenderTargetView_);

	SafeRelease(this->pDepthStencilView_);
	SafeRelease(this->pDepthStencil_);

}

void Graphics::Render() {

	ID3D11DeviceContext* pDeviceContext = DX11_DEVICE.GetDeviceContext();
	IDXGISwapChain* pSwapChain = DX11_DEVICE.GetSwapChain();

	float clearColor[4] = { 0.0f, 0.2f, 0.2f, 1.0f }; //red,green,blue,alpha

	pDeviceContext->OMSetRenderTargets(1, &this->pRenderTargetView_, this->pDepthStencilView_);
	pDeviceContext->ClearRenderTargetView(this->pRenderTargetView_, clearColor);
	pDeviceContext->ClearDepthStencilView(this->pDepthStencilView_, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	UINT strides = sizeof(Vertex);
	UINT offsets = 0;
	pDeviceContext->IASetInputLayout(this->pInputLayout_);
	pDeviceContext->IASetVertexBuffers(0, 1, &this->pVertexBuffer_, &strides, &offsets);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pDeviceContext->VSSetShader(this->pVertexShader_, NULL, 0);
	pDeviceContext->RSSetViewports(1, &this->viewport_);
	pDeviceContext->PSSetShader(this->pPixelShader_, NULL, 0);

	pDeviceContext->Draw(3, 0);


	pSwapChain->Present(0,0);

}