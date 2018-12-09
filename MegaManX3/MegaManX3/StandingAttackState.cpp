#include "StandingAttackState.h"
#include "MegaManCharacters.h"



StandingAttackState::StandingAttackState(MegaManData *megaManData, bool isStart) {
	this->megaManData = megaManData;
	listAnimation = this->megaManData->megaMan->GetListAnimation();
	if (isStart == true) {
		this->megaManData->megaMan->SetVx(0);
		this->megaManData->megaMan->SetVy(0);
		this->megaManData->megaMan->SetAx(0);
		this->megaManData->megaMan->SetAy(-200);
	}
}


StandingAttackState::~StandingAttackState()
{
}

void StandingAttackState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_S])
	{
		this->megaManData->megaMan->SetState(new SweepingAttackState(this->megaManData));
	}
	if (keys[VK_SPACE]) {
		this->megaManData->megaMan->SetState(new JumpingAttackState(this->megaManData));
	}
}

CharactersStates StandingAttackState::GetState()
{
	return STANDING_ATTACK;
}

void StandingAttackState::Update(double time) {

}
