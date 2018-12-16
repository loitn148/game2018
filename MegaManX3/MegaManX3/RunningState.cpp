#include "RunningState.h"
#include "MegaManCharacters.h"



RunningState::RunningState(MegaManData *megaManData, bool isStart) {
	this->megaManData = megaManData;
	listAnimation = this->megaManData->megaMan->GetListAnimation();
	if (isStart == true) {
		listAnimation[RUNNING].SetIndex(0);
		this->megaManData->megaMan->SetVy(0);
		this->megaManData->megaMan->SetAx(0);
		this->megaManData->megaMan->SetVx(this->megaManData->megaMan->GetDirect()*RUN_SPEED);
	}
}


RunningState::~RunningState()
{
}

void RunningState::HandleKeyboard(std::map<int, bool> keys)
{
	/*if (keys[VK_A]) {
		int index = listAnimation[RUNNING].GetIndex();
		listAnimation[RUNNING_ATTACK].SetIndex(index);
		this->megaManData->megaMan->SetState(new RunningAttackState(this->megaManData, false));
	}*/
	if (keys[VK_S]){
		this->megaManData->megaMan->SetState(new SweepingState(this->megaManData));
	}
	if (keys[VK_SPACE]) {
		this->megaManData->megaMan->SetState(new JumpingState(this->megaManData));
	}
}

CharactersStates RunningState::GetState()
{
	return RUNNING;
}

void RunningState::Update(double time) {

}
