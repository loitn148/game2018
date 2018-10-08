#include "SenceManager.h"



SenceManager::SenceManager() {
}


SenceManager::~SenceManager() {
}

SenceManager * SenceManager::instance = 0;
SenceManager * SenceManager::GetInstance() {
	if (!SenceManager::instance)
	{
		SenceManager::instance = new SenceManager();
	}
	return SenceManager::instance;
}

void SenceManager::Update(double time) {
	this->currentSence->Update(time);
}

GameSence * SenceManager::GetCurrentSence() {
	return this->currentSence;
}

void SenceManager::ReplaceSence(GameSence * sence)
{
	if (this->currentSence)
		delete(this->currentSence);
	this->currentSence = sence;
}