#include "JumpingFromWallState.h"
#include "MegaManCharacters.h"



JumpingFromWallState::JumpingFromWallState(MegaManData *megaManData, bool isStart) {
	this->megaManData = megaManData;
	listAnimation = this->megaManData->megaMan->GetListAnimation();
	if (isStart == true) {
		listAnimation[JUMPING].SetIndex(0);
		this->megaManData->megaMan->SetVy(JUMP_SPEED);
		this->megaManData->megaMan->SetAy(-200);
	}
}

JumpingFromWallState::~JumpingFromWallState() {}

void JumpingFromWallState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_A]) {
		int index = listAnimation[JUMPING].GetIndex();
		listAnimation[JUMPING_ATTACK].SetIndex(index);
		this->megaManData->megaMan->SetState(new JumpingAttackState(this->megaManData, false));
	}

	if (keys[VK_SPACE]) {
		this->megaManData->megaMan->SetState(new JumpingFromWallState(this->megaManData));
	}
}

CharactersStates JumpingFromWallState::GetState()
{
	return JUMPING;
}

void JumpingFromWallState::Update(double time) {
	if (this->megaManData->megaMan->GetVy() > 0 && listAnimation[JUMPING].GetIndex() == 3) {
		listAnimation[JUMPING].SetIndex(2);
	}
	else if (this->megaManData->megaMan->GetVy() <= 0 && this->megaManData->megaMan->GetAy() != 0 && listAnimation[JUMPING].GetIndex() == 5) {
		listAnimation[JUMPING].SetIndex(4);
	}
	if (listAnimation[JUMPING].GetIndex() == (listAnimation[JUMPING].GetTotalFrame() - 1)) {
		if (this->megaManData->megaMan->isRightLeftKeyDown == true) {
			this->megaManData->megaMan->SetState(new RunningState(this->megaManData));
		}
		else {
			this->megaManData->megaMan->SetState(new StandingState(this->megaManData));
		}
	}
}
