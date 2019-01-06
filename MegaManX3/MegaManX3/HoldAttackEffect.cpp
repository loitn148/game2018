#include "HoldAttackEffect.h"

HoldAttackEffect::HoldAttackEffect()
{
	this->id = HOLDATTACK;
}


HoldAttackEffect::~HoldAttackEffect()
{
}

HoldAttackEffect::HoldAttackEffect(VT3 position, int bulletType)
{
	listAnimation = new Animation[2];

	std::vector<Rect> temp;

	//Bullet2
	temp.push_back(Rect(64, 201, 112, 205));
	temp.push_back(Rect(0, 0, 44, 46));
	temp.push_back(Rect(40, 47, 80, 90));
	temp.push_back(Rect(82, 88, 118, 126));
	temp.push_back(Rect(0, 174, 34, 210));
	temp.push_back(Rect(43, 133, 87, 167));
	temp.push_back(Rect(64, 168, 106, 200));
	temp.push_back(Rect(45, 0, 84, 44));
	temp.push_back(Rect(0, 92, 36, 134));
	temp.push_back(Rect(37, 92, 81, 132));
	temp.push_back(Rect(0, 135, 42, 173));
	temp.push_back(Rect(0, 47, 39, 91));
	temp.push_back(Rect(81, 45, 118, 87));
	temp.push_back(Rect(85, 0, 117, 37));
	temp.push_back(Rect(35, 174, 63, 208));
	temp.push_back(Rect(88, 127, 114, 159));
	temp.push_back(Rect(45, 45, 46, 46));

	listAnimation[0].Create(HOLD_1_EFFECT_PATH, temp.size(), temp, 0.005f, RIGHT);
	temp.clear();

	//Bullet3
	temp.push_back(Rect(64, 201, 112, 205));
	temp.push_back(Rect(0, 0, 44, 46));
	temp.push_back(Rect(40, 47, 80, 90));
	temp.push_back(Rect(82, 88, 118, 126));
	temp.push_back(Rect(0, 174, 34, 210));
	temp.push_back(Rect(43, 133, 87, 167));
	temp.push_back(Rect(64, 168, 106, 200));
	temp.push_back(Rect(45, 0, 84, 44));
	temp.push_back(Rect(0, 92, 36, 134));
	temp.push_back(Rect(37, 92, 81, 132));
	temp.push_back(Rect(0, 135, 42, 173));
	temp.push_back(Rect(0, 47, 39, 91));
	temp.push_back(Rect(81, 45, 118, 87));
	temp.push_back(Rect(85, 0, 117, 37));
	temp.push_back(Rect(35, 174, 63, 208));
	temp.push_back(Rect(88, 127, 114, 159));
	temp.push_back(Rect(45, 45, 46, 46));

	listAnimation[1].Create(HOLD_2_EFFECT_PATH, temp.size(), temp, 0.005f, RIGHT);
	temp.clear();

	this->id = HOLDATTACK;
	this->position = position;
	this->bulletType = 0;
	this->isDead = false;
	this->width = 15;
	this->height = 15;
	this->direct = RIGHT;
}

void HoldAttackEffect::Update(double time)
{
	
}

void HoldAttackEffect::Draw(double time)
{
	if (!isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->listAnimation[bulletType].Draw(transform.positionInViewport, this->direct, time, VT2(2, 2), transform.translation);
	}
}

void HoldAttackEffect::ChangeAnimation(int bulletType) {
	this->bulletType = bulletType;
}
