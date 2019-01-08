#include "BossFinalStartState.h"
#include "BossFinal.h"

BossFinalStartState::BossFinalStartState(BossFinalData *bossFinalData)
{
	this->bossFinalData = bossFinalData;
	listAnimation = this->bossFinalData->bossFinal->GetListAnimation();
	listAnimation[START].SetIndex(0);
	this->bossFinalData->bossFinal->isPrick = false;
	//this->bossFinalData->bossFinal->isCallEnemies = false;
	if (this->bossFinalData->bossFinal->isJustPrick)
	{
		if (this->bossFinalData->bossFinal->GetPosition().x < this->bossFinalData->bossFinal->megaMan->GetInstance()->GetPosition().x)
		{
			this->bossFinalData->bossFinal->SetDirect(RIGHT);
			this->bossFinalData->bossFinal->SetVy(200);
			this->bossFinalData->bossFinal->SetVx(abs(500 - this->bossFinalData->bossFinal->GetPosition().x) / abs(2600 - this->bossFinalData->bossFinal->GetPosition().y) * this->bossFinalData->bossFinal->GetVy());
		}
		else
		{
			this->bossFinalData->bossFinal->SetDirect(LEFT);
			this->bossFinalData->bossFinal->SetVy(200);
			this->bossFinalData->bossFinal->SetVx(- abs(100 - this->bossFinalData->bossFinal->GetPosition().x) / abs(2600 - this->bossFinalData->bossFinal->GetPosition().y) * this->bossFinalData->bossFinal->GetVy());
		}

	}
	else
	{
		this->bossFinalData->bossFinal->SetVy(-500);
	}
}

BigBossStates BossFinalStartState::GetState()
{
	return START;
}

void BossFinalStartState::Update(double time) {
	
}

BossFinalStartState::~BossFinalStartState()
{
}
