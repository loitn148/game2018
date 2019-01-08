#include "Enemy.h"



Enemy::Enemy()
{
	this->id = ENEMY;
}


Enemy::~Enemy()
{
}

Enemy::Enemy(D3DXVECTOR3 position, float vx, float vy, Direct direct)
{
	enemy = new Animation();

	std::vector<Rect> temp;

	temp.push_back(Rect(0, 23, 22, 42));
	temp.push_back(Rect(0, 43, 18, 62));
	temp.push_back(Rect(0, 0, 20, 22));

	enemy->Create(ENEMIES_PATH, temp.size(), temp, 0.05f, LEFT);
	temp.clear();

	this->id = ENEMY;
	this->direct = direct;
	this->position = position;
	this->vx = vx;
	this->vy = vy;
	this->isDead = false;
	this->width = 10;
	this->height = 10;
	UpdateRect();
}

void Enemy::Update(float time, MegaManCharacters *megaman)
{
	CollisionResult result;
	Attack(megaman);
	position.x += vx*time;
	position.y += vy*time;

	UpdateRect();
}

void Enemy::Draw(float time)
{
	if (!isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->enemy->Draw(transform.positionInViewport, this->direct, time, VT2(2, 2), transform.translation);
	}
}

void Enemy::Attack(MegaManCharacters *megaman)
{
	if (this->position.y < megaman->GetPosition().y)
	{
		this->vy = 0;
		this->vx = this->direct * abs(this->vx);
	}
	else if (this->position.y > megaman->GetPosition().y)
	{
		if (this->position.x < megaman->GetPosition().x)
		{
			this->direct = RIGHT;
		}
		else
		{
			this->direct = LEFT;
		}

		double angleAttack = abs(this->position.x - megaman->GetPosition().x) / abs(this->position.y - megaman->GetPosition().y);
		this->vy = -100;
		this->vx = (this->direct * angleAttack * abs(this->vy));
	}
	else
	{
		if (this->position.x = megaman->GetPosition().x)
		{
			this->vx = 0;
			this->vy = 0;
		}
	}
}

