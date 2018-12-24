#include "Graphics.h"
#include "../Device/Device.h"

#include "../VertexBuffer/VertexBuffer.h"
#include "../Shader/Shader.h"
#include "../Shader/ShaderParamater.h"
#include "../Texture/Texture.h"
#include "../Image/BMPImage.h"
#include "../Image/Loader/BMP/ReadBMPImage.h"

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


	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	//こっちはいいでしょ
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	//転送先の色は　「1 - ソースもとのアルファ」% の色にしてよ　ってことらしい
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	//１になるようにしないと面白い
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	pDevice->CreateBlendState(&BlendDesc, &this->pBlendState_);
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	pDeviceContext->OMSetBlendState(this->pBlendState_, blendFactor, 0xffffffff);

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

Texture* Graphics::CreateTexture(std::string path) {

	ID3D11Device* pDevice = DX11_DEVICE.GetDevice();

	BYTE* pImageData = nullptr;
	int imageDataLength = 0;
	BMPData optionData;
	::ZeroMemory(&optionData,sizeof(BMPData));

	ReadBMPImage readBmp = ReadBMPImage();
	readBmp.ReadImageToPath(path,&pImageData,&imageDataLength,optionData);

	Image* image = new BMPImage(pImageData,imageDataLength,optionData);

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = image->GetWidth();
	desc.Height = image->GetHeight();
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = image->GetData();
	initData.SysMemPitch = image->GetWidthStride();
	initData.SysMemSlicePitch = image->GetSize();

	ID3D11Texture2D* pTexture = nullptr;

	pDevice->CreateTexture2D(&desc,&initData,&pTexture);

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;

	ID3D11ShaderResourceView* pSRV;
	pDevice->CreateShaderResourceView(pTexture,&SRVDesc,&pSRV);

	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* pSampler = nullptr;
	pDevice->CreateSamplerState(&samplerDesc,&pSampler);

	Texture* pMyDXTexture = new Texture(pTexture,pSRV,pSampler);

	this->textures_[pMyDXTexture] = image;

	return pMyDXTexture;

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

	for (auto pair : this->textures_) {

		Texture* tex = pair.first;

		tex->GetTexture()->Release();
		tex->GetSRV()->Release();
		tex->GetSamplerState()->Release();

		delete tex;

		Image* image = pair.second;
		delete image;

	}

	this->textures_.clear();

	SafeRelease(this->pBlendState_);
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

void Graphics::ScreenSwap() {

	IDXGISwapChain* pSwapChain = DX11_DEVICE.GetSwapChain();
	pSwapChain->Present(0, 0);

}