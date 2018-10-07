#include "Bar.h"



Bar::Bar() {
	this->id = BAR;
}


Bar::~Bar() {
}

Bar::Bar(VT3 position, float vx, float vy) {
	this->listBar = new Animation[1];
	std::vector<Rect> temp;

	temp.push_back(Rect(0, 0, 20, 200));

	this->listBar[0].Create(BAR1_PATH, temp.size(), temp, 0.015f, RIGHT);
	temp.clear();

	this->currentState = 0;
	this->id = BAR;
	this->position = position;
	this->vx = vx;
	this->vy = vy;
	this->isDead = false;
	this->width = 200;
	this->height = 20;
	UpdateRect();
}

void Bar::Update(float time)
{
	Rect rectTop(-1, 0, 0, WIDTH);
	Rect rectBot(HEIGHT, 0, HEIGHT + 1, WIDTH);
	Rect rectLeft(0, -1, HEIGHT, 0);
	Rect rectRight(0, WIDTH, HEIGHT, WIDTH + 1);
	CollisionResult collisionTop, collisionRight;

	collisionTop = Collision::SweptAABB(this->GetRect(), VT2(this->GetVx(), this->GetVy()), rectTop, VT2(0, 0), time);
	collisionRight = Collision::SweptAABB(this->GetRect(), VT2(this->GetVx(), this->GetVy()), rectBot, VT2(0, 0), time);

	if (collisionTop.isCollision && collisionTop.directCollision == BOTTOM) {
		this->vy = this->vy*collisionTop.entryTime;
	}
	else if (collisionRight.isCollision && collisionRight.directCollision == TOP) {
		this->vy = this->vy*collisionRight.entryTime;
	}

	this->position.x += this->vx*time;
	this->position.y += this->vy*time;

	if (this->position.x + this->width / 2 >= WIDTH) {
		this->position.x = WIDTH - this->width / 2;
		this->vx = -400.0f;
	}
	if (this->position.x - this->width / 2 <= 0) {
		this->position.x = this->width / 2;
		this->vx = 400.0f;
	}
	if (this->position.y + this->height >= HEIGHT) {
		this->position.y = HEIGHT - this->height;
		this->vy = -400.0f;
	}
	if (this->position.y <= 0) {
		this->position.y = 0;
		this->vy = 400.0f;
	}
	UpdateRect();
}

void Bar::Draw(float time)
{
	if (!this->isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->listBar[this->currentState].Draw(this->transform.positionInViewport, this->direct, time, VT2(1, 1), this->transform.translation);
	}
}
