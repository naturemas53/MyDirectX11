#pragma once

namespace MyDirectX11 {

	class IScene {

	public:

		IScene() {}
		virtual ~IScene() {}

		void Proc() {

			this->Draw();
			this->Update();

		}

		virtual bool Initialize() = 0;
		virtual void Finalize() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;

	};

}