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
	
	////camera flow pipe map
	//if (position.x > 6237) {
	//	allowMove(true, true);
	//	if (position.y < 2200) {
	//		position.y = 2200;
	//	}
	//}
	//if (position.x > 3920) {
	//	if (position.x < 6237) {
	//		allowMove(true, false);
	//	}
	//}

	//if (position.x > 1705 && position.x < 5000) {
	//	if (position.y < 3910) {
	//		if (position.x < 3410) {
	//			position.x = 3410;
	//		}
	//		else if (position.x > 3920 && position.y > 2250) {
	//			position.x = 3920;
	//		}
	//	}
	//	if (position.y <= 2250) {
	//		position.y = 2200;
	//		allowMove(true, false);
	//	}
	//}

	////Part 3
	//if (position.y == 3910) {
	//	if ((position.x > 2650 && position.x < 3500) || (position.x > 3410 && position.x < 4420 && MegaManCharacters::GetInstance()->GetVy() < 0)) {
	//		allowMove(true, true);
	//	}
	//	//allowMove(true, false);
	//	if (position.x < 1705) {
	//		position.x = 1705;
	//	}
	//	if (position.x > 4600) {
	//		position.x = 4600;
	//	}
	//}

	////Part 2
	//if (position.y > 2784 && position.y < 3910 && position.x <= 1705) {
	//	allowMoveX = false;
	//	allowMoveY = true;
	//	position.x = 1705;
	//}
	//if (position.x == 1705) {
	//	if (position.y > 3910) {
	//		position.y = 3910;
	//	}
	//	if (position.y < 2784) {
	//		position.y = 2784;
	//	}
	//}

	////Part 1
	//if (position.x < 1705) {
	//	allowMoveX = true;
	//	allowMoveY = false;
	//	position.y = 2784;
	//}

	if (state == 1) {
		allowMove(true, false);
	}
	else if (state == 2) {
		allowMove(false, true);
		if (position.y < 2784) {
			position.y = 2784;
		}
		if (position.x < 1705 || position.x > 1705) {
			position.x = 1705;
		}
	}
	else if (state == 3) {
		if (position.x < 1705) {
			position.x = 1705;
		}
		else if (position.x < 2770 || (position.x > 2900 && position.x < 3430) || position.x > 4000) {
			allowMove(true, false);
		}
		else if (position.x > 4555) {
			position.x = 4555;
		}
		else {
			allowMove(true, true);
		}
	} 
	else if (state == 4) {
		if (position.x < 2770) {
			position.x = 2770;
		}
		if (position.x > 2900) {
			position.x = 2900;
		}
		if (position.y < 3910) {
			position.y = 3910;
		}
	}
	else if (state == 5) {
		if (position.x < 3430) {
			position.x = 3430;
		} else if (position.x > 4000) {
			position.x = 4000;
		}

		if (position.y < 2250) {
			position.y = 2200;
		} else if (position.y > 3910) {
			position.y = 3910;
		}
	}
	else if (state == 6) {
		allowMove(true, false);
	}
	else if (state == 7) {
		if (position.x > 12550) {
			allowMove(true, false);
			if (position.x > 13770) {
				position.x = 13770;
			}
		}
		else {
			allowMove(true, true);
			if (position.x < 6350) {
				position.x < 6350;
			}
			
		}

		if (position.y < 2250) {
			position.y = 2200;
		}
		else if (position.y > 2800) {
			position.y = 2800;
		}
	}
	else if (state == 8) {
		allowMove(true, true);
		if (position.y < 500) {
			position.y = 500;
		}
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

	if (position.x < 1705 && position.y == 2784) {
		state = 1;
	}
	else if (position.x == 1705 && position.y > 2784 && position.y < 3910) {
		state = 2;
	}
	else if (position.x >= 1705 && position.x < 4555 && position.y == 3910) {
		state = 3;
	}
	else if (position.x >= 2770 && position.x <= 2900 && position.y > 3910) {
		state = 4;
	}
	else if (position.x > 3430 && position.x < 4000 && position.y < 3910) {
		state = 5;
	}
	else if (position.x >= 4000 && position.x < 6350 && position.y == 2200) {
		state = 6;
	}
	else if (position.x >= 6350 && position.x < 13770 && position.y >= 2200) {
		state = 7;

		if (megaManPosition.y < 1800) {
			state = 8;
		}
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
	rect.bottom = rect.top - height;
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
	state = 7;
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
