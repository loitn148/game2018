#pragma once
#include "GameObject.h"
class GameEnemy :
	public GameObject
{
	VT3 BasePos;
	bool bIsDead;
	bool isCollide(RECT rect1, RECT rect2);
public:
	int nLife;
	VT3 GetBasePosition(){ return BasePos; };
	void  SetBasePos(VT3 BasePos){ this->BasePos = BasePos; };
	void SetDead(bool Dead){ bIsDead = Dead; };
	bool GetDead(){ return bIsDead; };
	bool checkCamera(int);
	GameEnemy();
	~GameEnemy();
};

