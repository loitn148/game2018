#include "Start2State.h"
#include "MegaManCharacters.h"



Start2State::Start2State(MegaManData *megaManData) {
	this->megaManData = megaManData;
	this->megaManData->megaMan->SetVx(0);
	//this->megaManData->megaMan->SetVy(0);
}


Start2State::~Start2State()
{
}

void Start2State::HandleKeyboard(std::map<int, bool> keys)
{
}

CharactersStates Start2State::GetState()
{
	return START2;
}

void Start2State::Update(double time) {
	Animation* listAnimation = this->megaManData->megaMan->GetListAnimation();
	if (listAnimation[START2].GetIndex() == listAnimation[START2].GetTotalFrame() - 1) {
		this->megaManData->megaMan->SetState(new StandingState(this->megaManData));
	}
}
