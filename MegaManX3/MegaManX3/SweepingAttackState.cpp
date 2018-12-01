#include "SweepingAttackState.h"
#include "MegaManCharacters.h"



SweepingAttackState::SweepingAttackState(MegaManData *megaManData, bool isStart) {
	this->megaManData = megaManData;
	listAnimation = this->megaManData->megaMan->GetListAnimation();
	if (isStart == true) {
		listAnimation[SWEEPING_ATTACK].SetIndex(0);
		this->megaManData->megaMan->SetVx(this->megaManData->megaMan->GetDirect()*SWEEP_SPEED);
		this->megaManData->megaMan->SetAx(-this->megaManData->megaMan->GetDirect() * 300);
	}
}


SweepingAttackState::~SweepingAttackState()
{
}

void SweepingAttackState::HandleKeyboard(std::map<int, bool> keys)
{
	if (!keys[VK_A]) {
		int index = listAnimation[SWEEPING_ATTACK].GetIndex();
		listAnimation[SWEEPING].SetIndex(index);
		this->megaManData->megaMan->SetState(new SweepingState(this->megaManData, false));
	}
}

CharactersStates SweepingAttackState::GetState()
{
	return SWEEPING_ATTACK;
}

void SweepingAttackState::Update(double time) {
	if (listAnimation[SWEEPING_ATTACK].GetIndex() == 0) {
		listAnimation[SWEEPING_ATTACK].SetIndex(listAnimation[SWEEPING_ATTACK].GetTotalFrame() - 1);
	}
	if (this->megaManData->megaMan->GetVx() * this->megaManData->megaMan->GetDirect() <= 0) {
		this->megaManData->megaMan->SetState(new StandingState(this->megaManData));
	}
}
