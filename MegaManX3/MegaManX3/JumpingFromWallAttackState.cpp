#include "JumpingFromWallAttackState.h"
#include "MegaManCharacters.h"



JumpingFromWallAttackState::JumpingFromWallAttackState(MegaManData *megaManData, bool isStart) {
	this->megaManData = megaManData;
	listAnimation = this->megaManData->megaMan->GetListAnimation();
	if (isStart == true) {
		listAnimation[JUMPING].SetIndex(0);
		this->megaManData->megaMan->SetVy(JUMP_SPEED);

		VT3 position = this->megaManData->megaMan->GetPosition();
		this->megaManData->megaMan->SetPosition(VT3(position.x + 10 * this->megaManData->megaMan->GetDirect(), position.y, 0));
		this->megaManData->megaMan->SetAy(ACCELERATION_Y);
		this->megaManData->megaMan->isJumping = true;
	}
}

JumpingFromWallAttackState::~JumpingFromWallAttackState() {}

void JumpingFromWallAttackState::HandleKeyboard(std::map<int, bool> keys)
{
	/*if (keys[VK_A]) {
		int index = listAnimation[JUMPING].GetIndex();
		listAnimation[JUMPING_ATTACK].SetIndex(index);
		this->megaManData->megaMan->SetState(new JumpingAttackState(this->megaManData, false));
	}*/

	/*if (keys[VK_SPACE]) {
		this->megaManData->megaMan->SetState(new JumpingFromWallAttackState(this->megaManData));
	}*/
}

CharactersStates JumpingFromWallAttackState::GetState()
{
	return JUMPING_FROM_WALL_ATTACK;
}

void JumpingFromWallAttackState::Update(double time) {
	if (this->megaManData->megaMan->GetVy() > 0 && listAnimation[JUMPING_FROM_WALL_ATTACK].GetIndex() == 2) {
		listAnimation[JUMPING_FROM_WALL_ATTACK].SetIndex(1);
	}
	else if (this->megaManData->megaMan->GetVy() <= 0 && this->megaManData->megaMan->isJumping == true && listAnimation[JUMPING_FROM_WALL_ATTACK].GetIndex() == 4) {
		listAnimation[JUMPING_FROM_WALL_ATTACK].SetIndex(3);
	}
	if (listAnimation[JUMPING_FROM_WALL_ATTACK].GetIndex() == (listAnimation[JUMPING_FROM_WALL_ATTACK].GetTotalFrame() - 1)) {
		if (this->megaManData->megaMan->isRightLeftKeyDown == true) {
			this->megaManData->megaMan->SetState(new RunningState(this->megaManData));
		}
		else {
			this->megaManData->megaMan->SetState(new StandingState(this->megaManData));
		}
	}
}
