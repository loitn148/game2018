#include "BossFinalCallEnemies.h"
#include "BossFinal.h"


BossFinalCallEnemies::BossFinalCallEnemies(BossFinalData *bossFinalData)
{
	this->bossFinalData = bossFinalData;
	listAnimation = this->bossFinalData->bossFinal->GetListAnimation();
	listAnimation[CALL_ENEMIES].SetIndex(0);
	this->positionMegan = this->bossFinalData->bossFinal->megaMan->GetInstance()->GetPosition();
	this->bossFinalData->bossFinal->SetVy(0);
	this->bossFinalData->bossFinal->SetVx(0);
	this->bossFinalData->bossFinal->isJustPrick = false;
	if (this->positionMegan.x > this->bossFinalData->bossFinal->GetPosition().x)
	{
		this->bossFinalData->bossFinal->SetDirect(RIGHT);
	}
	else
	{
		this->bossFinalData->bossFinal->SetDirect(LEFT);
	}
}

BigBossStates BossFinalCallEnemies::GetState()
{
	return CALL_ENEMIES;
}

void BossFinalCallEnemies::Update(double time) {
	if (this->listAnimation[this->bossFinalData->bossFinal->currentState].GetIndex() == 4)
	{
		//this->bossFinalData->bossFinal->CallEnemy();
	}
}

BossFinalCallEnemies::~BossFinalCallEnemies()
{
}
