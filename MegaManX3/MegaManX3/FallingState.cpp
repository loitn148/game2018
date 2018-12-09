#include "FallingState.h"
#include "MegaManCharacters.h"


FallingState::FallingState(MegaManData *megaManData, bool isStart) {
	this->megaManData = megaManData;
	listAnimation = this->megaManData->megaMan->GetListAnimation();
	if (isStart == true) {
		listAnimation[FALLING].SetIndex(0);
		this->megaManData->megaMan->isFalling = true;
	}
}

FallingState::~FallingState() {}

void FallingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_A]) {
		int index = listAnimation[FALLING].GetIndex();
		listAnimation[FALLING_ATTACK].SetIndex(index);
		this->megaManData->megaMan->SetState(new FallingAttackState(this->megaManData, false));
	}

	/*if (keys[VK_SPACE]) {
	this->megaManData->megaMan->SetState(new FallingState(this->megaManData));
	}*/
}

CharactersStates FallingState::GetState()
{
	return FALLING;
}

void FallingState::Update(double time) {
	if (this->megaManData->megaMan->GetVy() <= 0 && this->megaManData->megaMan->isFalling == true && listAnimation[FALLING].GetIndex() == 1) {
		listAnimation[FALLING].SetIndex(0);
	}
	if (listAnimation[FALLING].GetIndex() == (listAnimation[FALLING].GetTotalFrame() - 1)) {
		if (this->megaManData->megaMan->isRightLeftKeyDown == true) {
			this->megaManData->megaMan->SetState(new RunningState(this->megaManData));
		}
		else {
			this->megaManData->megaMan->SetState(new StandingState(this->megaManData));
		}
	}
}
