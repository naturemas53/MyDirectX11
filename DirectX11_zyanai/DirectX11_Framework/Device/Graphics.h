#pragma once
#include <d3d11.h>

namespace MyDirectX11 {

	class Graphics final {

	public:

		static Graphics& GetInstance() {

			static Graphics instance;
			return instance;

		}
		~Graphics();

		bool Initialize();
		void Release();

		void Render();


		inline void SafeRelease(IUnknown* pointer) { 
			
			if (pointer == nullptr) return;

				pointer->Release();
				pointer = nullptr;

		}

	private:

		Graphics();

		//�`�悷��|���S���f�[�^�Ƃ��̃f�[�^�̌`��
		ID3D11Buffer*			pVertexBuffer_;
		ID3D11InputLayout*		pInputLayout_;

		//�V�F�[�_�[�֘A(���ݎ����Ă����)
		ID3D11VertexShader*		pVertexShader_;
		ID3D11PixelShader*		pPixelShader_;

		//�萔�o�b�t�@
		ID3D11Buffer* pConstantBuffer_;

		//�r���[�|�[�g
		D3D11_VIEWPORT			viewport_;
		
		//���̑��������@�����o�b�N�o�b�t�@�֘A
		ID3D11RenderTargetView* pRenderTargetView_;
		ID3D11Texture2D*		pDepthStencil_;
		ID3D11DepthStencilView* pDepthStencilView_;


	};

}

#define DX11_GRAPHIC MyDirectX11::Graphics::GetInstance()