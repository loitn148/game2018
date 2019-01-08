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
#define WIDTH 565
#define HEIGHT 500
#define GAME_TITLE "MegaMan X3"

//POSITION
#define WORLD_X 18336  //6112
#define WORLD_Y 4512  //1504
#define CAMERA_START_X 1
#define CAMERA_START_Y 2784 //2862
#define MEGAMAN_START_X 100
#define MEGAMAN_START_Y 2500
#define MAP_BASE_Y 2386
#define MEGAMAN_WIDTH 50
#define MEGAMAN_HEIGHT 80
#define DELTA_CAMERA 20
#define BIGBOSS_POSITION_CALL_ENEMIES_LEFT_X 100
#define BIGBOSS_POSITION_CALL_ENEMIES_LEFT_Y 2600
#define BIGBOSS_POSITION_CALL_ENEMIES_RIGHT_X 500
#define BIGBOSS_POSITION_CALL_ENEMIES_RIGHT_Y 2600

//MEGAMAN SPEED
#define RUN_SPEED 500
#define JUMP_SPEED 1500
#define SWEEP_SPEED 1600
#define SWEEP_WALL_SPEED 500
#define START_SPEED_Y -1300
#define ACCELERATION_Y -300
#define ACCELERATION_X 300
#define ACCELERATION_SWEEP_Y -200

//KEY CODE
#define VK_A 0x41
#define VK_S 0x53

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
	START1 = 0,
	START2 = 1,
	STANDING = 2,
	STANDING_ATTACK = 3,
	RUNNING = 4,
	RUNNING_ATTACK = 5,
	JUMPING = 6,
	JUMPING_ATTACK = 7,
	SWEEPING = 8,
	SWEEPING_ATTACK = 9,
	SWEEPING_WALL = 10,
	SWEEPING_WALL_ATTACK = 11,
	JUMPING_FROM_WALL = 12,
	JUMPING_FROM_WALL_ATTACK = 13,
	FALLING = 14,
	FALLING_ATTACK = 15,
	HURT = 16
};

//BossFinal State
enum BigBossStates {
	START = 0,
	FLY = 1,
	PRICK = 2,
	CALL_ENEMIES = 3,
	DEAD = 4
};

//Object Game
enum Object {
	MEGAMAN,
	STATICOBJECT,
	ONEHITOBJECT,
	CAUTHANG,
	BULLET,
	NORMALBOSS,
	ONEGUN,
	ENEMYROCKET,
	ELEVATOR,
	BULLETENEMY,
	SMOKE,
	HOLDATTACK,
	BOSSFINAL,
	WINGS,
	ENEMY
};

enum OneGunStates{
	ENEMYJUMPING = 0,
	ENEMYSTANDING,
	ENEMYATTACK1,
	ENEMYATTACK2,

};

enum EnemyRocketStates{
	ENEMYROCKETSTANDING = 0,
	ENEMYROCKETATTACK1,
	ENEMYROCKETATTACK2,

};

enum EnemySweepingStates{
	ENEMYSWEEPINGNORMAL = 0,
	ENEMYSWEEPINGSHOOTING,

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
#define START1_PATH "Assets/megaman/start_1.png"
#define START2_PATH "Assets/megaman/start_2.png"
#define STAND_PATH "Assets/megaman/standing.png"
#define STAND_ATTACK_PATH "Assets/megaman/stand-attack.png"
#define RUN_PATH "Assets/megaman/running.png"
#define RUN_ATTACK_PATH "Assets/megaman/run_attack.png"
#define JUMP_PATH "Assets/megaman/jumping.png"
#define JUMP_ATTACK_PATH "Assets/megaman/jump_attack.png"
#define SWEEP_PATH "Assets/megaman/sweeping.png"
#define SWEEP_ATTACK_PATH "Assets/megaman/sweep_attack.png"
#define SWEEP_WALL_PATH "Assets/megaman/sweep_wall.png"
#define SWEEP_WALL_ATTACK_PATH "Assets/megaman/sweep_wall_attack.png"
#define JUMP_FROM_WALL_PATH "Assets/megaman/jump_from_wall.png"
#define JUMP_FROM_WALL_ATTACK_PATH "Assets/megaman/jump_from_wall_attack.png"
#define HURT_PATH "Assets/megaman/hurt.png"

#define BULLET_LV1_PATH "Assets/megaman/bullet_lv1.png"
#define BULLET_LV2_PATH "Assets/megaman/bullet_lv2.png"
#define BULLET_LV3_PATH "Assets/megaman/bullet_lv3.png"

#define SMOKE_EFFECT_PATH "Assets/megaman/smoke_effect.png"
#define HOLD_1_EFFECT_PATH "Assets/megaman/hold_bullet_2.png"
#define HOLD_2_EFFECT_PATH "Assets/megaman/hold_bullet_3.png"
#define HEALTH_PATH "Assets/megaman/health.png"
#define DESTROYED_EFFECT_PATH "Assets/destroyed.png"

#define ENEMIES_1 "Assets/enemies/running.png"

#define BOSSNORMAL "Assets/boss/boss_normal.png"
#define ELEVATOR1 "Assets/map/elevator1.png"

#define ENEMIES_1_JUMP		 "Assets/enemies/jump.png"
#define ENEMIES_1_STAND		 "Assets/enemies/stand.png"
#define ENEMIES_1_ATTACK1	 "Assets/enemies/attack1.png"
#define ENEMIES_1_ATTACK2	 "Assets/enemies/attack2.png"

#define ENEMIES_ROCKET_SHOOTING		 "Assets/enemies/shooting.png"
#define ENEMIES_ROCKET_STAND		 "Assets/enemies/EnemyRocketStand.png"

#define ENEMIES_SWEEPING_NORMAL		 "Assets/enemies/normal.png"
#define ENEMIES_SWEEPING_SHOOTING	 "Assets/enemies/Sweepingshooting.png"

#define BOSSFINAL_PATH "Assets/bossfinal/fly.png"
#define BOSSFINAL_PRICK_PATH "Assets/bossfinal/prick.png"
#define BOSSFINAL_DEAD_PATH "Assets/bossfinal/dead.png"
#define BOSSFINAL_CALL_ENEMIES_PATH "Assets/bossfinal/call_enemies.png"
#define WINGS_PATH "Assets/bossfinal/wing.png"
#define ENEMIES_PATH "Assets/bossfinal/enemies.png"


