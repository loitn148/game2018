#include "Camera.h"

Camera* Camera::instance = NULL;
Camera* Camera::GetInstance() {
	if (!Camera::instance) {
		Camera::instance = new Camera();
	}
	return Camera::instance;
}

void Camera::CameraOnWorld() {
	VT3 tl_position = position;
	VT3 tr_position = VT3(position.x + width, position.y, 0);
	VT3 br_position = VT3(position.x + width, position.y - height, 0);
	VT3 bl_position = VT3(position.x, position.y - height, 0);

	//TopLeft
	if (tl_position.x < 0)
		position.x = 0;
	if (tl_position.y > WORLD_Y)
		position.y = WORLD_Y;

	//TopRight
	if (tr_position.x > WORLD_X)
		position.x = WORLD_X - width;
	if (tr_position.y > WORLD_Y)
		position.y = WORLD_Y;

	//BottomRight
	if (br_position.x > WORLD_X)
		position.x = WORLD_X - width;
	if (br_position.y < 0)
		position.y = height;

	//BottomLeft
	if (bl_position.x < 0)
		position.x = 0;
	if (bl_position.y < 0)
		position.y = height;
	
	//camera flow pipe map
	if (position.x > 6237) {
		allowMove(true, true);
		if (position.y < 2200) {
			position.y = 2200;
		}
	}
	if (position.x > 3920) {
		if (position.x < 6237) {
			allowMove(true, false);
		}
	}

	if (position.x > 1705 && position.x < 5000) {
		if (position.y < 3910) {
			if (position.x < 3410) {
				position.x = 3410;
			}
			else if (position.x > 3920 && position.y > 2250) {
				position.x = 3920;
			}
		}
		if (position.y <= 2250) {
			position.y = 2200;
			allowMove(true, false);
		}
	}

	//Part 3
	if (position.y == 3910) {
		if ((position.x > 2650 && position.x < 3500) || (position.x > 3410 && position.x < 4420 && MegaManCharacters::GetInstance()->GetVy() < 0)) {
			allowMove(true, true);
		}
		//allowMove(true, false);
		if (position.x < 1705) {
			position.x = 1705;
		}
		if (position.x > 4600) {
			position.x = 4600;
		}
	}

	//Part 2
	if (position.y > 2784 && position.y < 3910 && position.x <= 1705) {
		allowMoveX = false;
		allowMoveY = true;
		position.x = 1705;
	}
	if (position.x == 1705) {
		if (position.y > 3910) {
			position.y = 3910;
		}
		if (position.y < 2784) {
			position.y = 2784;
		}
	}

	//Part 1
	if (position.x < 1705) {
		allowMoveX = true;
		allowMoveY = false;
		position.y = 2784;
	}
	
}

void Camera::Update(MegaManCharacters* megaMan)
{
	VT3 megaManPosition = megaMan->GetPosition();

	double halfWidth = (double) width / 2;
	double halfHeight = (double) height / 2;

	double cameraXCenter = position.x + halfWidth;
	double cameraYCenter = position.y - halfHeight;

	vx = 0;
	vy = 0;

	if (allowMoveX) {
		//Left
		if (megaManPosition.x < cameraXCenter - DELTA_CAMERA)
			vx = megaManPosition.x - cameraXCenter + DELTA_CAMERA;

		//Right
		if (megaManPosition.x > cameraXCenter + DELTA_CAMERA)
			vx = megaManPosition.x - cameraXCenter - DELTA_CAMERA;
	}

	if (allowMoveY) {
		//Top
		if (megaManPosition.y < cameraYCenter - DELTA_CAMERA - 150)
			vy = megaManPosition.y - cameraYCenter + DELTA_CAMERA + 150;

		//Bottom
		if (megaManPosition.y > cameraYCenter + DELTA_CAMERA)
			vy = megaManPosition.y - cameraYCenter - DELTA_CAMERA;
	}

	position.x += vx;
	position.y += vy;

	CameraOnWorld();
}

void Camera::SetPosition(VT3 position)
{
	this->position = position;
}

RECT Camera::GetRect()
{
	RECT rect;
	rect.left = position.x;
	rect.top = position.y;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;
	return rect;
}

VT3 Camera::GetPosition()
{
	return position;
}

void Camera::Create(VT3 position, int width, int height)
{
	this->position = position;
	this->width = width;
	this->height = height;
	allowMoveX = true;
	allowMoveY = false;
}

Camera::Camera() {
	position = VT3(CAMERA_START_X, CAMERA_START_Y, 0);
	width = WIDTH;
	height = HEIGHT;
}


Camera::~Camera() {
}

void Camera::allowMove(bool moveX, bool moveY) {
	allowMoveX = moveX;
	allowMoveY = moveY;
}
