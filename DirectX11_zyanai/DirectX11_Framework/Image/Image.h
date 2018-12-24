#pragma once

namespace MyDirectX11 {

	class Image {

	public:

		Image() {}
		virtual ~Image() {}

		virtual void* GetData()		   = 0;
		virtual int	  GetWidth()	   = 0;
		virtual int   GetHeight()	   = 0;
		virtual int   GetPixelSize()   = 0;
		virtual int   GetWidthStride() = 0;
		virtual int   GetSize()	   = 0;

	};

}