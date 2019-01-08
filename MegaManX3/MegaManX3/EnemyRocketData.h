#pragma once
#ifndef __ENEMYROCKETDATA__H__
#define __ENEMYROCKETDATA__H__
class EnemyRocket;
class EnemyRocketState;

class EnemyRocketData
{
public:
	EnemyRocketData(){}
	~EnemyRocketData(){}

	EnemyRocket* m_EnemyRocket;
	EnemyRocketState* m_EnemyRocketState;
};
#endif
