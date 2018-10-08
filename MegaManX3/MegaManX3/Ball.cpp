#include "Ball.h"
#include <iostream>
using namespace std;


Ball::Ball() {
	this->id = BALL;
}


Ball::~Ball() {
}

Ball::Ball(VT3 position, double vx, double vy) {
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

void Ball::Update(double time) {
	Rect rectTop(HEIGHT + 1, 0, HEIGHT, WIDTH);
	Rect rectBot(0, 0, -1, WIDTH);
	Rect rectLeft(HEIGHT, -1, 0, 0);
	Rect rectRight(HEIGHT, WIDTH, 0, WIDTH + 1);
	CollisionResult collisionTop, collisionBot, collisionLeft, collisionRight;
	CollisionResult collisionBar, collisionBar2;
	double entryTimeX = time, entryTimeY = time;
	collisionTop = Collision::SweptAABB(this->GetRect(), VT2(this->GetVx(), this->GetVy()), rectTop, VT2(0, 0), time);
	collisionBot = Collision::SweptAABB(this->GetRect(), VT2(this->GetVx(), this->GetVy()), rectBot, VT2(0, 0), time);
	collisionLeft = Collision::SweptAABB(this->GetRect(), VT2(this->GetVx(), this->GetVy()), rectLeft, VT2(0, 0), time);
	collisionRight = Collision::SweptAABB(this->GetRect(), VT2(this->GetVx(), this->GetVy()), rectRight, VT2(0, 0), time);
	collisionBar = Collision::SweptAABB(this->GetRect(), VT2(this->GetVx(), this->GetVy()), bar->GetRect(), VT2(bar->GetVx(), bar->GetVy()), time);
	collisionBar2 = Collision::SweptAABB(this->GetRect(), VT2(this->GetVx(), this->GetVy()), bar2->GetRect(), VT2(bar->GetVx(), bar->GetVy()), time);
	if (collisionTop.isCollision && collisionTop.directCollision == TOP) {
		//this->vy = this->vy*collisionTop.entryTime;
		entryTimeY = collisionTop.entryTime;
	} else if (collisionBot.isCollision && collisionBot.directCollision == BOTTOM) {
		//this->vy = this->vy*collisionBot.entryTime;
		entryTimeY = collisionBot.entryTime;
	} else if (collisionLeft.isCollision && collisionLeft.directCollision == LEFT) {
		//this->vx = this->vx*collisionLeft.entryTime;
		entryTimeX = collisionLeft.entryTime;
	} else if (collisionRight.isCollision && collisionRight.directCollision == RIGHT) {
		//this->vx = this->vx*collisionRight.entryTime;
		entryTimeX = collisionRight.entryTime;
	}

	if (collisionBar.isCollision)
	{
		entryTimeX = collisionBar.entryTime;
	}
	if (collisionBar2.isCollision)
	{
		entryTimeX = collisionBar2.entryTime;
	}

	this->position.x += this->vx*entryTimeX;
	this->position.y += this->vy*entryTimeY;

	UpdateRect();

	if ((collisionBar.isCollision && (collisionBar.directCollision == LEFT || collisionBar.directCollision == RIGHT))
		|| (collisionBar2.isCollision && (collisionBar2.directCollision == LEFT || collisionBar2.directCollision == RIGHT)))
	{
		this->vx = -this->vx;
	}

	if ((collisionBar.isCollision && (collisionBar.directCollision == TOP || collisionBar.directCollision == BOTTOM))
		|| (collisionBar2.isCollision && (collisionBar2.directCollision == TOP || collisionBar2.directCollision == BOTTOM)))
	{
		this->vy = -this->vy;
	}
	
	if (collisionRight.isCollision) {
		this->position.x = WIDTH - this->width/2;
		this->vx = 0;
		this->vy = 0;
	}
	if (collisionLeft.isCollision) {
		this->position.x = this->width/2;
		this->vx = 0;
		this->vy = 0;
	}
	if (collisionBot.isCollision) {
		this->position.y = 0;
		this->vy = 400.0f;
	}
	if (collisionTop.isCollision) {
		this->position.y = HEIGHT - this->height;
		this->vy = -400.0f;
	}
}

void Ball::Draw(double time) {
	if (!this->isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->listBall[this->currentState].Draw(this->transform.positionInViewport, this->direct, time, VT2(1, 1), this->transform.translation);
	}
}

void Ball::SetBar(Bar* bar, Bar* bar2) {
	this->bar = bar;
	this->bar2 = bar2;
}
