#include "Collision.h"
#include <math.h>

bool Collision::IsColliding(Rect rect1, Rect rect2) {
	double left = rect2.left - rect1.right;
	double top = rect2.top - rect1.bottom;
	double right = rect2.right - rect1.left;
	double bottom = rect2.bottom - rect1.top;

	return !(left > 0.0f || right < 0.0f || top < 0.0f || bottom > 0.0f);
}

Rect Collision::GetSweptBroadphaseRect(Rect rect, VT2 velocity, double time) {
	double dx = velocity.x*time;
	double dy = velocity.y*time;

	Rect newRect(rect.top + dy, rect.left + dx, rect.bottom + dy, rect.right + dx);

	double top = rect.top > newRect.top ? rect.top : newRect.top;
	double left = rect.left < newRect.left ? rect.left : newRect.left;
	double bottom = rect.bottom < newRect.bottom ? rect.bottom : newRect.bottom;
	double right = rect.right > newRect.right ? rect.right : newRect.right;

	return Rect(top, left, bottom, right);
}

CollisionResult Collision::SweptAABB(Rect rect1, VT2 v1, Rect rect2, VT2 v2, double time) {
	
	CollisionResult collisionResult;

	Rect rect = GetSweptBroadphaseRect(rect1, v1, time);

	if (!IsColliding(rect, rect2))
	{
		collisionResult.directCollision = NONE;
		collisionResult.isCollision = false;
		return collisionResult;
	}

	v1.x = v1.x - v2.x; //Gia su v1 di chuyen, v2 dung yen
	v1.y = v1.y - v2.y;

	double xEntry, yEntry; //Khoang cach giua 2 vat khi chua va cham
	double xExit, yExit; //Khoang cach giua 2 vat sau khi va cham

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

	double txEntry, tyEntry; //Thoi gian den va cham
	double txExit, tyExit; //Thoi gian thoat khoi va cham

	if (v1.x == 0.0f)
	{
		txEntry = -std::numeric_limits<double>::infinity();
		txExit = std::numeric_limits<double>::infinity();
	}
	else
	{
		txEntry = xEntry / v1.x;
		txExit = xExit / v1.x;
	}

	if (v1.y == 0.0f)
	{
		tyEntry = -std::numeric_limits<double>::infinity();
		tyExit = std::numeric_limits<double>::infinity();
	}
	else
	{
		tyEntry = yEntry / v1.y;
		tyExit = yExit / v1.y;
	}

	//Kiem tra va cham
	double entryTime = max(txEntry, tyEntry);
	double exitTime = min(txExit, tyExit);

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
			if (xEntry > 0.0f) //Right of rect1
			{
				collisionResult.directCollision = RIGHT;
			}
			else //Left of rect1
			{
				collisionResult.directCollision = LEFT;
			}
		}
		else
		{
			if (yEntry > 0.0f) //Top of rect1
			{
				collisionResult.directCollision = TOP;
			}
			else //Bottom of rect1
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
