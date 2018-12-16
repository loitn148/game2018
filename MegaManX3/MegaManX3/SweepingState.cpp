#include "SweepingState.h"
#include "MegaManCharacters.h"



SweepingState::SweepingState(MegaManData *megaManData, bool isStart) {
	this->megaManData = megaManData;
	listAnimation = this->megaManData->megaMan->GetListAnimation();
	if (isStart == true) {
		listAnimation[SWEEPING].SetIndex(0);
		this->megaManData->megaMan->SetVx(this->megaManData->megaMan->GetDirect()*SWEEP_SPEED);
		this->megaManData->megaMan->SetAx(-this->megaManData->megaMan->GetDirect() * ACCELERATION_X);
	}
}

SweepingState::~SweepingState()
{
}

void SweepingState::HandleKeyboard(std::map<int, bool> keys)
{
	/*if (keys[VK_A]) {
		int index = listAnimation[SWEEPING].GetIndex();
		listAnimation[SWEEPING_ATTACK].SetIndex(index);
		this->megaManData->megaMan->SetState(new SweepingAttackState(this->megaManData, false));
	}*/
}

CharactersStates SweepingState::GetState()
{
	return SWEEPING;
}

void SweepingState::Update(double time) {
	if (listAnimation[SWEEPING].GetIndex() == 0) {
		listAnimation[SWEEPING].SetIndex(listAnimation[SWEEPING].GetTotalFrame() - 1);
	}
	if (this->megaManData->megaMan->GetVx() * this->megaManData->megaMan->GetDirect() <= 0) {
		if (this->megaManData->megaMan->isRightLeftKeyDown == true) {
			this->megaManData->megaMan->SetState(new RunningState(this->megaManData));
		}
		else {
			this->megaManData->megaMan->SetState(new StandingState(this->megaManData));
		}
	}
}
