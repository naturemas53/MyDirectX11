#include "Device.h"

using namespace MyDirectX11;

inline static bool SafeRelease(IUnknown* pObject) {

	if (!pObject) return false;

	pObject->Release();
	pObject = nullptr;

	return true;

}

Device::Device() {

	this->pDevice_		  = nullptr;
	this->pDeviceContext_ = nullptr;
	this->pDXGI_		  = nullptr;
	this->pAdapter_		  = nullptr;
	this->pFactory_		  = nullptr;
	this->pSwapChain_	  = nullptr;

	this->hWnd_ = NULL;

}

Device::~Device() {

	this->Release();

}

bool Device::Initialize(HWND hwnd) {

	this->Release();

	this->hWnd_ = hwnd;

	HRESULT hr = 0;
	hr = D3D11CreateDevice(NULL,
								   D3D_DRIVER_TYPE_HARDWARE,
								   NULL,
								   0,
								   NULL,0, 
								   D3D11_SDK_VERSION,
								   &pDevice_,
								   &level_,
								   &pDeviceContext_);

	if (FAILED(hr)) {

		MessageBox(hwnd, L"D3D11CreateDevice", L"Error", MB_ICONSTOP);
		return false;

	}

	hr = pDevice_->QueryInterface(__uuidof(IDXGIDevice1),(void**)&pDXGI_);
	if (FAILED(hr)) {

		MessageBox(hwnd, L"QueryInterface (ID3D11Device -> IDXGIDevice1)", L"Error", MB_ICONSTOP);
		return false;

	}

	hr = pDXGI_->GetAdapter(&pAdapter_);
	if (FAILED(hr)) {

		MessageBox(hwnd, L"GetAdapter", L"Error", MB_ICONSTOP);
		return false;

	}

	hr = pAdapter_->GetParent(__uuidof(IDXGIFactory),(void**)&pFactory_);
	if (FAILED(hr)) {

		MessageBox(hwnd, L"GetParent( IDXGIAdapter -> IDXGIFactory )", L"Error", MB_ICONSTOP);
		return false;

	}

	hr = pFactory_->MakeWindowAssociation(hwnd,0);
	if (FAILED(hr)) {

		MessageBox(hwnd, L"MakeWindowAssociation", L"Error", MB_ICONSTOP);
		return false;

	}

	DXGI_SWAP_CHAIN_DESC hDXGISwapChainDesc;
	memset(&hDXGISwapChainDesc, 0, sizeof(DXGI_SWAP_CHAIN_DESC));
	hDXGISwapChainDesc.BufferDesc.Width = 1280;
	hDXGISwapChainDesc.BufferDesc.Height = 720;
	hDXGISwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	hDXGISwapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	hDXGISwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	hDXGISwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	hDXGISwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
	hDXGISwapChainDesc.SampleDesc.Count = 1;
	hDXGISwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	hDXGISwapChainDesc.BufferCount = 1;
	hDXGISwapChainDesc.OutputWindow = hwnd;
	hDXGISwapChainDesc.Windowed = TRUE;
	hDXGISwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	hDXGISwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	hr = pFactory_->CreateSwapChain(pDevice_,&hDXGISwapChainDesc,&pSwapChain_);
	if (FAILED(hr)) {

		MessageBox(hwnd, L"CreateSwapChain", L"Error", MB_ICONSTOP);
		return false;

	}

	return true;

}

void Device::Release() {

	SafeRelease(pSwapChain_);
	this->pSwapChain_ = nullptr;

	SafeRelease(pFactory_);
	this->pFactory_ = nullptr;

	SafeRelease(pAdapter_);
	this->pAdapter_ = nullptr;

	SafeRelease(pDXGI_);
	this->pDXGI_ = nullptr;

	SafeRelease(pDeviceContext_);
	this->pDeviceContext_ = nullptr;

	SafeRelease(pDevice_);
	this->pDevice_ = nullptr;

}