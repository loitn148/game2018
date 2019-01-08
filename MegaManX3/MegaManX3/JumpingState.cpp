#include "JumpingState.h"
#include "MegaManCharacters.h"



JumpingState::JumpingState(MegaManData *megaManData, bool isStart) {
	this->megaManData = megaManData;
	listAnimation = this->megaManData->megaMan->GetListAnimation();
	if (isStart == true) {
		listAnimation[JUMPING].SetIndex(0);
		this->megaManData->megaMan->SetVy(JUMP_SPEED);
		this->megaManData->megaMan->SetAy(ACCELERATION_Y);
		this->megaManData->megaMan->isJumping = true;
	}
}

JumpingState::~JumpingState(){}

void JumpingState::HandleKeyboard(std::map<int, bool> keys)
{
	/*if (keys[VK_A]) {
		int index = listAnimation[JUMPING].GetIndex();
		listAnimation[JUMPING_ATTACK].SetIndex(index);
		this->megaManData->megaMan->SetState(new JumpingAttackState(this->megaManData, false));
	}*/
}

CharactersStates JumpingState::GetState()
{
	return JUMPING;
}

void JumpingState::Update(double time) {
	if (this->megaManData->megaMan->GetVy() > 0 && listAnimation[JUMPING].GetIndex() == 3) {
		listAnimation[JUMPING].SetIndex(2);
	}
	else if (this->megaManData->megaMan->GetVy() <= 0 && this->megaManData->megaMan->isJumping == true && listAnimation[JUMPING].GetIndex() == 5) {
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
