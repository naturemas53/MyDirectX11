#include "SceneContext.h"
#include "IScene.h"
#include <time.h>
#include <Windows.h>

using namespace MyDirectX11;

SceneContext::SceneContext() {

	this->currentScene_ = nullptr;

}

SceneContext::~SceneContext() {

	if (this->currentScene_ != nullptr)
		delete this->currentScene_;

}

void SceneContext::SetScene(IScene* scene) {

	if (this->currentScene_ != nullptr) {
		this->currentScene_->Finalize();
		delete this->currentScene_;
	}

	this->currentScene_ = scene;
	scene->Initialize();

}

void SceneContext::Update() {

	static long prevTime = clock();

	this->currentScene_->Proc();

	long nowTime = clock();

	long duration = nowTime - prevTime;

	long frameMilliTime = (long)(1.0f / 60.0f * 1000.0f);

	if (duration < frameMilliTime) {

		long sleepTime = frameMilliTime - duration;
		Sleep(sleepTime);

	}

	prevTime = clock();

}