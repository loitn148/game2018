#include "Start1State.h"
#include "MegaManCharacters.h"
#include "Start2State.h"



Start1State::Start1State(MegaManData *megaManData) {
	this->megaManData = megaManData;
	this->megaManData->megaMan->SetVx(0);
	this->megaManData->megaMan->SetVy(START_SPEED_Y);
}


Start1State::~Start1State()
{
}

void Start1State::HandleKeyboard(std::map<int, bool> keys)
{
}

CharactersStates Start1State::GetState()
{
	return START1;
}

void Start1State::Update(double time) {
}
