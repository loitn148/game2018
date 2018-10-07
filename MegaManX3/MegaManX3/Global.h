#pragma once

//LIBRARY
#define D3D LPDIRECT3D9
#define DEVICE LPDIRECT3DDEVICE9
#define SPRITE LPD3DXSPRITE 
#define SURFACE LPDIRECT3DSURFACE9 
#define TEXTURE LPDIRECT3DTEXTURE9
#define VT2 D3DXVECTOR2
#define VT3 D3DXVECTOR3
#define COLOR D3DCOLOR
#define C_XRGB D3DCOLOR_XRGB
#define MATRIX D3DXMATRIX
#define MATRIX D3DXMATRIX

//Window
#define WIDTH 800
#define HEIGHT 600
#define TITLE "Game PingPong"

//WORLD
#define WORLD_X 800
#define WORLD_Y 600

//Transform
struct Transform
{
	VT3 positionInViewport;
	VT2 translation;
	VT2 scale;
	VT2 scalingCenter;
};

//Object Game
enum Object {
	BAR,
	BALL
};

//Object Direct
enum Direct {
	LEFT = -1,
	RIGHT = 1,
	TOP = -2,
	BOTTOM = 2,
	NONE = 0
};

//Collision Result
struct CollisionResult
{
	float entryTime; //Thoi gian de xay ra va cham
	float remainingTime; //Thoi gian sau khi va cham
	float exitTime; //Thoi gian ket thuc va cham
	bool isCollision; //Kiem tra co xay ra va cham hay khong?
	Direct directCollision; //Huong va cham
	int indexObject; //Stt cua object trong list
};

//Object Path
#define BALL_PATH "Assets/ball.png"
#define BAR1_PATH "Assets/bar1.png"
#define BAR2_PATH "Assets/bar2.png"
#define MAP_PATH "Assets/wall.png"