#pragma once

namespace MyDirectX11 {

	class IScene;

	class SceneContext final {

	public:

		static SceneContext& GetInstance() {

			static SceneContext instance;
			return instance;

		}

		~SceneContext();

		void SetScene(IScene* scene_);
		void Update();

	private:

		SceneContext();

		IScene* currentScene_;

	};

}

#define SCENEMANAGER MyDirectX11::SceneContext::GetInstance()