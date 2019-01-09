#include "BossFinalHealth.h"

BossFinalHealth* BossFinalHealth::instance = NULL;
BossFinalHealth* BossFinalHealth::GetInstance() {
	if (!BossFinalHealth::instance) {
		BossFinalHealth::instance = new BossFinalHealth();
	}
	return BossFinalHealth::instance;
}

BossFinalHealth::BossFinalHealth()
{
	this->animation = new Animation();
	this->currentHealth = 14;
	this->SetAnimation();
	this->position = VT3(CAMERA_START_X + 450, CAMERA_START_Y - 10, 0);
}


BossFinalHealth::~BossFinalHealth()
{
}

void BossFinalHealth::Update(double time) {
	if (currentHealth > 0) {
		int curentIdx = currentHealth - 1;
		this->animation->SetIndex(curentIdx);
	}
	else {
		isDead = true;
	}
}

void BossFinalHealth::SetHealth(int health) {
	this->currentHealth = health;
}

void BossFinalHealth::Draw(double time) {
	if (!isDead) {
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->animation->Draw(transform.positionInViewport, this->direct, time, VT2(2.2, 2.5), transform.translation, C_XRGB(255, 255, 255));
	}
}

void BossFinalHealth::SetAnimation() {
	std::vector<Rect> temp;
	temp.push_back(Rect(0, 0, 76, 14));
	temp.push_back(Rect(0, 14, 76, 28));
	temp.push_back(Rect(0, 28, 76, 42));
	temp.push_back(Rect(0, 42, 76, 56));
	temp.push_back(Rect(0, 56, 76, 70));
	temp.push_back(Rect(0, 70, 76, 84));
	temp.push_back(Rect(0, 84, 76, 98));
	temp.push_back(Rect(0, 98, 76, 112));
	temp.push_back(Rect(0, 112, 76, 126));
	temp.push_back(Rect(0, 126, 76, 140));
	temp.push_back(Rect(0, 140, 76, 154));
	temp.push_back(Rect(0, 154, 76, 168));
	temp.push_back(Rect(0, 168, 76, 182));
	temp.push_back(Rect(0, 182, 76, 196));

	this->animation->Create(BOSSHEALTH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();
}