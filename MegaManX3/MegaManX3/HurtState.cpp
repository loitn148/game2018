#include "HurtState.h"
#include "MegaManCharacters.h"


HurtState::HurtState(MegaManData *megaManData) {
	this->megaManData = megaManData;
	this->megaManData->megaMan->SetAx(0);
	this->megaManData->megaMan->SetVy(500);
	this->megaManData->megaMan->SetVx(-this->megaManData->megaMan->GetDirect()*100);
	this->megaManData->megaMan->SetAy(ACCELERATION_Y);
}

HurtState::~HurtState() {}

void HurtState::HandleKeyboard(std::map<int, bool> keys)
{
	
}

CharactersStates HurtState::GetState()
{
	return HURT;
}

void HurtState::Update(double time) {
}
