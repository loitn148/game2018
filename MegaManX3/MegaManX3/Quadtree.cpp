#include "Quadtree.h"



Quadtree::Quadtree(int level, Rect rectBound)
{
	this->rectBound = rectBound;
	this->level = level;
}

void Quadtree::Clear()
{
	if (Nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (Nodes[i])
			{
				Nodes[i]->Clear();
				delete Nodes[i];
				Nodes[i] = nullptr;
			}
		}

		delete[] Nodes;
	}
}

void Quadtree::InsertObject(GameObject *obj)
{
	int index = GetIndex(obj->GetRect());

	//neu node ta ton tai thi insert vao node con
	if (Nodes != NULL)
	{
		if (index != -1)
		{
			Nodes[index]->InsertObject(obj);
			return;
		}
	}

	//luc nay entity nam giua 2 Bound nen se add vao node nay luon
	if (index == -1)
	{
		this->listObject.push_back(obj);
	}
	else
	{
		//node chua dc tao nen se tao va split roi moi insert
		if (Nodes == NULL)
		{
			Split();
		}

		Nodes[index]->InsertObject(obj);
	}
}

bool Quadtree::IsContain(GameObject *obj)
{
	RECT r = obj->GetRect();

	if (r.left >= rectBound.left && r.right <= rectBound.right && r.top <= rectBound.top && r.bottom >= rectBound.bottom)
	{
		return true;
	}

	return false;
}

void Quadtree::Split()
{
	//cat phan region (ranh gioi) ra thanh 4 phan bang nhau
	Nodes = new Quadtree *[4];

	Rect bound;

	int width = (rectBound.right - rectBound.left) / 2;
	int height = (rectBound.top - rectBound.bottom) / 2;

	//phan goc trai tren
	bound.left = rectBound.left;
	bound.right = bound.left + width;
	bound.top = rectBound.top;
	bound.bottom = bound.top - height;
	Nodes[0] = new Quadtree(level + 1, bound);

	//phan goc phai tren
	bound.left = rectBound.left + width;
	bound.right = bound.left + width;
	bound.top = rectBound.top;
	bound.bottom = bound.top - height;
	Nodes[1] = new Quadtree(level + 1, bound);

	//phan goc trai duoi
	bound.left = rectBound.left;
	bound.right = bound.left + width;
	bound.top = rectBound.top - height;
	bound.bottom = bound.top - height;
	Nodes[2] = new Quadtree(level + 1, bound);

	//phan goc phai duoi
	bound.left = rectBound.left + width;
	bound.right = bound.left + width;
	bound.top = rectBound.top - height;
	bound.bottom = bound.top - height;
	Nodes[3] = new Quadtree(level + 1, bound);
}

int Quadtree::GetTotalObjects()
{
	int total = listObject.size();

	if (Nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			total += Nodes[i]->GetTotalObjects();
		}
	}

	return total;
}

int Quadtree::GetIndex(Rect body)
{
	/*lay vi tri cua Entity
	0: nam trong Node con goc trai tren
	1: nam trong Node con goc phai tren
	2: nam trong Node con goc trai duoi
	3: nam trong Node con goc phai duoi
	-1: bi dinh > 2 node con*/

	float middleVerticle = rectBound.left + (rectBound.right - rectBound.left) / 2.0f;
	float middleHorizontal = rectBound.top - (rectBound.top - rectBound.bottom) / 2.0f;

	if (body.top < rectBound.top && body.bottom > middleHorizontal)
	{
		//nam phia ben tren
		if (body.left > rectBound.left && body.right < middleVerticle)
		{
			//nam phia ben trai
			return 0;
		}
		else if (body.left > middleVerticle && body.right < rectBound.right)
		{
			//nam phia ben phai
			return 1;
		}
	}
	else if (body.top < middleHorizontal && body.bottom > rectBound.bottom)
	{
		//nam phia ben duoi
		if (body.left > rectBound.left && body.right < middleVerticle)
		{
			//nam phia ben trai
			return 2;
		}
		else if (body.left > middleVerticle && body.right < rectBound.right)
		{
			//nam phia ben phai
			return 3;
		}
	}

	return -1;
}

void Quadtree::GetAllObjects(std::vector<GameObject*> &objectOut)
{
	for (auto child : listObject)
	{
		objectOut.push_back(child);
	}

	if (Nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			Nodes[i]->GetAllObjects(objectOut);
		}
	}
}

void Quadtree::GetEntitiesCollideAble(std::vector<GameObject*> &objectOut, GameObject *obj)
{
	int index = this->GetIndex(obj->GetRect());

	if (index != -1)
	{
		//nhung Entity o day se la nam tren 2 node con nen chung ta cung se lay de set va cham
		for (auto child : listObject)
		{
			objectOut.push_back(child);
		}

		if (Nodes != NULL)
		{
			//kiem tra va lay cac node trong node con
			Nodes[index]->GetEntitiesCollideAble(objectOut, obj);
		}
	}
	else
	{
		GetAllObjects(objectOut);
	}
}

Quadtree::~Quadtree()
{
}
