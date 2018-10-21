#pragma once
#ifndef __SCENEMANAGER__H__
#define __SCENEMANAGER__H__

#include "GameScene.h"

class SceneManager
{
private:
	static SceneManager* instance;
	GameScene* currentScene;
public:
	static SceneManager* GetInstance();
	void Update(double time);
	GameScene* GetCurrentScene();
	void ReplaceScene(GameScene* Scene);

	SceneManager();
	~SceneManager();
};
#endif // !__SCENEMANAGER__H__