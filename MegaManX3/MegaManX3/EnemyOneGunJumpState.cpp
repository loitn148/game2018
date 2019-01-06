#include "EnemyOneGunJumpState.h"
#include "EnemyOneGun.h"
#include "MegaManCharacters.h"


EnemyOneGunJumpState::EnemyOneGunJumpState()
{
}

EnemyOneGunJumpState::EnemyOneGunJumpState(EnemyOneGunData * enemyOneGunData)
{
	this->enemyOneGunData = enemyOneGunData;
	this->enemyOneGunData->m_EnemyOneGun->SetVy(1100);
	this->enemyOneGunData->m_EnemyOneGun->SetAy(-200);
	this->enemyOneGunData->m_EnemyOneGun->listAnimation[OneGunStates::ENEMYJUMPING].SetIndex(0);
	if (this->enemyOneGunData->m_EnemyOneGun->GetPosition().x > MegaManCharacters::GetInstance()->GetPosition().x)
	{
		this->enemyOneGunData->m_EnemyOneGun->SetDirect(Direct::LEFT);
		this->enemyOneGunData->m_EnemyOneGun->SetVx(-600);
	}
	else
	{
		this->enemyOneGunData->m_EnemyOneGun->SetDirect(Direct::RIGHT);
		this->enemyOneGunData->m_EnemyOneGun->SetVx(600);

	}
}

void EnemyOneGunJumpState::Update(double time)
{
	if (this->enemyOneGunData->m_EnemyOneGun->GetVy() != 0 && this->enemyOneGunData->m_EnemyOneGun->listAnimation[OneGunStates::ENEMYJUMPING].GetIndex() == 4) {
		this->enemyOneGunData->m_EnemyOneGun->listAnimation[0].SetIndex(3);
	}

}

void EnemyOneGunJumpState::HandleKeyboard(std::map<int, bool> keys)
{

}

OneGunStates EnemyOneGunJumpState::GetState()
{
	return OneGunStates::ENEMYJUMPING;
}

void EnemyOneGunJumpState::OnCollision()
{
	this->enemyOneGunData->m_EnemyOneGun->SetVx(0);
}

EnemyOneGunJumpState::~EnemyOneGunJumpState()
{
}
