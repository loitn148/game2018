#pragma once
#ifndef __ENEMYONEGUNDATA__H__
#define __ENEMYONEGUNDATA__H__
class EnemyOneGun;
class EnemyOneGunState;


class EnemyOneGunData
{
public:
	EnemyOneGun* m_EnemyOneGun;
	EnemyOneGunState* m_EnemyOneGunState;

	EnemyOneGunData();
	~EnemyOneGunData();
};
#endif
