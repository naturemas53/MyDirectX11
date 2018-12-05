#pragma once
#include <Windows.h>
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")

namespace MyDirectX11 {

	class Device final {

	public:

		~Device();

		static Device& GetInstance() {

			static Device instance;
			return instance;

		}

		bool Initialize(HWND hwnd);
		void Release();

		ID3D11Device*		 GetDevice()		{ return pDevice_;		  }
		ID3D11DeviceContext* GetDeviceContext() { return pDeviceContext_; }
		IDXGISwapChain*		 GetSwapChain()		{ return pSwapChain_;	  }
		HWND				 GetHWnd()			{ return this->hWnd_;	  }

	private:

		Device();

		D3D_FEATURE_LEVEL	 level_;
		ID3D11Device*		 pDevice_;

		ID3D11DeviceContext* pDeviceContext_;

		IDXGIDevice1* pDXGI_;

		IDXGIAdapter* pAdapter_;

		IDXGIFactory* pFactory_;

		IDXGISwapChain* pSwapChain_;

		HWND hWnd_;

	};

}

#define DX11_DEVICE MyDirectX11::Device::GetInstance()