#include "StandingState.h"
#include "MegaManCharacters.h"



StandingState::StandingState(MegaManData *megaManData, bool isStart) {
	this->megaManData = megaManData;
	listAnimation = this->megaManData->megaMan->GetListAnimation();
	if (isStart == true) {
		this->megaManData->megaMan->SetVx(0);
		//this->megaManData->megaMan->SetVy(0);
		this->megaManData->megaMan->SetAx(0);
		//this->megaManData->megaMan->SetAy(ACCELERATION_Y);
	}
}


StandingState::~StandingState()
{
}

void StandingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_S]) {
		this->megaManData->megaMan->SetState(new SweepingState(this->megaManData));
	}
	if (keys[VK_SPACE]) {
		this->megaManData->megaMan->SetState(new JumpingState(this->megaManData));
	}
}

CharactersStates StandingState::GetState()
{
	return STANDING;
}

void StandingState::Update(double time) {

}

