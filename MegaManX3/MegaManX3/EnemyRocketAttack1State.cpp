#include "EnemyRocketAttack1State.h"
#include "EnemyRocket.h"
#include "EnemyRocketStandingState.h"


EnemyRocketAttack1State::EnemyRocketAttack1State()
{
}
EnemyRocketAttack1State::EnemyRocketAttack1State(EnemyRocketData * enemyOneGunData)
{
	this->enemyRocketData = enemyOneGunData;
	this->enemyRocketData->m_EnemyRocket->SetVy(0);
	this->enemyRocketData->m_EnemyRocket->SetVx(0);
	this->enemyRocketData->m_EnemyRocket->SetAy(0);
	this->enemyRocketData->m_EnemyRocket->SetAx(0);
	this->enemyRocketData->m_EnemyRocket->listAnimation[EnemyRocketStates::ENEMYROCKETATTACK1].SetIndex(0);
}

void EnemyRocketAttack1State::Update(double time)
{
	if (this->enemyRocketData->m_EnemyRocket->listAnimation[ENEMYROCKETATTACK1].GetIndex() == (this->enemyRocketData->m_EnemyRocket->listAnimation[ENEMYROCKETATTACK1].GetTotalFrame() - 1))
	{
		if (this->enemyRocketData->m_EnemyRocket->rocket->GetIsDead())
		{
			
			this->enemyRocketData->m_EnemyRocket->rocket->SetIsDead(false);
			this->enemyRocketData->m_EnemyRocket->rocket->isCollision = false;
			this->enemyRocketData->m_EnemyRocket->rocket->SetPosition(VT3(this->enemyRocketData->m_EnemyRocket->GetPosition().x + 30 * this->enemyRocketData->m_EnemyRocket->GetDirect(),
																		this->enemyRocketData->m_EnemyRocket->GetPosition().y + 70, 0));
			this->enemyRocketData->m_EnemyRocket->rocket->SetVx(400 * this->enemyRocketData->m_EnemyRocket->GetDirect());
			if (this->enemyRocketData->m_EnemyRocket->rocket->GetPosition().y >= MegaManCharacters::GetInstance()->GetPosition().y)
			{
				this->enemyRocketData->m_EnemyRocket->rocket->SetVy(-150);
			}
			else
			{
				this->enemyRocketData->m_EnemyRocket->rocket->SetVy(150);

			}
			
			this->enemyRocketData->m_EnemyRocket->SetState(new EnemyRocketStandingState(enemyRocketData));
		}

	}

}

void EnemyRocketAttack1State::HandleKeyboard(std::map<int, bool> keys)
{

}

EnemyRocketStates EnemyRocketAttack1State::GetState()
{
	return EnemyRocketStates::ENEMYROCKETATTACK1;
}

void EnemyRocketAttack1State::OnCollision()
{

}

EnemyRocketAttack1State::~EnemyRocketAttack1State()
{
}
