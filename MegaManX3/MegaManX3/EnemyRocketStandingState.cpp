#include "EnemyRocketStandingState.h"
#include "EnemyRocket.h"
#include "EnemyRocketAttack1State.h"


EnemyRocketStandingState::EnemyRocketStandingState()
{
}

EnemyRocketStandingState::EnemyRocketStandingState(EnemyRocketData * enemyOneGunData)
{
	this->enemyRocketData = enemyOneGunData;
	this->enemyRocketData->m_EnemyRocket->SetVy(0);
	this->enemyRocketData->m_EnemyRocket->SetVx(0);
	this->enemyRocketData->m_EnemyRocket->SetAy(0);
	this->enemyRocketData->m_EnemyRocket->SetAx(0);
	this->enemyRocketData->m_EnemyRocket->listAnimation[EnemyRocketStates::ENEMYROCKETSTANDING].SetIndex(0);
}

void EnemyRocketStandingState::Update(double time)
{
	if (this->enemyRocketData->m_EnemyRocket->rocket->GetIsDead()&&
		this->enemyRocketData->m_EnemyRocket->listAnimation[EnemyRocketStates::ENEMYROCKETSTANDING].GetIndex()>0)
	{
		this->enemyRocketData->m_EnemyRocket->SetState(new EnemyRocketAttack1State(enemyRocketData));
	}

}

void EnemyRocketStandingState::HandleKeyboard(std::map<int, bool> keys)
{

}

EnemyRocketStates EnemyRocketStandingState::GetState()
{
	return EnemyRocketStates::ENEMYROCKETSTANDING;
}

void EnemyRocketStandingState::OnCollision()
{
	
}

EnemyRocketStandingState::~EnemyRocketStandingState()
{
}
