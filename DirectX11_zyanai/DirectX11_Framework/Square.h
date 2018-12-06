#pragma once
#include "VertexBuffer/VertexData.h"
#include <d3d11.h>

namespace MyDirectX11 {

	class CVertexBuffer;

	class Square final{

	public:

		Square(float sizeX , float sizeY);
		~Square();

		void Initialize(ID3D11Device* pDevice);
		
		void SetPosition(Vector3 pos) { this->pos_ = pos; }
		Vector3 GetPosision() { return this->pos_; }

		void Draw(ID3D11DeviceContext* pDeviceContext);

	private:

		Vector3 pos_;

		float sizeX_;
		float sizeY_;

		VertexData vertexs_[6];

		CVertexBuffer* pVertexBuffer_;

	};

}