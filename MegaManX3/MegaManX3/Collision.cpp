#include "Collision.h"


CollisionResult Collision::SweptAABB(Rect rect1, VT2 v1, Rect rect2, VT2 v2, float time)
{
	v1.x = (v1.x - v2.x)*time; //Gia su v1 di chuyen, v2 dung yen
	v1.y = (v1.y - v2.y)*time;

	float xEntry, yEntry; //Khoang cach giua 2 vat khi chua va cham
	float xExit, yExit; //Khoang cach giua 2 vat sau khi va cham

	if (v1.x >= 0.0f)
	{
		xEntry = rect2.left - rect1.right;
		xExit = rect2.right - rect1.left;
	}
	else
	{
		xEntry = rect2.right - rect1.left;
		xExit = rect2.left - rect1.right;
	}

	if (v1.y >= 0.0f)
	{
		yEntry = rect2.bottom - rect1.top;
		yExit = rect2.top - rect1.bottom;
	}
	else
	{
		yEntry = rect2.top - rect1.bottom;
		yExit = rect2.bottom - rect1.top;
	}

	float txEntry, tyEntry; //Thoi gian den va cham
	float txExit, tyExit; //Thoi gian thoat khoi va cham

	if (v1.x == 0)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = xEntry / v1.x;
		txExit = xExit / v1.x;
	}

	if (v1.y == 0)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = yEntry / v1.y;
		tyExit = yExit / v1.y;
	}

	//Kiem tra va cham
	CollisionResult collisionResult;
	float entryTime = max(txEntry, tyEntry);
	float exitTime = min(txExit, tyExit);

	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f)
	{
		collisionResult.directCollision = NONE;
		collisionResult.isCollision = false;
	}
	else
	{
		collisionResult.isCollision = true;
		//Xac dinh huong va cham
		if (txEntry > tyEntry)
		{
			if (xEntry < 0.0f) //Right of rect2
			{
				collisionResult.directCollision = RIGHT;
			}
			else //Left of rect2
			{
				collisionResult.directCollision = LEFT;
			}
		}
		else
		{
			if (yEntry < 0.0f) //Top of rect2
			{
				collisionResult.directCollision = TOP;
			}
			else //Bottom of rect2
			{
				collisionResult.directCollision = BOTTOM;
			}
		}
	}
	collisionResult.entryTime = entryTime;
	collisionResult.exitTime = exitTime;
	collisionResult.remainingTime = 1.0f - entryTime;

	return collisionResult;
}

Collision::Collision()
{
}


Collision::~Collision()
{
}
