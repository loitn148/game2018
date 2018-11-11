#include "RunningState.h"
#include "MegaManCharacters.h"



RunningState::RunningState(MegaManData *megaManData) {
	this->megaManData = megaManData;
	this->megaManData->megaMan->SetVx(RUN_SPEED);
	this->megaManData->megaMan->SetVy(0);
}


RunningState::~RunningState()
{
}

void RunningState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		//this->megaManData->megaMan->SetState();
		return;
	}
}

CharactersStates RunningState::GetState()
{
	return RUNNING;
}

void RunningState::Update(double time) {

}
