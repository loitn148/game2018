#include "Blood.h"
#include <stdlib.h> 
#include <time.h> 

Blood::Blood()
{
}

Blood::Blood(D3DXVECTOR3 position)
{
	std::vector<Rect> temp;
	listAnimation= new Animation[2];
	temp.push_back(Rect(9, 11, 17, 19));
	temp.push_back(Rect(0, 0, 8, 10));
	temp.push_back(Rect(0, 11, 8, 21));
	temp.push_back(Rect(9, 0, 17, 10));

	this->listAnimation[0].Create("Assets/Blood/blood1.png", temp.size(), temp, 0.05f, RIGHT);
	temp.clear();
	temp.push_back(Rect(13, 17, 25, 31));
	temp.push_back(Rect(0, 0, 12, 16));
	temp.push_back(Rect(13, 0, 25, 16));
	temp.push_back(Rect(0, 17, 12, 33));

	this->listAnimation[1].Create("Assets/Blood/blood2.png", temp.size(), temp, 0.05f, RIGHT);
	temp.clear();
	vy = -300;
	this->id = BULLETENEMY;
	this->position = position;
	this->vx = 0;
	this->isDead = false;
	this->isCollision = false;
	this->direct = direct;
	this->width = 15;
	this->height = 35;
	int iSecret;

	srand(time(NULL));

	iSecret = rand() % 10 + 1;
	if (iSecret < 2)
	{
		Level = 2;
	}
	else
	{
		Level = 1;
	}
	UpdateRect();
}

void Blood::Update(double time)
{
	if (!isDead)
	{
		
		CollisionResult staticCollision;
		staticCollision = Collision::SweptAABB(rectBound,
			VT2(this->vx, this->vy),
			MegaManCharacters::GetInstance()->GetRect(),
			VT2(MegaManCharacters::GetInstance()->GetVx(), MegaManCharacters::GetInstance()->GetVy()),
			time);
		if (staticCollision.isCollision)
		{

			MegaManCharacters::GetInstance()->AddLife(Level * 4);
			this->isCollision = true;

		}
		position.x += vx*time;
		position.y += vy*time;
		if (this->isCollision == true) {
			this->isDead = true;
		}

		vector<GameObject*> listCollision;
		GameMap::GetInstance()->GetQuadtree()->GetEntitiesCollideAble(listCollision, this);
		double entryTime = time;
		for (int i = 0; i < listCollision.size(); i++) {
			staticCollision = Collision::SweptAABB(this->rectBound, VT2(this->vx, this->vy), listCollision[i]->GetRect(), VT2(listCollision[i]->GetVx(), listCollision[i]->GetVy()), time);
			if (staticCollision.isCollision) {
				if (listCollision[i]->GetId() == Object::STATICOBJECT)
				{
					vy = 0;
				}
			}
		}

		position.x += vx*entryTime;

		UpdateRect();
	}

}

void Blood::Draw(double time)
{
	if (!isDead)
	{
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->listAnimation[Level-1].Draw(transform.positionInViewport, this->direct, time, VT2(2, 2), transform.translation);
	}
}


Blood::~Blood()
{
}
