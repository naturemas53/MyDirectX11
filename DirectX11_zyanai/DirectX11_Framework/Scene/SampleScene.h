#pragma once
#include "IScene.h"

namespace MyDirectX11 {

	class Square;
	class CVertexShader;
	class CPixelShader;
	class ShaderParamater;

	class SampleScene final : public IScene{

	public:

		SampleScene() {};
		virtual ~SampleScene() {};

	    virtual bool Initialize() override;
		virtual void Finalize()   override;
		virtual void Update()     override;
		virtual void Draw ()	  override;

	private:

		Square* square_;
		CVertexShader*   vertexShader_;
		CPixelShader*    pixelShader_;
		ShaderParamater* shaderParamater_;

	};

}