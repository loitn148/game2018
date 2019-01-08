#include "BossFinalPrickState.h"
#include "BossFinal.h"
#include <cmath>


BossFinalPrickState::BossFinalPrickState(BossFinalData *bossFinalData)
{
	this->bossFinalData = bossFinalData;
	listAnimation = this->bossFinalData->bossFinal->GetListAnimation();
	listAnimation[PRICK].SetIndex(0);
	this->positionMegan = this->bossFinalData->bossFinal->megaMan->GetInstance()->GetPosition();
	this->bossFinalData->bossFinal->SetVy(0);
	this->bossFinalData->bossFinal->SetVx(0);
	//this->bossFinalData->bossFinal->isCallEnemies = false;
	this->bossFinalData->bossFinal->isPrick = true;
	if (this->positionMegan.x > this->bossFinalData->bossFinal->GetPosition().x)
	{
		this->bossFinalData->bossFinal->SetDirect(RIGHT);
	}
	else
	{
		this->bossFinalData->bossFinal->SetDirect(LEFT);
	}
	this->angleAttack = abs(this->bossFinalData->bossFinal->GetPosition().x - this->positionMegan.x) / abs(this->bossFinalData->bossFinal->GetPosition().y - this->positionMegan.y);
}

BigBossStates BossFinalPrickState::GetState()
{
	return PRICK;
}

void BossFinalPrickState::Update(double time) {
	if (this->listAnimation[PRICK].GetIndex() == 6) {
		this->listAnimation[PRICK].SetIndex(5);

		this->bossFinalData->bossFinal->SetVy(-500);
		this->bossFinalData->bossFinal->SetVx(this->bossFinalData->bossFinal->GetDirect() * this->angleAttack * abs(this->bossFinalData->bossFinal->GetVy()));
	}

	if (this->bossFinalData->bossFinal->GetPosition().y < this->positionMegan.y)
	{
		this->bossFinalData->bossFinal->isJustPrick = true;
	}
}

BossFinalPrickState::~BossFinalPrickState()
{
}
