#pragma once
#ifndef __QUADTREE__H__
#define __QUADTREE__H__

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include "GameObject.h"
#include "Rect.h"
#include "Collision.h"

class Quadtree
{
protected:
	Quadtree** Nodes;
	std::vector<GameObject*> listObject;
	int GetIndex(Rect body);
	void Split();
	bool IsContain(GameObject* obj);
	int level;
	Rect* region;
	
public:
	Quadtree(int level, Rect rectBound);
	~Quadtree();
	void Clear();
	void InsertObject(GameObject *obj);

	/*lay danh sach nhung Entity co kha nang xay ra va cham
	tra ve danh sach cac phan tu nam trong vung va cham */
	void GetEntitiesCollideAble(std::vector<GameObject*> &objectOut, GameObject *obj);

	void GetAllObjects(std::vector<GameObject*> &objectOut);

	int GetTotalObjects();

	Rect rectBound;
};

#endif // !__QUADTREE__H__



