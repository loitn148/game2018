#include "EnemyOneGunAttack2State.h"
#include "EnemyOneGun.h"
#include "MegaManCharacters.h"


EnemyOneGunAttack2State::EnemyOneGunAttack2State()
{
}

EnemyOneGunAttack2State::EnemyOneGunAttack2State(EnemyOneGunData * enemyOneGunData)
{
	this->enemyOneGunData = enemyOneGunData;
	this->enemyOneGunData->m_EnemyOneGun->listAnimation[OneGunStates::ENEMYATTACK2].SetIndex(0);
	NumberBullet = 0;
}

void EnemyOneGunAttack2State::Update(double time)
{
	if (this->enemyOneGunData->m_EnemyOneGun->listAnimation[OneGunStates::ENEMYATTACK2].GetIndex() == (this->enemyOneGunData->m_EnemyOneGun->listAnimation[OneGunStates::ENEMYATTACK2].GetTotalFrame() - 1))
	{
		//if (this->enemyOneGunData->m_EnemyOneGun->vtRocket.size()<4)
		//{
			OneGunBullet* rocket = new OneGunBullet(VT3(this->enemyOneGunData->m_EnemyOneGun->GetPosition().x, this->enemyOneGunData->m_EnemyOneGun->GetPosition().y+80, 0),
													1500,-200,200,
													this->enemyOneGunData->m_EnemyOneGun->GetDirect());
			this->enemyOneGunData->m_EnemyOneGun->listAnimation[OneGunStates::ENEMYATTACK2].SetIndex(0);
			this->enemyOneGunData->m_EnemyOneGun->vtRocket.push_back(rocket);
			NumberBullet++;
		//}
	}
	if (NumberBullet > 2)
	{
		this->enemyOneGunData->m_EnemyOneGun->SetState(new EnemyOneGunStandState(this->enemyOneGunData));
	}
}

void EnemyOneGunAttack2State::HandleKeyboard(std::map<int, bool> keys)
{

}

OneGunStates EnemyOneGunAttack2State::GetState()
{
	return OneGunStates::ENEMYATTACK2;
}

void EnemyOneGunAttack2State::OnCollision()
{
	this->enemyOneGunData->m_EnemyOneGun->SetVx(0);
}

EnemyOneGunAttack2State::~EnemyOneGunAttack2State()
{
}
