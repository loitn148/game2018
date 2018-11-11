#pragma once
#include <d3dx9.h>
#include "WriteLog.h"
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

#define KEYBOARD_BUFFER_SIZE 1024

//Window
#define WIDTH 600
#define HEIGHT 500
#define GAME_TITLE "MegaMan X3"

//POSITION
#define WORLD_X 17664  //5888
#define WORLD_Y 4590  //1530
#define CAMERA_START_X 0
#define CAMERA_START_Y 4590 //2865
#define MEGAMAN_START_X 30
#define MEGAMAN_START_Y 2580
#define MEGAMAN_WIDTH 35
#define MEGAMAN_HEIGHT 20
#define DELTA_CAMERA 50

//Transform
struct Transform
{
	D3DXVECTOR3 positionInViewport;
	D3DXVECTOR2 translation;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 scalingCenter;
};

//MegaMan State
enum CharactersStates {
	STANDING = 0,
	RUNNING = 1,
	JUMPING = 2,
};

//Object Game
enum Object {
	MEGAMAN
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
	double entryTime; //Thoi gian de xay ra va cham
	double remainingTime; //Thoi gian sau khi va cham
	double exitTime; //Thoi gian ket thuc va cham
	bool isCollision; //Kiem tra co xay ra va cham hay khong?
	Direct directCollision; //Huong va cham
	int indexObject; //Stt cua object trong list
};

//Object Path
#define MAP_PATH "Assets/map/map.tmx"
#define STAND_PATH "Assets/megaman/standing.png"
#define RUN_PATH "Assets/megaman/running.png"
#define JUMP_PATH "Assets/megaman/jumping.png"

#define ENEMIES_1 "Assets/enemies/running.png"