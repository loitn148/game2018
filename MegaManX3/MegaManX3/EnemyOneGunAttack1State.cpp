#include "EnemyOneGunAttack1State.h"
#include "EnemyOneGun.h"
#include "MegaManCharacters.h"
#include "EnemyOneGunStandState.h"
#include "OneGunBullet.h"


EnemyOneGunAttack1State::EnemyOneGunAttack1State()
{
}

EnemyOneGunAttack1State::EnemyOneGunAttack1State(EnemyOneGunData * enemyOneGunData)
{
	NumberBullet = 0;
	this->enemyOneGunData = enemyOneGunData;
	this->enemyOneGunData->m_EnemyOneGun->listAnimation[OneGunStates::ENEMYATTACK1].SetIndex(0);
}

void EnemyOneGunAttack1State::Update(double time)
{
	if (this->enemyOneGunData->m_EnemyOneGun->listAnimation[OneGunStates::ENEMYATTACK1].GetIndex() == (this->enemyOneGunData->m_EnemyOneGun->listAnimation[OneGunStates::ENEMYATTACK1].GetTotalFrame() - 1))
	{
		//if (this->enemyOneGunData->m_EnemyOneGun->vtRocket.size()<4)
		//{
			OneGunBullet* rocket = new OneGunBullet(VT3(this->enemyOneGunData->m_EnemyOneGun->GetPosition().x + (35*this->enemyOneGunData->m_EnemyOneGun->GetDirect()), this->enemyOneGunData->m_EnemyOneGun->GetPosition().y + 80, 0),
													900, -200, 600,
													this->enemyOneGunData->m_EnemyOneGun->GetDirect());
			this->enemyOneGunData->m_EnemyOneGun->listAnimation[OneGunStates::ENEMYATTACK1].SetIndex(0);
			this->enemyOneGunData->m_EnemyOneGun->vtRocket.push_back(rocket);
			NumberBullet++;
		//}
	}
	if (NumberBullet > 2)
	{
		this->enemyOneGunData->m_EnemyOneGun->SetState(new EnemyOneGunStandState(this->enemyOneGunData));
	}


}

void EnemyOneGunAttack1State::HandleKeyboard(std::map<int, bool> keys)
{

}

OneGunStates EnemyOneGunAttack1State::GetState()
{
	return OneGunStates::ENEMYATTACK1;
}

void EnemyOneGunAttack1State::OnCollision()
{
	this->enemyOneGunData->m_EnemyOneGun->SetVx(0);
}

EnemyOneGunAttack1State::~EnemyOneGunAttack1State()
{
}
