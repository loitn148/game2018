#include "Camera.h"

Camera* Camera::instance = NULL;
Camera* Camera::GetInstance() {
	if (!Camera::instance) {
		Camera::instance = new Camera();
	}
	return Camera::instance;
}

void Camera::CameraOnWorld() {
	VT3 tl_position = this->position;
	VT3 tr_position = VT3(this->position.x + this->width, this->position.y, 0);
	VT3 br_position = VT3(this->position.x + this->width, this->position.y - this->height, 0);
	VT3 bl_position = VT3(this->position.x, this->position.y - this->height, 0);

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

	//Row 1
	if (tl_position.x < 1700) {
		if (tl_position.y > 2784 || bl_position.y < 2284) {
			this->position.y = 2784;
		}
	}

}

void Camera::Update(MegaManCharacters* megaMan)
{
	VT3 megaManPosition = megaMan->GetPosition();

	double halfWidth = (double) this->width / 2;
	double halfHeight = (double) this->height / 2;

	double cameraXCenter = this->position.x + halfWidth;
	double cameraYCenter = this->position.y - halfHeight;

	this->vx = 0;
	this->vy = 0;

	//Left
	if (megaManPosition.x < cameraXCenter - DELTA_CAMERA)
		this->vx = megaManPosition.x - cameraXCenter + DELTA_CAMERA;

	//Right
	if (megaManPosition.x > cameraXCenter + DELTA_CAMERA)
		this->vx = megaManPosition.x - cameraXCenter - DELTA_CAMERA;

	//Top
	if (megaManPosition.y < cameraYCenter - DELTA_CAMERA)
		this->vy = megaManPosition.y - cameraYCenter + DELTA_CAMERA;

	//Bottom
	if (megaManPosition.y > cameraYCenter + DELTA_CAMERA)
		this->vy = megaManPosition.y - cameraYCenter - DELTA_CAMERA;


	this->position.x += this->vx;
	this->position.y += this->vy;

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

VT3 Camera::GetPosition()
{
	return this->position;
}

void Camera::Create(VT3 position, int width, int height)
{
	this->position = position;
	this->width = width;
	this->height = height;
}

Camera::Camera() {
	this->position = VT3(CAMERA_START_X, CAMERA_START_Y, 0);
	this->width = WIDTH;
	this->height = HEIGHT;
}


Camera::~Camera() {
}
