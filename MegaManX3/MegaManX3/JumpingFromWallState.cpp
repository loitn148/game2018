#include "JumpingFromWallState.h"
#include "MegaManCharacters.h"



JumpingFromWallState::JumpingFromWallState(MegaManData *megaManData, bool isStart) {
	this->megaManData = megaManData;

	if (this->megaManData->megaMan->GetDirect() == LEFT) {
		this->megaManData->megaMan->SetDirect(RIGHT);
	}
	else {
		this->megaManData->megaMan->SetDirect(LEFT);
	}

	listAnimation = this->megaManData->megaMan->GetListAnimation();
	if (isStart == true) {
		listAnimation[JUMPING_FROM_WALL].SetIndex(0);
		this->megaManData->megaMan->SetVy(JUMP_SPEED);

		VT3 position = this->megaManData->megaMan->GetPosition();
		this->megaManData->megaMan->SetPosition(VT3(position.x + -10 * this->megaManData->megaMan->GetDirect(), position.y, 0));
		this->megaManData->megaMan->SetAy(ACCELERATION_Y);
		this->megaManData->megaMan->isJumping = true;
	}
}

JumpingFromWallState::~JumpingFromWallState() {}

void JumpingFromWallState::HandleKeyboard(std::map<int, bool> keys)
{
	/*if (keys[VK_A]) {
		int index = listAnimation[JUMPING_FROM_WALL].GetIndex();
		listAnimation[JUMPING_FROM_WALL_ATTACK].SetIndex(index);
		this->megaManData->megaMan->SetState(new JumpingFromWallAttackState(this->megaManData, false));
	}*/
}

CharactersStates JumpingFromWallState::GetState()
{
	return JUMPING_FROM_WALL;
}

void JumpingFromWallState::Update(double time) {
	if (this->megaManData->megaMan->GetVy() > 0 && listAnimation[JUMPING_FROM_WALL].GetIndex() == 2) {
		listAnimation[JUMPING_FROM_WALL].SetIndex(1);
	}
	else if (this->megaManData->megaMan->GetVy() <= 0 && this->megaManData->megaMan->isJumping == true && listAnimation[JUMPING_FROM_WALL].GetIndex() == 4) {
		listAnimation[JUMPING_FROM_WALL].SetIndex(3);
	}
	if (listAnimation[JUMPING_FROM_WALL].GetIndex() == (listAnimation[JUMPING_FROM_WALL].GetTotalFrame() - 1)) {
		if (this->megaManData->megaMan->isRightLeftKeyDown == true) {
			this->megaManData->megaMan->SetState(new RunningState(this->megaManData));
		}
		else {
			this->megaManData->megaMan->SetState(new StandingState(this->megaManData));
		}
	}
}
