#include "JumpingAttackState.h"
#include "MegaManCharacters.h"



JumpingAttackState::JumpingAttackState(MegaManData *megaManData, bool isStart) {
	this->megaManData = megaManData;
	listAnimation = this->megaManData->megaMan->GetListAnimation();
	if (isStart == true) {
		listAnimation[JUMPING_ATTACK].SetIndex(0);
		this->megaManData->megaMan->SetVy(JUMP_SPEED);
		this->megaManData->megaMan->SetAy(ACCELERATION_Y);
		this->megaManData->megaMan->isJumping = true;
	}
}


JumpingAttackState::~JumpingAttackState()
{
}

void JumpingAttackState::HandleKeyboard(std::map<int, bool> keys)
{
	/*if (!keys[VK_A]) {
		int index = listAnimation[JUMPING_ATTACK].GetIndex();
		listAnimation[JUMPING].SetIndex(index);
		this->megaManData->megaMan->SetState(new JumpingState(this->megaManData, false));
	}*/
}

CharactersStates JumpingAttackState::GetState()
{
	return JUMPING_ATTACK;
}

void JumpingAttackState::Update(double time) {
	if (this->megaManData->megaMan->GetVy() > 0 && listAnimation[JUMPING_ATTACK].GetIndex() == 3) {
		listAnimation[JUMPING_ATTACK].SetIndex(2);
	}
	else if (this->megaManData->megaMan->GetVy() <= 0 && this->megaManData->megaMan->isJumping == true && listAnimation[JUMPING_ATTACK].GetIndex() == 5) {
		listAnimation[JUMPING_ATTACK].SetIndex(4);
	}
	if (listAnimation[JUMPING_ATTACK].GetIndex() == (listAnimation[JUMPING_ATTACK].GetTotalFrame() - 1)) {
		if (this->megaManData->megaMan->isRightLeftKeyDown == true) {
			this->megaManData->megaMan->SetState(new RunningState(this->megaManData));
		}
		else {
			this->megaManData->megaMan->SetState(new StandingState(this->megaManData));
		}
	}
}
