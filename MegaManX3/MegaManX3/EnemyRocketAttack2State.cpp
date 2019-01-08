#include "EnemyRocketAttack2State.h"
#include "EnemyRocket.h"


EnemyRocketAttack2State::EnemyRocketAttack2State()
{
}

EnemyRocketAttack2State::EnemyRocketAttack2State(EnemyRocketData * enemyOneGunData)
{
	this->enemyRocketData = enemyOneGunData;
	this->enemyRocketData->m_EnemyRocket->SetVy(0);
	this->enemyRocketData->m_EnemyRocket->SetVx(0);
	this->enemyRocketData->m_EnemyRocket->SetAy(0);
	this->enemyRocketData->m_EnemyRocket->SetAx(0);
	this->enemyRocketData->m_EnemyRocket->listAnimation[EnemyRocketStates::ENEMYROCKETSTANDING].SetIndex(0);
}

void EnemyRocketAttack2State::Update(double time)
{


}

void EnemyRocketAttack2State::HandleKeyboard(std::map<int, bool> keys)
{

}

EnemyRocketStates EnemyRocketAttack2State::GetState()
{
	return EnemyRocketStates::ENEMYROCKETSTANDING;
}

void EnemyRocketAttack2State::OnCollision()
{

}

EnemyRocketAttack2State::~EnemyRocketAttack2State()
{
}
