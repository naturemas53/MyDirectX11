#pragma once
#include <d3d11.h>

namespace MyDirectX11 {

	struct Vector3 {

		Vector3() {};
		Vector3(float x,float y,float z) {

			this->x = x;
			this->y = y;
			this->z = z;

		}

		MyDirectX11::Vector3& operator +(const MyDirectX11::Vector3 aite) {

			this->x += aite.x;
			this->y += aite.y;
			this->z += aite.z;

			return *this;

		}

		MyDirectX11::Vector3& operator +=(const MyDirectX11::Vector3 aite) {

			return operator+(aite);

		}

		float x = 0;
		float y = 0;
		float z = 0;

	};


	struct Vector2 {

		Vector2() {};
		Vector2(float x, float y) {

			this->x = x;
			this->y = y;

		}

		MyDirectX11::Vector2& operator +(const MyDirectX11::Vector2 aite) {

			this->x += aite.x;
			this->y += aite.y;

			return *this;

		}

		MyDirectX11::Vector2& operator +=(const MyDirectX11::Vector2 aite) {

			return operator+(aite);

		}

		float x = 0;
		float y = 0;

	};

	struct Color {

		Color() {};
		Color(float r, float g, float b, float a) {

			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;

		}

		float r = 0;
		float g = 0;
		float b = 0;
		float a = 0;

	};

	struct VertexData {

		VertexData(Vector3 pos ,Vector2 uv) {

			this->pos_[0] = pos.x;
			this->pos_[1] = pos.y;
			this->pos_[2] = pos.z;

			this->uv_[0] = uv.x;
			this->uv_[1] = uv.y;

		}

		VertexData() {

			this->pos_[0] = 0;
			this->pos_[1] = 0;
			this->pos_[2] = 0;

			this->uv_[0] = 0;
			this->uv_[1] = 0;

		}

		static void GetElementDescs(D3D11_INPUT_ELEMENT_DESC** pOutDescs,int* descCount) {

			static D3D11_INPUT_ELEMENT_DESC elementDescs[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,							   0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT   ,	 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};

			*pOutDescs = elementDescs;
			*descCount = 2;

		}

		float pos_[3] = {};
		float uv_[2] = {};

	};

}

#define Vector3_Zero MyDirectX11::Vector3(0.0f,0.0f,0.0f)