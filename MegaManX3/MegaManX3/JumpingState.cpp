#include "JumpingState.h"
#include "MegaManCharacters.h"



JumpingState::JumpingState(MegaManData *megaManData) {
	this->megaManData = megaManData;
	this->megaManData->megaMan->SetVy(200);
	this->megaManData->megaMan->SetVx(0);
	this->megaManData->megaMan->SetAy(-30);
}


JumpingState::~JumpingState()
{
}

void JumpingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT]) {
		this->megaManData->megaMan->SetVx(200);
		this->megaManData->megaMan->SetDirect(LEFT);
		//return;
	}
	if (keys[VK_RIGHT]) {
		this->megaManData->megaMan->SetVx(200);
		this->megaManData->megaMan->SetDirect(RIGHT);
	}
}

CharactersStates JumpingState::GetState()
{
	return JUMPING;
}

void JumpingState::Update(double time) {
	if (this->megaManData->megaMan->GetPosition().y <= MEGAMAN_START_Y) {
		this->megaManData->megaMan->SetState(new StandingState(this->megaManData));
	}
}
