#include "Viewport.h"



Viewport::Viewport() {
	this->x = 0;
	this->y = HEIGHT;
}


Viewport::~Viewport() {
}

Viewport* Viewport::instance = NULL;
Viewport* Viewport::GetInstance() {
	if (!Viewport::instance) {
		Viewport::instance = new Viewport();
	}
	return Viewport::instance;
}

void Viewport::Init(int x, int y) {
	this->x = x;
	this->y = y;
}

int Viewport::GetX() {
	return this->x;
}

int Viewport::GetY() {
	return this->y;
}

VT3 Viewport::GetPositionInViewport(VT3 worldPosition) {
	worldPosition.z = 1;
	MATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1.0f;
	matrix._41 = -this->x;
	matrix._42 = this->y;

	D3DXVECTOR4 viewport;
	D3DXVec3Transform(&viewport, &worldPosition, &matrix);

	VT3 positionInViewport = VT3(viewport.x, viewport.y, 0);
	return positionInViewport;
}
