#include "BossNormal.h"
#include "MegaManCharacters.h"
BossNormal::BossNormal()
{
	this->id = NORMALBOSS;
}


BossNormal::~BossNormal()
{
}

BossNormal::BossNormal(D3DXVECTOR3 position, double vx, double vy)
{
	animation = new Animation();

	std::vector<Rect> temp;

	temp.push_back(Rect(227, 700, 447, 920));
	temp.push_back(Rect(235, 0, 468, 233));
	temp.push_back(Rect(231, 468, 457, 695));
	temp.push_back(Rect(235, 234, 465, 465));
	temp.push_back(Rect(0, 468, 230, 699));
	temp.push_back(Rect(0, 700, 226, 926));
	temp.push_back(Rect(0, 0, 234, 233));
	temp.push_back(Rect(469, 0, 689, 219));
	temp.push_back(Rect(0, 234, 234, 467));

	animation->Create(BOSSNORMAL, temp.size(), temp, 0.01f, RIGHT);
	temp.clear();

	this->id = NORMALBOSS;
	this->position = position;
	this->angle = 0.1f;
	this->vx = vx;
	this->vy = vy;
	this->ax = 0;
	this->ay = 0;
	this->isDead = false;
	this->width = 70;
	this->height = 100;
	this->Life = 10;
	this->isAttack1 = false;
	this->isAttack2 = false;
	this->isAttack3 = false;
	this->isIntro = true;
	this->countAttack1 = 0;
	this->countAttack1 = 0;
	this->countAttack1 = 0;
	//this->rotateCenter = VT2(2300, 100);
	UpdateRect();
}

void BossNormal::UpdatePosition(double time)
{
	this->position.x += this->vx * time;
	this->position.y += this->vy * time;

	this->UpdateRect();

	this->vx += this->ax;
	this->vy += this->ay;
}

void BossNormal::Update(double time)
{
	if (isIntro == true &&
		(this->position.x - MegaManCharacters::GetInstance()->GetPosition().x) <= 400)
	{
		isIntro = false;
	}
	if (Collision::IsColliding(this->rectBound, MegaManCharacters::GetInstance()->GetRect()) 
		&& !MegaManCharacters::GetInstance()->isUndying) {
		MegaManCharacters::GetInstance()->SubLife(2);
	}
	if (!isIntro) {

		if (this->isAttack1)
		{
			if (this->position.x > 5400)
			{
				this->vx = -800;
				this->vy = -50;
				this->countAttack1++;
			}
			if (this->position.x < 5050)
			{
				this->vx = 800;
				this->vy = 50;
			}

			if (this->countAttack1 == 2)
			{
				this->isAttack2 = true;
				this->isAttack1 = false;
				this->isAttack3 = false;
				this->countAttack1 = 0;
			}
		}

		else if (this->isAttack2)
		{
			if (this->position.x > 5400)
			{
				this->vx = -800;
				this->vy = -50;
				this->countAttack2++;
			}
			if (this->position.x < 5050)
			{
				this->vx = 550;
				this->vy = -565;
			}
			if (this->position.x < 5200 && this->vx < 0 && this->vy < 0)
			{
				this->vx = -550;
				this->vy = 565;
			}
			if (this->position.y < 2350 && this->vx > 0 && this->vy < 0)
			{
				this->position.y = 2350;
				this->vx = 800;
				this->vy = 50;
			}
			if (this->countAttack2 >= 2)
			{
				this->isAttack3 = true;
				this->isAttack2 = false;
				this->isAttack1 = false;
				this->countAttack2 = 0;
				this->position.y = 2350;
			}
		}

		else if (this->isAttack3)
		{
			if (this->position.x > 5400 && vx > 0 && vy > 0)
			{
				this->position.x = 5400;
				this->vx = 100;
				this->vy = -800;
			}
			if (this->position.x < 5070 && vx < 0 && vy < 0)
			{
				this->position.x = 5070;
				this->vx = -100;
				this->vy = 800;
			}
			if (this->position.y > 2550 && vy > 0)
			{
				this->position.y = 2550;
				this->vx = 800;
				this->vy = 200;
			}
			if (this->position.y < 2370 && vy < 0 && vx > 0)
			{
				this->position.y = 2370;
				this->vx = -800;
				this->vy = -50;

				this->countAttack3++;
			}
			if (this->countAttack3 == 2)
			{
				this->isAttack1 = true;
				this->isAttack3 = false;
				this->isAttack2 = false;
				this->countAttack3 = 0;
			}
		}

		else
		{
			if (this->position.y > 2380)
			{
				this->vx = 50;
				this->vy = -800;
			}
			else
			{
				this->vx = -800;
				this->vy = -50;
				this->isAttack1 = true;
			}
		}

		UpdatePosition(time);
	}
}

void BossNormal::Draw(double time)
{
	if (!isDead /*&& checkCamera()*/)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->animation->Draw(transform.positionInViewport, this->direct, time, VT2(0.6, 0.6), transform.translation, C_XRGB(255, 255, 255), this->angle, this->rotateCenter);
	}
}

void BossNormal::SubLife(int sub) {
	this->Life -= sub;
	if (this->Life <= 0) {
		this->Life = 0;
		this->isDead = true;
	}
}