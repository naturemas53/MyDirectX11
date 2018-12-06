#include "VertexBuffer.h"

using namespace MyDirectX11;

CVertexBuffer::CVertexBuffer(ID3D11Buffer* pVertexBuffer) {

	this->pVertexBuffer_ = pVertexBuffer;

}

CVertexBuffer::~CVertexBuffer() {



}

D3D11_MAPPED_SUBRESOURCE CVertexBuffer::Map(ID3D11DeviceContext* pDeviceContext) {

	D3D11_MAPPED_SUBRESOURCE vertexResource;
	ZeroMemory(&vertexResource,sizeof(D3D11_MAPPED_SUBRESOURCE));

	pDeviceContext->Map(this->pVertexBuffer_,0, D3D11_MAP_READ_WRITE,0,&vertexResource);

	return vertexResource;

}

void CVertexBuffer::UnMap(ID3D11DeviceContext* pDeviceContext) {

	pDeviceContext->Unmap(this->pVertexBuffer_, 0);

}