#include "Square.h"
#include "VertexBuffer/VertexBuffer.h"

using namespace MyDirectX11;

Square::Square(float sizeX, float sizeY) {

	this->pVertexBuffer_ = nullptr;
	this->sizeX_ = sizeX;
	this->sizeY_ = sizeY;

}

Square::~Square() {

	this->pVertexBuffer_->GetDX11Buffer()->Release();
	delete this->pVertexBuffer_;

}

void Square::Initialize(ID3D11Device* pDevice) {

	//::ZeroMemory(this->vertexs_,sizeof(VertexData) * 6);

	this->pos_.x = 0.0f;
	this->pos_.y = 0.0f;
	this->pos_.z = 0.0f;
	
	Vector3 vertexPos = this->pos_;

	this->vertexs_[0] = VertexData(vertexPos, Color(1.0f, 1.0f, 1.0f, 1.0f));

	vertexPos.x += this->sizeX_;
	this->vertexs_[1] = VertexData(vertexPos, Color(1.0f, 1.0f, 1.0f, 1.0f));

	vertexPos.y += this->sizeY_;
	this->vertexs_[2] = VertexData(vertexPos, Color(1.0f, 1.0f, 1.0f, 1.0f));

	this->vertexs_[3] = this->vertexs_[2];
	
	vertexPos.x -= this->sizeX_;
	this->vertexs_[4] = VertexData(vertexPos, Color(1.0f, 1.0f, 1.0f, 1.0f));
	this->vertexs_[5] = this->vertexs_[0];

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(VertexData) * 6;
	bufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = this->vertexs_;
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	ID3D11Buffer* pVertexBuffer;
	HRESULT hr = pDevice->CreateBuffer(&bufferDesc, &subResourceData, &pVertexBuffer);

	this->pVertexBuffer_ = new CVertexBuffer(pVertexBuffer);

}

void Square::Draw(ID3D11DeviceContext* pDeviceContext) {

	Vector3 vertexPos = this->pos_;

	this->vertexs_[0] = VertexData(vertexPos, Color(1.0f, 1.0f, 1.0f, 1.0f));

	vertexPos.x += this->sizeX_;
	this->vertexs_[1] = VertexData(vertexPos, Color(1.0f, 1.0f, 1.0f, 1.0f));

	vertexPos.y += this->sizeY_;
	this->vertexs_[2] = VertexData(vertexPos, Color(1.0f, 1.0f, 1.0f, 1.0f));

	this->vertexs_[3] = this->vertexs_[2];

	vertexPos.x -= this->sizeX_;
	this->vertexs_[4] = VertexData(vertexPos, Color(1.0f, 1.0f, 1.0f, 1.0f));
	this->vertexs_[5] = this->vertexs_[0];

	ID3D11Buffer* pDX11Buffer = this->pVertexBuffer_->GetDX11Buffer();

	pDeviceContext->UpdateSubresource(pDX11Buffer, 0, NULL, this->vertexs_, 0, 0);

	UINT stride = sizeof(VertexData);
	UINT offsets = 0;

	pDeviceContext->IASetVertexBuffers(0,1, &pDX11Buffer, &stride , &offsets);
	pDeviceContext->Draw(6, 0);

}