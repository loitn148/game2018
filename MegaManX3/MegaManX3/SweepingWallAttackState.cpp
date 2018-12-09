#include "SweepingWallAttackState.h"
#include "MegaManCharacters.h"



SweepingWallAttackState::SweepingWallAttackState(MegaManData *megaManData, bool isStart) {
	this->megaManData = megaManData;
	listAnimation = this->megaManData->megaMan->GetListAnimation();
	if (isStart == true) {
		listAnimation[JUMPING_FROM_WALL_ATTACK].SetIndex(0);
		this->megaManData->megaMan->SetVy(0);
		this->megaManData->megaMan->SetAy(-100);
	}
}

SweepingWallAttackState::~SweepingWallAttackState()
{
}

void SweepingWallAttackState::HandleKeyboard(std::map<int, bool> keys)
{
	if (!keys[VK_A]) {
		int index = listAnimation[JUMPING_FROM_WALL_ATTACK].GetIndex();
		listAnimation[JUMPING_FROM_WALL].SetIndex(index);
		this->megaManData->megaMan->SetState(new SweepingWallState(this->megaManData, false));
	}
}

CharactersStates SweepingWallAttackState::GetState()
{
	return JUMPING_FROM_WALL_ATTACK;
}

void SweepingWallAttackState::Update(double time) {
	if (this->megaManData->megaMan->GetVy() > 0 && listAnimation[JUMPING_FROM_WALL_ATTACK].GetIndex() == 3) {
		listAnimation[JUMPING_FROM_WALL_ATTACK].SetIndex(2);
	}
	else if (this->megaManData->megaMan->GetVy() <= 0 && this->megaManData->megaMan->GetAy() != 0 && listAnimation[JUMPING_FROM_WALL_ATTACK].GetIndex() == 5) {
		listAnimation[JUMPING_FROM_WALL_ATTACK].SetIndex(4);
	}
	if (listAnimation[JUMPING_FROM_WALL_ATTACK].GetIndex() == (listAnimation[JUMPING_FROM_WALL_ATTACK].GetTotalFrame() - 1)) {
		if (this->megaManData->megaMan->isRightLeftKeyDown == true) {
			this->megaManData->megaMan->SetState(new RunningAttackState(this->megaManData));
		}
		else {
			this->megaManData->megaMan->SetState(new StandingAttackState(this->megaManData));
		}
	}
}
