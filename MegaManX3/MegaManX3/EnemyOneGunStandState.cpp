#include "EnemyOneGunStandState.h"
#include "EnemyOneGun.h"
#include "MegaManCharacters.h"
#include "EnemyOneGunAttack1State.h"
#include "EnemyOneGunAttack2State.h"
#include "EnemyOneGunJumpState.h"


EnemyOneGunStandState::EnemyOneGunStandState()
{
}

EnemyOneGunStandState::EnemyOneGunStandState(EnemyOneGunData * enemyOneGunData)
{
	this->enemyOneGunData = enemyOneGunData;
	this->enemyOneGunData->m_EnemyOneGun->SetVy(0);
	this->enemyOneGunData->m_EnemyOneGun->SetVx(0);
	this->enemyOneGunData->m_EnemyOneGun->SetAy(0);
	this->enemyOneGunData->m_EnemyOneGun->SetAx(0);
	if (this->enemyOneGunData->m_EnemyOneGunState->GetState() == OneGunStates::ENEMYJUMPING)
		this->enemyOneGunData->m_EnemyOneGun->listAnimation[OneGunStates::ENEMYSTANDING].SetIndex(0);
	else if (this->enemyOneGunData->m_EnemyOneGunState->GetState() == OneGunStates::ENEMYATTACK1)
		this->enemyOneGunData->m_EnemyOneGun->listAnimation[OneGunStates::ENEMYSTANDING].SetIndex(6);
	else if (this->enemyOneGunData->m_EnemyOneGunState->GetState() == OneGunStates::ENEMYATTACK2)
		this->enemyOneGunData->m_EnemyOneGun->listAnimation[OneGunStates::ENEMYSTANDING].SetIndex(4);
}

void EnemyOneGunStandState::Update(double time)
{

	if (abs(this->enemyOneGunData->m_EnemyOneGun->GetPosition().x - MegaManCharacters::GetInstance()->GetPosition().x) <= 200)
	{
		if (this->enemyOneGunData->m_EnemyOneGun->listAnimation[OneGunStates::ENEMYSTANDING].GetIndex() == 1)
			this->enemyOneGunData->m_EnemyOneGun->SetState(new EnemyOneGunAttack2State(this->enemyOneGunData));
	}
	else if (abs(this->enemyOneGunData->m_EnemyOneGun->GetPosition().x - MegaManCharacters::GetInstance()->GetPosition().x) <= 400)
	{
		if (this->enemyOneGunData->m_EnemyOneGun->listAnimation[OneGunStates::ENEMYSTANDING].GetIndex() ==  3)
			this->enemyOneGunData->m_EnemyOneGun->SetState(new EnemyOneGunAttack1State(this->enemyOneGunData));
	}
	if (this->enemyOneGunData->m_EnemyOneGun->listAnimation[OneGunStates::ENEMYSTANDING].GetIndex() == 7)
		this->enemyOneGunData->m_EnemyOneGun->SetState(new EnemyOneGunJumpState(this->enemyOneGunData));

}

void EnemyOneGunStandState::HandleKeyboard(std::map<int, bool> keys)
{

}

OneGunStates EnemyOneGunStandState::GetState()
{
	return OneGunStates::ENEMYSTANDING;
}

void EnemyOneGunStandState::OnCollision()
{
	this->enemyOneGunData->m_EnemyOneGun->SetVx(0);
}

EnemyOneGunStandState::~EnemyOneGunStandState()
{
}
