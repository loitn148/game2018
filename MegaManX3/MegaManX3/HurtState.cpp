#include "HurtState.h"
#include "MegaManCharacters.h"


HurtState::HurtState(MegaManData *megaManData, CharactersStates previousState) {
	this->megaManData = megaManData;
	this->megaManData->megaMan->SetVx(0);
	this->previousState = previousState;
	this->duration = 0.0f;
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
	if (duration >= 1.5f) {
		switch (previousState)
		{
		case JUMPING:
		case JUMPING_ATTACK:
		case JUMPING_FROM_WALL:
		case JUMPING_FROM_WALL_ATTACK:
		case SWEEPING_WALL:
		case SWEEPING_WALL_ATTACK:
		case FALLING:
		case FALLING_ATTACK:
			this->megaManData->megaMan->SetState(new FallingState(this->megaManData));
			break;
		default:
			this->megaManData->megaMan->SetState(new StandingState(this->megaManData));
			break;
		}
	}

	duration += time;
}
