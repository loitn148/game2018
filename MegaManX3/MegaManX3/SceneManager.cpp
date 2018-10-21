#include "SceneManager.h"



SceneManager::SceneManager() {
}


SceneManager::~SceneManager() {
}

SceneManager * SceneManager::instance = 0;
SceneManager * SceneManager::GetInstance() {
	if (!SceneManager::instance)
	{
		SceneManager::instance = new SceneManager();
	}
	return SceneManager::instance;
}

void SceneManager::Update(double time) {
	this->currentScene->Update(time);
}

GameScene * SceneManager::GetCurrentScene() {
	return this->currentScene;
}

void SceneManager::ReplaceScene(GameScene * Scene)
{
	if (this->currentScene)
		delete(this->currentScene);
	this->currentScene = Scene;
}