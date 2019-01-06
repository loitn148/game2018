#include "EnemySweepingNormalState.h"
#include "EnemySweepingShootingState.h"
#include "EnemySweeping.h"


EnemySweepingNormalState::EnemySweepingNormalState()
{
}

EnemySweepingNormalState::EnemySweepingNormalState(EnemySweepingData * enemyOneGunData)
{
	this->enemySweepingData = enemyOneGunData;
	this->enemySweepingData->enemySweeping->SetVy(-100);
	this->enemySweepingData->enemySweeping->SetVx(0);
	this->enemySweepingData->enemySweeping->SetAy(-30);
	this->enemySweepingData->enemySweeping->SetAx(0);
	MoveTimes = 0;
	Term = true;
	this->enemySweepingData->enemySweeping->listAnimation[ENEMYSWEEPINGNORMAL].SetIndex(0);
	if (this->enemySweepingData->enemySweeping->GetPosition().y < this->enemySweepingData->enemySweeping->oldPosition.y - 100)
	{
		this->enemySweepingData->enemySweeping->SetVy(-this->enemySweepingData->enemySweeping->GetVy());
		this->enemySweepingData->enemySweeping->SetVx(-this->enemySweepingData->enemySweeping->GetVx());
		this->enemySweepingData->enemySweeping->SetAy(30);

	}
}

void EnemySweepingNormalState::Update(double time)
{
	if (this->enemySweepingData->enemySweeping->GetPosition().y < this->enemySweepingData->enemySweeping->oldPosition.y - 100
		&& !Term)
	{
		this->enemySweepingData->enemySweeping->SetVy(-this->enemySweepingData->enemySweeping->GetVy());
		this->enemySweepingData->enemySweeping->SetVx(-this->enemySweepingData->enemySweeping->GetVx());
		if (this->enemySweepingData->enemySweeping->rocket == NULL)
		{
			MoveTimes++;
		}
	}
	if (MoveTimes>2)
	{
		this->enemySweepingData->enemySweeping->SetState(new EnemySweepingShootingState(enemySweepingData));
	}
	if (this->enemySweepingData->enemySweeping->GetPosition().y >= this->enemySweepingData->enemySweeping->oldPosition.y - 50)
	{
		this->enemySweepingData->enemySweeping->SetAy(-30);
		Term = false;
	}

}

void EnemySweepingNormalState::HandleKeyboard(std::map<int, bool> keys)
{

}

EnemySweepingStates EnemySweepingNormalState::GetState()
{
	return EnemySweepingStates::ENEMYSWEEPINGNORMAL;
}

void EnemySweepingNormalState::OnCollision()
{

}

EnemySweepingNormalState::~EnemySweepingNormalState()
{
}
