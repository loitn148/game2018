#include "Camera.h"

Camera* Camera::instance = NULL;
Camera* Camera::GetInstance() {
	if (!Camera::instance) {
		Camera::instance = new Camera();
	}
	return Camera::instance;
}

void Camera::CameraOnWorld() {
	D3DXVECTOR3 tl_position = this->position;
	D3DXVECTOR3 tr_position = D3DXVECTOR3(this->position.x + this->width, this->position.y, 0);
	D3DXVECTOR3 br_position = D3DXVECTOR3(this->position.x + this->width, this->position.y - this->height, 0);
	D3DXVECTOR3 bl_position = D3DXVECTOR3(this->position.x, this->position.y - this->height, 0);

	//TopLeft
	if (tl_position.x < 0)
		this->position.x = 0;
	if (tl_position.y > WORLD_Y)
		this->position.y = WORLD_Y;

	//TopRight
	if (tr_position.x > WORLD_X)
		this->position.x = WORLD_X - this->width;
	if (tr_position.y > WORLD_Y)
		this->position.y = WORLD_Y;

	//BottomRight
	if (br_position.x > WORLD_X)
		this->position.x = WORLD_X - this->width;
	if (br_position.y < 0)
		this->position.y = this->height;

	//BottomLeft
	if (bl_position.x < 0)
		this->position.x = 0;
	if (bl_position.y < 0)
		this->position.y = this->height;
}

void Camera::Update()
{
	/*
	Add code handle camera follow character here
	*/

	CameraOnWorld();
}

void Camera::SetPosition(VT3 position)
{
	this->position = position;
}

RECT Camera::GetRect()
{
	RECT rect;
	rect.left = this->position.x;
	rect.top = this->position.y;
	rect.right = rect.left + this->width;
	rect.bottom = rect.top + this->height;
	return rect;
}

D3DXVECTOR3 Camera::GetPosition()
{
	return this->position;
}

void Camera::Create(D3DXVECTOR3 position, int width, int height)
{
	this->position = position;
	this->width = width;
	this->height = height;
}

Camera::Camera() {
	this->position = VT3(0, HEIGHT, 0);
	this->width = WIDTH;
	this->height = HEIGHT;
}


Camera::~Camera() {
}
