#include "StandingState.h"
#include "MegaManCharacters.h"



StandingState::StandingState(MegaManData *megaManData) {
	this->megaManData = megaManData;
	this->megaManData->megaMan->SetVx(0);
	this->megaManData->megaMan->SetVy(0);
}


StandingState::~StandingState()
{
}

void StandingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		//this->megaManData->megaMan->SetState();
		return;
	}
}

CharactersStates StandingState::GetState()
{
	return STANDING;
}

void StandingState::Update(double time) {

}

