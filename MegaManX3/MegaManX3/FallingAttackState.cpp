#include "FallingAttackState.h"
#include "MegaManCharacters.h"



FallingAttackState::FallingAttackState(MegaManData *megaManData, bool isStart) {
	this->megaManData = megaManData;
	listAnimation = this->megaManData->megaMan->GetListAnimation();
	if (isStart == true) {
		listAnimation[FALLING_ATTACK].SetIndex(0);
		this->megaManData->megaMan->isFalling = true;
	}
}


FallingAttackState::~FallingAttackState()
{
}

void FallingAttackState::HandleKeyboard(std::map<int, bool> keys)
{
	/*if (!keys[VK_A]) {
		int index = listAnimation[FALLING_ATTACK].GetIndex();
		listAnimation[FALLING].SetIndex(index);
		this->megaManData->megaMan->SetState(new JumpingState(this->megaManData, false));
	}*/
}

CharactersStates FallingAttackState::GetState()
{
	return FALLING_ATTACK;
}

void FallingAttackState::Update(double time) {
	if (this->megaManData->megaMan->GetVy() > 0 && listAnimation[FALLING_ATTACK].GetIndex() == 3) {
		listAnimation[FALLING_ATTACK].SetIndex(2);
	}
	else if (this->megaManData->megaMan->GetVy() <= 0) {
		this->megaManData->megaMan->SetVx(0);
		if (this->megaManData->megaMan->isFalling == true && listAnimation[FALLING_ATTACK].GetIndex() == 5) {
			listAnimation[FALLING_ATTACK].SetIndex(4);
		}
	}
	if (listAnimation[FALLING_ATTACK].GetIndex() == (listAnimation[FALLING_ATTACK].GetTotalFrame() - 1)) {
		if (this->megaManData->megaMan->isRightLeftKeyDown == true) {
			this->megaManData->megaMan->SetState(new RunningState(this->megaManData));
		}
		else {
			this->megaManData->megaMan->SetState(new StandingState(this->megaManData));
		}
	}
}
