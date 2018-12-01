#include "SweepingWallState.h"
#include "MegaManCharacters.h"



SweepingWallState::SweepingWallState(MegaManData *megaManData, bool isStart) {
	this->megaManData = megaManData;
	listAnimation = this->megaManData->megaMan->GetListAnimation();
	if (isStart == true) {
		listAnimation[SWEEPING_WALL].SetIndex(0);
		this->megaManData->megaMan->SetVy(0);
		this->megaManData->megaMan->SetAy(-100);
	}
}

SweepingWallState::~SweepingWallState()
{
}

void SweepingWallState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_A]) {
		int index = listAnimation[SWEEPING_WALL].GetIndex();
		listAnimation[SWEEPING_WALL_ATTACK].SetIndex(index);
		this->megaManData->megaMan->SetState(new SweepingWallAttackState(this->megaManData, false));
	}
	if (keys[VK_SPACE]) {
		this->megaManData->megaMan->SetState(new JumpingFromWallState(this->megaManData));
	}
}

CharactersStates SweepingWallState::GetState()
{
	return SWEEPING_WALL;
}

void SweepingWallState::Update(double time) {
	if (listAnimation[SWEEPING_WALL].GetIndex() == 0) {
		listAnimation[SWEEPING_WALL].SetIndex(listAnimation[SWEEPING_WALL].GetTotalFrame() - 1);
	}
}
