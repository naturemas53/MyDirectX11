#pragma once
#include <d3d11.h>
#include "VertexData.h"

namespace MyDirectX11 {

	class IVertexBuffer {

	public:

		IVertexBuffer() {}
		virtual ~IVertexBuffer() {}

		virtual D3D11_MAPPED_SUBRESOURCE Map(ID3D11DeviceContext* pDeviceContext)   = 0;
		virtual void					 UnMap(ID3D11DeviceContext* pDeviceContext) = 0;

		virtual ID3D11Buffer*	   GetDX11Buffer()		= 0;

		virtual bool IsNull() = 0;

	};

	class CVertexBuffer final : public IVertexBuffer {

	public:

		CVertexBuffer(ID3D11Buffer* pVertexBuffer);
		virtual ~CVertexBuffer();

		virtual D3D11_MAPPED_SUBRESOURCE Map(ID3D11DeviceContext* pDeviceContext);
		virtual void					 UnMap(ID3D11DeviceContext* pDeviceContext);

		virtual ID3D11Buffer* GetDX11Buffer() { return this->pVertexBuffer_; }

		virtual bool IsNull() { return false; }

	private:

		ID3D11Buffer*	   pVertexBuffer_;

	};

	class CNullVertexBuffer : public IVertexBuffer {

	public:

		CNullVertexBuffer() {}
		virtual ~CNullVertexBuffer() {}

		virtual D3D11_MAPPED_SUBRESOURCE Map(ID3D11DeviceContext* pDeviceContext) { return D3D11_MAPPED_SUBRESOURCE(); }
		virtual void					 UnMap(ID3D11DeviceContext* pDeviceContext) { }

		virtual ID3D11Buffer*	   GetDX11Buffer() { return nullptr; }

		virtual bool IsNull() { return true; }

	};

}