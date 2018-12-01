#include "SweepingWallAttackState.h"
#include "MegaManCharacters.h"



SweepingWallAttackState::SweepingWallAttackState(MegaManData *megaManData, bool isStart) {
	this->megaManData = megaManData;
	listAnimation = this->megaManData->megaMan->GetListAnimation();
	if (isStart == true) {
		listAnimation[SWEEPING_WALL].SetIndex(0);
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
		int index = listAnimation[SWEEPING_WALL_ATTACK].GetIndex();
		listAnimation[SWEEPING_WALL].SetIndex(index);
		this->megaManData->megaMan->SetState(new SweepingWallState(this->megaManData, false));
	}

	if (keys[VK_SPACE]) {
		this->megaManData->megaMan->SetState(new JumpingFromWallAttackState(this->megaManData));
	}
}

CharactersStates SweepingWallAttackState::GetState()
{
	return SWEEPING_WALL_ATTACK;
}

void SweepingWallAttackState::Update(double time) {
	if (listAnimation[SWEEPING_WALL_ATTACK].GetIndex() == 0) {
		listAnimation[SWEEPING_WALL_ATTACK].SetIndex(listAnimation[SWEEPING_WALL_ATTACK].GetTotalFrame() - 1);
	}
}
