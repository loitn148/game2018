#include "Rect.h"



D3DXVECTOR3 Rect::GetCenter()
{
	return this->center;
}

Rect::Rect(int top, int left, int bottom, int right, VT3 deltaCenter) {
	this->top = top;
	this->left = left;
	this->bottom = bottom;
	this->right = right;

	this->center = VT3((right - left) / 2 + deltaCenter.x, bottom - top + deltaCenter.y, 0);
}

Rect::Rect() {
}


Rect::~Rect() {
}