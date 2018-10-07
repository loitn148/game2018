#include "Ball.h"
#include <iostream>
using namespace std;


Ball::Ball() {
	this->id = BALL;
}


Ball::~Ball() {
}

Ball::Ball(VT3 position, float vx, float vy) {
	this->listBall = new Animation[1];
	std::vector<Rect> temp;

	temp.push_back(Rect(0, 0, 40, 40));

	this->listBall[0].Create(BALL_PATH, temp.size(), temp, 0.015f, RIGHT);
	temp.clear();

	this->currentState = 0;
	this->id = BALL;
	this->position = position;
	this->vx = vx;
	this->vy = vy;
	this->isDead = false;
	this->width = 40;
	this->height = 40;
	UpdateRect();
}

void Ball::Update(float time)
{
	Rect rectTop(-1, 0, 0, WIDTH);
	Rect rectBot(HEIGHT, 0, HEIGHT + 1, WIDTH);
	Rect rectLeft(0, -1, HEIGHT, 0);
	Rect rectRight(0, WIDTH, HEIGHT, WIDTH + 1);
	CollisionResult collisionTop, collisionBot, collisionLeft, collisionRight;
	CollisionResult colisionBar;
	float entryTimeX = time, entryTimeY = time;
	collisionTop = Collision::SweptAABB(this->GetRect(), VT2(this->GetVx(), this->GetVy()), rectTop, VT2(0, 0), time);
	collisionBot = Collision::SweptAABB(this->GetRect(), VT2(this->GetVx(), this->GetVy()), rectBot, VT2(0, 0), time);
	collisionLeft = Collision::SweptAABB(this->GetRect(), VT2(this->GetVx(), this->GetVy()), rectLeft, VT2(0, 0), time);
	collisionRight = Collision::SweptAABB(this->GetRect(), VT2(this->GetVx(), this->GetVy()), rectRight, VT2(0, 0), time);
	colisionBar = Collision::SweptAABB(this->GetRect(), VT2(this->GetVx(), this->GetVy()), bar->GetRect(), VT2(bar->GetVx(), bar->GetVy()), time);
	if (collisionTop.isCollision && collisionTop.directCollision == BOTTOM) {
		//this->vy = this->vy*collisionTop.entryTime;
		entryTimeY = collisionTop.entryTime;
	} else if (collisionBot.isCollision && collisionBot.directCollision == TOP) {
		//this->vy = this->vy*collisionBot.entryTime;
		entryTimeY = collisionBot.entryTime;
	} else if (collisionLeft.isCollision && collisionLeft.directCollision == RIGHT) {
		//this->vx = this->vx*collisionLeft.entryTime;
		entryTimeX = collisionLeft.entryTime;
	} else if (collisionRight.isCollision && collisionRight.directCollision == LEFT) {
		//this->vx = this->vx*collisionRight.entryTime;
		entryTimeX = collisionRight.entryTime;
	}

	if (colisionBar.isCollision &&
		(colisionBar.directCollision == LEFT || colisionBar.directCollision == RIGHT))
	{
		entryTimeX = colisionBar.entryTime;

	}
	else if (colisionBar.isCollision)
	{
		entryTimeY = colisionBar.entryTime;
	}
	this->position.x += this->vx*entryTimeX;
	this->position.y += this->vy*entryTimeY;

	if (colisionBar.isCollision &&
		(colisionBar.directCollision == LEFT || colisionBar.directCollision == RIGHT))
	{
		this->vx = 0.0f;
		this->vy = 0.0f;

	}
	else if (colisionBar.isCollision)
	{
		this->vx = 0.0f;
		this->vy = 0.0f;
	}

	
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

void Ball::Draw(float time)
{
	if (!this->isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->listBall[this->currentState].Draw(this->transform.positionInViewport, this->direct, time, VT2(1, 1), this->transform.translation);
	}
}

void Ball::SetBar(GameObject *b)
{
	this->bar = b;
}
