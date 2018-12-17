#include "RunningAttackState.h"
#include "MegaManCharacters.h"



RunningAttackState::RunningAttackState(MegaManData *megaManData, bool isStart) {
	this->megaManData = megaManData;
	listAnimation = this->megaManData->megaMan->GetListAnimation();
	if (isStart == true) {
		listAnimation[RUNNING_ATTACK].SetIndex(0);
		this->megaManData->megaMan->SetVx(this->megaManData->megaMan->GetDirect()*RUN_SPEED);
		//this->megaManData->megaMan->SetVy(0);
	}
}


RunningAttackState::~RunningAttackState()
{
}

void RunningAttackState::HandleKeyboard(std::map<int, bool> keys)
{
	/*if (!keys[VK_A]) {
		int index = listAnimation[RUNNING_ATTACK].GetIndex();
		listAnimation[RUNNING].SetIndex(index);
		this->megaManData->megaMan->SetState(new RunningState(this->megaManData, false));
	}*/
	if (keys[VK_S])
	{
		this->megaManData->megaMan->SetState(new SweepingState(this->megaManData));
	}
	if (keys[VK_SPACE]) {
		this->megaManData->megaMan->SetState(new JumpingState(this->megaManData));
	}
}

CharactersStates RunningAttackState::GetState()
{
	return RUNNING_ATTACK;
}

void RunningAttackState::Update(double time) {
	if (listAnimation[RUNNING_ATTACK].GetIndex() == 0) {
		this->megaManData->megaMan->SetState(new RunningState(this->megaManData));
	}
}
