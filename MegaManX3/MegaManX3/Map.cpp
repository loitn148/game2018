#include "Map.h"



Map::Map() {
	this->position = VT3(0, HEIGHT, 0);
	LoadResource();
}


Map::~Map() {
}

Map::Map(int x, int y, int z) {
	this->position = VT3(x, y, z);
	LoadResource();
}

void Map::LoadResource()
{
	this->mapRect.left = 0;
	this->mapRect.top = 0;
	this->mapRect.right = WIDTH;
	this->mapRect.bottom = HEIGHT;

	this->mapTexture = GameGraphic::GetInstance()->LoadTexture(MAP_PATH, C_XRGB(0, 0, 0));
}

void Map::Draw() {
	VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());

	VT2 translation = VT2(-cameraPosition.x, -cameraPosition.y);

	VT3 inPosition = Viewport::GetInstance()->GetPositionInViewport(this->position);

	GameGraphic::GetInstance()->DrawTexture(this->mapTexture, this->mapRect, VT3(0, 0, 0), inPosition, VT2(1, 1), VT2(inPosition.x, inPosition.y), translation);
}
