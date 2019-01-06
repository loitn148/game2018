#include "GameEnemy.h"
#include "Camera.h"


GameEnemy::GameEnemy()
{
}

bool GameEnemy::checkCamera(int time)
{
	return true;
//	return Collision::IsColliding(rectBound, Camera::GetInstance()->GetRect());

}

bool GameEnemy::isCollide(RECT rect1, RECT rect2)
{
	if (rect1.left > rect2.left && rect1.right < rect2.right && rect1.top > rect2.top && rect1.bottom < rect2.bottom)
	{
		return true;
	}

	return false;
}

GameEnemy::~GameEnemy()
{
}
