#pragma once
#include <d3d11.h>
#include <list>

namespace MyDirectX11 {

	class CVertexBuffer;
	class CVertexShader;
	class CPixelShader;
	class ShaderParamater;

	class Graphics final {

	public:

		static Graphics& GetInstance() {

			static Graphics instance;
			return instance;

		}
		~Graphics();

		bool Initialize();
		void Release();

		void Clear();

		void ScreenSwap();

		//CVertexBuffer* CreateVertexBuffer();

		CVertexShader* CreateVertexShader(void* shaderCode, size_t shaderSize,
										 D3D11_INPUT_ELEMENT_DESC* elementDescs = nullptr,int elementDescCount = 0);

		CPixelShader*  CreatePixelShader (void* shaderCode, size_t shaderSize,
										 D3D11_INPUT_ELEMENT_DESC* elementDescs = nullptr, int elementDescCount = 0);

		ShaderParamater* CreateShaderParamater(size_t paramaterSize);

		inline void SafeRelease(IUnknown* pointer) { 
			
			if (pointer == nullptr) return;

				pointer->Release();
				pointer = nullptr;

		}

	private:

		Graphics();

		//ビューポート
		D3D11_VIEWPORT			viewport_;
		
		//その他もろもろ　多分バックバッファ関連
		ID3D11RenderTargetView* pRenderTargetView_;
		ID3D11Texture2D*		pDepthStencil_;
		ID3D11DepthStencilView* pDepthStencilView_;

		std::list<CVertexBuffer*>	vertexBuffers_;
		std::list<CVertexShader*>	vertexShaders_;
		std::list<CPixelShader*>	pixelShaders_;
		std::list<ShaderParamater*> shaderParamaters_;

	};

}

#define DX11_GRAPHIC MyDirectX11::Graphics::GetInstance()