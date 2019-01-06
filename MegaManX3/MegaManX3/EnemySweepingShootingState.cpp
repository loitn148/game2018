#include "EnemySweepingShootingState.h"
#include "EnemySweepingNormalState.h"
#include "EnemySweeping.h"

EnemySweepingShootingState::EnemySweepingShootingState()
{
}

EnemySweepingShootingState::EnemySweepingShootingState(EnemySweepingData * enemyOneGunData)
{
	this->enemySweepingData = enemyOneGunData;
	this->enemySweepingData->enemySweeping->SetVy(0);
	this->enemySweepingData->enemySweeping->SetVx(0);
	this->enemySweepingData->enemySweeping->SetAy(0);
	this->enemySweepingData->enemySweeping->SetAx(0);
	this->enemySweepingData->enemySweeping->listAnimation[ENEMYSWEEPINGSHOOTING].SetIndex(0);
}

void EnemySweepingShootingState::Update(double time)
{
	if (this->enemySweepingData->enemySweeping->rocket == NULL)
	{
		this->enemySweepingData->enemySweeping->rocket = new RocketEnemy3(VT3(this->enemySweepingData->enemySweeping->GetPosition().x, this->enemySweepingData->enemySweeping->GetPosition().y, 0),
			500 * this->enemySweepingData->enemySweeping->GetDirect(),
			this->enemySweepingData->enemySweeping->GetDirect());
	}
	if (this->enemySweepingData->enemySweeping->listAnimation[ENEMYSWEEPINGSHOOTING].GetIndex() == (this->enemySweepingData->enemySweeping->listAnimation[ENEMYSWEEPINGSHOOTING].GetTotalFrame() - 1))
	{
		this->enemySweepingData->enemySweeping->SetState(new EnemySweepingNormalState(this->enemySweepingData));

	}

}

void EnemySweepingShootingState::HandleKeyboard(std::map<int, bool> keys)
{

}

EnemySweepingStates EnemySweepingShootingState::GetState()
{
	return EnemySweepingStates::ENEMYSWEEPINGSHOOTING;
}

void EnemySweepingShootingState::OnCollision()
{

}

EnemySweepingShootingState::~EnemySweepingShootingState()
{
}
