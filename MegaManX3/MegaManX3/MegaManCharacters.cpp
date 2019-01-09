#include "MegaManCharacters.h"
#include "SmokeEffect.h"
#include "HoldAttackEffect.h"
#include "MegaManHealth.h"
#include "DestroyedEffect.h"



MegaManCharacters* MegaManCharacters::instance = NULL;
MegaManCharacters* MegaManCharacters::GetInstance() {
	if (!MegaManCharacters::instance) {
		MegaManCharacters::instance = new MegaManCharacters();
	}
	return MegaManCharacters::instance;
}

MegaManCharacters::MegaManCharacters() {
	this->id = MEGAMAN;
	this->megaManData = new MegaManData();
	this->megaManData->megaMan = this;
}

void MegaManCharacters::Init(HINSTANCE hInstance, HWND hWnd) {
	this->hInstance = hInstance;
	this->hWnd = hWnd;
	this->id = MEGAMAN;
	this->direct = RIGHT;
	this->position = VT3(MEGAMAN_START_X, MEGAMAN_START_Y, 0);
	this->vx = this->vy = 0;
	this->ax = 0;
	this->ay = ACCELERATION_Y;
	this->width = MEGAMAN_WIDTH;
	this->height = MEGAMAN_HEIGHT;
	this->isAttacking = false;
	this->isJumping = false;
	this->isFalling = false;
	this->isDestroying = false;
	this->isRightLeftKeyDown = false;
	this->holdAttack = 0.0f;
	this->listAnimation = new Animation[17];
	this->Life = 16;
	this->healthDraw = MegaManHealth::GetInstance();
	this->healthDraw->SetHealth(this->Life);
	this->isUndying = true;
	this->undyingDuration = 0.0f;

	this->megaManData = new MegaManData();
	this->megaManData->megaMan = this;
	this->SetState(new Start1State(this->megaManData));

	this->UpdateRect();
	this->SetListAnimation();
}

void MegaManCharacters::UpdatePosition(double time)
{
	this->position.x += this->vx * time;
	this->position.y += this->vy * time;

	this->UpdateRect();

	this->vx += this->ax;
	this->vy += this->ay;
}

void MegaManCharacters::Update(double time)
{
	if (!isDestroying) {
		vector<GameObject*> listCollision;
		GameMap::GetInstance()->GetQuadtree()->GetEntitiesCollideAble(listCollision, this);
		CollisionResult staticCollision;
		double entryTime = time;
		int deltaBottom = MEGAMAN_WIDTH;
		for (int i = 0; i < listCollision.size(); i++) {
			if (listCollision[i]->GetId() == ONEGUN || listCollision[i]->GetId() == ENEMYROCKET
				|| listCollision[i]->GetId() == BOSSFINAL || listCollision[i]->GetId() == NORMALBOSS
				|| listCollision[i]->GetId() == ENEMY) {
				if (Collision::IsColliding(this->rectBound, listCollision[i]->GetRect()) && !isUndying){
					this->SubLife(2);
				}
			}
			else {
				staticCollision = Collision::SweptAABB(this->rectBound, VT2(this->vx, this->vy), listCollision[i]->GetRect(), VT2(listCollision[i]->GetVx(), listCollision[i]->GetVy()), time);
			if (staticCollision.isCollision) {
				if (listCollision[i]->GetId() == ONEHITOBJECT) {
					if (currentState != HURT) {
						this->SubLife(16);
					}
				}
				else {
					entryTime = staticCollision.entryTime;

					switch (staticCollision.directCollision)
					{
					case BOTTOM:
						this->position.y += this->vy * entryTime;
						this->UpdateRect();

						if (this->direct == RIGHT) {
							deltaBottom = listCollision[i]->GetRect().right - this->rectBound.left;
						}
						else if (this->direct == LEFT) {
							deltaBottom = this->rectBound.right - listCollision[i]->GetRect().left;
						}

						this->ay = ACCELERATION_Y;
						this->vy = 0;
						//Start 1 -> Start2
						if (this->currentState == START1) {
							this->SetState(new Start2State(this->megaManData));
						}
						//jumping, jumping attack, falling, falling attack -> vy = 0
						else if (this->currentState == JUMPING || this->currentState == JUMPING_ATTACK ||
							this->currentState == FALLING || this->currentState == FALLING_ATTACK ||
							this->currentState == JUMPING_FROM_WALL || this->currentState == JUMPING_FROM_WALL_ATTACK) {
							this->vy = 0;
							this->isFalling = false;
							this->isJumping = false;
						}
						else if (this->currentState == RUNNING_ATTACK || this->currentState == RUNNING
							|| this->currentState == STANDING || this->currentState == STANDING_ATTACK
							|| this->currentState == SWEEPING || this->currentState == SWEEPING_ATTACK) {
							if (deltaBottom <= MEGAMAN_WIDTH / 5) {
								this->SetPosition(VT3(this->position.x + MEGAMAN_WIDTH / 5, this->position.y, 0));
								if (listCollision[i]->GetId() != CAUTHANG) {
									this->SetState(new FallingState(this->megaManData));
								}
							}
							else {
								this->vy = 0;
							}
						}
						//else ->standing
						else {
							this->SetState(new StandingState(this->megaManData));
						}
						break;
					case TOP:
						this->position.y += this->vy * entryTime;
						this->UpdateRect();

						this->vy = 0;
						break;
					case RIGHT:
					case LEFT:
						this->position.x += this->vx * entryTime;
						this->UpdateRect();

						if (listCollision[i]->GetId() == CAUTHANG) {
							this->position.y += listCollision[i]->GetHeight() + 3;
							this->position.x += this->direct * 3;
							this->UpdateRect();
							this->vx = 0;
						}
						else {
							if (this->currentState == JUMPING || this->currentState == JUMPING_ATTACK
								|| this->currentState == JUMPING_FROM_WALL || this->currentState == JUMPING_FROM_WALL_ATTACK) {
								this->SetState(new SweepingWallState(this->megaManData));
							}
							this->vx = 0;
						}
						break;
					default:
						break;
					}
				}
			}
			}
		}

		this->UpdatePosition(time);

		if (this->listBullet.size() > 0)
		{
			for (size_t i = 0; i < this->listBullet.size(); i++)
			{
				if (!this->listBullet[i]->GetIsDead())
				{
					this->listBullet[i]->Update(time);
					/*free(this->listBullet[i]);
					this->listBullet[i] = nullptr;*/
				}
				/*else
					this->listBullet[i]->Update(time);*/
			}
		}

		if (this->listSmokeEff.size() > 0)
		{
			for (size_t i = 0; i < this->listSmokeEff.size(); i++)
			{
				if (!this->listSmokeEff[i]->GetIsDead())
				{
					this->listSmokeEff[i]->Update(time);
				}
			}
		}

		if (this->holdAttackEffect) {
			this->holdAttackEffect->SetPosition(this->position);

			if (this->holdAttackEffect->GetIsDead() == true) {
				free(this->holdAttackEffect);
				this->holdAttackEffect = nullptr;
			}
		}

		if (this->isUndying) {
			this->undyingDuration += time;
			if (this->undyingDuration >= 1.5f) {
				this->isUndying = false;
				this->undyingDuration = 0.0f;
			}
		}

		if (this->healthDraw) {
			this->healthDraw->Update(time);
		}

		if (this->megaManData->megaManState) {
			this->megaManData->megaManState->Update(time);
		}
	}
	else {
		if (this->destroyedEffect) {
			destroyedEffect->Update(time);
			if (destroyedEffect->GetIsDead()) {
				this->isDead = true;
			}
		}
	}
}

void MegaManCharacters::HandleKeyboard(std::map<int, bool> keys) {
	if (!isDestroying) {
		if (this->megaManData->megaManState) {
			this->megaManData->megaManState->HandleKeyboard(keys);
		}
	}
}

void MegaManCharacters::SetState(MegaManState *newState)
{
	delete this->megaManData->megaManState;

	this->megaManData->megaManState = newState;

	this->currentState = newState->GetState();
}

void MegaManCharacters::OnKeyDown(int keyCode) {
	if (!isDestroying) {
		if (keyCode == VK_RIGHT || keyCode == VK_LEFT) {

			this->isRightLeftKeyDown = true;

			if (currentState == STANDING)
			{
				this->SetState(new RunningState(this->megaManData));
			}
			else if (currentState == STANDING_ATTACK) {
				this->SetState(new RunningAttackState(this->megaManData));
			}

			if (currentState != SWEEPING && currentState != SWEEPING_ATTACK) {
				if (keyCode == VK_RIGHT) {
					this->direct = RIGHT;
					this->vx = RUN_SPEED;
				}
				else {
					this->direct = LEFT;
					this->vx = -RUN_SPEED;
				}
			}
		}
		if (keyCode == VK_A) {
			this->holdAttack += 0.25f;

			if (this->holdAttack >= 0.5f) {
				if (!this->holdAttackEffect) {
					this->holdAttackEffect = new HoldAttackEffect(VT3(this->position.x, this->position.y + 40, 0), 0);
				}
			}

			if (this->holdAttack >= 3.5f) {
				this->holdAttackEffect->ChangeAnimation(1);
			}
		}
	}
}

void MegaManCharacters::OnKeyUp(int keyCode) {
	if (!isDestroying) {
		if (keyCode == VK_RIGHT || keyCode == VK_LEFT) {
			this->isRightLeftKeyDown = false;
			if (currentState == RUNNING || currentState == RUNNING_ATTACK)
			{
				this->SetState(new StandingState(this->megaManData));
			}
			if (currentState == JUMPING || currentState == JUMPING_ATTACK ||
				currentState == JUMPING_FROM_WALL || currentState == JUMPING_FROM_WALL_ATTACK ||
				currentState == FALLING || currentState == FALLING_ATTACK
				)
			{
				this->vx = 0;
			}
		}

		if (keyCode == VK_A) {
			int index = listAnimation[currentState].GetIndex();
			switch (currentState)
			{
			case STANDING:
				this->SetState(new StandingAttackState(this->megaManData));
				break;
			case RUNNING:
				this->listAnimation[RUNNING_ATTACK].SetIndex(index);
				this->SetState(new RunningAttackState(this->megaManData, false));
				break;
			case JUMPING:
				this->listAnimation[JUMPING_ATTACK].SetIndex(index);
				this->SetState(new JumpingAttackState(this->megaManData, false));
				break;
			case SWEEPING:
				this->listAnimation[SWEEPING_ATTACK].SetIndex(index);
				this->SetState(new SweepingAttackState(this->megaManData, false));
				break;
			case SWEEPING_WALL:
				this->listAnimation[SWEEPING_WALL_ATTACK].SetIndex(index);
				this->SetState(new SweepingWallAttackState(this->megaManData, false));
				break;
			case JUMPING_FROM_WALL:
				this->listAnimation[JUMPING_FROM_WALL_ATTACK].SetIndex(index);
				this->SetState(new JumpingFromWallAttackState(this->megaManData, false));
				break;
			case FALLING:
				this->listAnimation[FALLING_ATTACK].SetIndex(index);
				this->SetState(new FallingAttackState(this->megaManData, false));
				break;
			default:
				break;
			}

			if (this->holdAttack >= 3.5f) {
				this->CreateBullet(3);
			}
			else if (this->holdAttack >= 1.0f) {
				this->CreateBullet(2);
			}
			else if (this->holdAttack < 1.0f) {
				this->CreateBullet(1);
			}
			this->holdAttack = 0.0f;
			if (this->holdAttackEffect) {
				this->holdAttackEffect->SetIsDead(true);
			}
		}
	}
}

void MegaManCharacters::Draw(double time) {
	if (!isDestroying) {
		this->transform.positionInViewport = this->GetPositionInViewport();
		VT3 cameraPosition = Viewport::GetInstance()->GetPositionInViewport(Camera::GetInstance()->GetPosition());
		this->transform.translation = VT2(-cameraPosition.x, -cameraPosition.y);

		this->listAnimation[this->currentState].Draw(transform.positionInViewport, this->direct, time, VT2(2.2, 2.5), transform.translation, C_XRGB(255, 255, 255));

		if (this->listBullet.size() > 0)
		{
			for (size_t i = 0; i < this->listBullet.size(); i++)
			{
				this->listBullet[i]->Draw(time);
			}
		}

		if (this->listSmokeEff.size() > 0)
		{
			for (size_t i = 0; i < this->listSmokeEff.size(); i++)
			{
				this->listSmokeEff[i]->Draw(time);
			}
		}

		if (this->holdAttackEffect)
		{
			this->holdAttackEffect->Draw(time);
		}

		if (this->healthDraw) {
			this->healthDraw->Draw(time);
		}
	}
	else {
		if (this->destroyedEffect) {
			this->destroyedEffect->Draw(time);
		}
	}
}

void MegaManCharacters::SetListAnimation() {
	std::vector<Rect> temp;

	//START1
	temp.push_back(Rect(0, 0, 48, 8));

	this->listAnimation[START1].Create(START1_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();

	//START2
	temp.push_back(Rect(40, 31, 69, 53));
	temp.push_back(Rect(0, 0, 42, 30));
	temp.push_back(Rect(0, 31, 39, 61));
	temp.push_back(Rect(0, 62, 36, 92));
	temp.push_back(Rect(0, 93, 34, 123));
	temp.push_back(Rect(43, 0, 75, 30));

	this->listAnimation[START2].Create(START2_PATH, temp.size(), temp, 0.03f, RIGHT);
	temp.clear();

	//STANDING
	temp.push_back(Rect(0, 0, 34, 30));
	temp.push_back(Rect(0, 31, 34, 61));
	temp.push_back(Rect(0, 62, 34, 92));
	temp.push_back(Rect(0, 93, 34, 123));

	this->listAnimation[STANDING].Create(STAND_PATH, temp.size(), temp, 0.015f, RIGHT);
	temp.clear();

	//STANDING_ATTACK
	temp.push_back(Rect(0, 0, 34, 30));
	temp.push_back(Rect(0, 31, 34, 60));

	this->listAnimation[STANDING_ATTACK].Create(STAND_ATTACK_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();


	//RUNNING
	temp.push_back(Rect(70, 53, 104, 73));
	temp.push_back(Rect(0, 103, 35, 126));
	temp.push_back(Rect(0, 70, 34, 102));
	temp.push_back(Rect(0, 0, 33, 34));
	temp.push_back(Rect(69, 0, 102, 26));
	temp.push_back(Rect(35, 61, 69, 83));
	temp.push_back(Rect(69, 27, 104, 52));
	temp.push_back(Rect(34, 0, 68, 30));
	temp.push_back(Rect(0, 35, 33, 69));
	temp.push_back(Rect(34, 31, 67, 60));

	this->listAnimation[RUNNING].Create(RUN_PATH, temp.size(), temp, 0.015f, RIGHT);
	temp.clear();

	//RUNNING_ATTACK
	temp.push_back(Rect(0, 113, 34, 142));
	temp.push_back(Rect(35, 71, 70, 103));
	temp.push_back(Rect(0, 77, 34, 112));
	temp.push_back(Rect(0, 0, 33, 38));
	temp.push_back(Rect(34, 36, 67, 70));
	temp.push_back(Rect(71, 70, 105, 101));
	temp.push_back(Rect(68, 36, 103, 69));
	temp.push_back(Rect(34, 0, 68, 35));
	temp.push_back(Rect(0, 39, 33, 76));
	temp.push_back(Rect(69, 0, 102, 35));

	this->listAnimation[RUNNING_ATTACK].Create(RUN_ATTACK_PATH, temp.size(), temp, 0.015f, RIGHT);
	temp.clear();

	//JUMPING
	temp.push_back(Rect(0, 84, 37, 108));
	temp.push_back(Rect(75, 0, 116, 15));
	temp.push_back(Rect(43, 24, 89, 43));
	temp.push_back(Rect(33, 0, 74, 23));
	temp.push_back(Rect(0, 31, 42, 58));
	temp.push_back(Rect(0, 59, 38, 83));
	temp.push_back(Rect(0, 0, 32, 30));

	this->listAnimation[JUMPING].Create(JUMP_PATH, temp.size(), temp, 0.01f, RIGHT);
	temp.clear();

	//JUMPING_ATTACK
	temp.push_back(Rect(72, 0, 109, 29));
	temp.push_back(Rect(0, 101, 41, 125));
	temp.push_back(Rect(43, 31, 89, 58));
	temp.push_back(Rect(0, 69, 41, 100));
	temp.push_back(Rect(0, 37, 42, 68));
	temp.push_back(Rect(33, 0, 71, 30));
	temp.push_back(Rect(0, 0, 32, 36));

	this->listAnimation[JUMPING_ATTACK].Create(JUMP_ATTACK_PATH, temp.size(), temp, 0.01f, RIGHT);
	temp.clear();


	//SWEEPING
	temp.push_back(Rect(27, 0, 58, 28));
	temp.push_back(Rect(0, 0, 26, 38));

	this->listAnimation[SWEEPING].Create(SWEEP_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();

	//SWEEPING_ATTACK
	temp.push_back(Rect(27, 0, 58, 37));
	temp.push_back(Rect(0, 0, 26, 48));

	this->listAnimation[SWEEPING_ATTACK].Create(SWEEP_ATTACK_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();

	//SWEEPING_WALL
	temp.push_back(Rect(0, 57, 42, 82));
	temp.push_back(Rect(0, 29, 43, 56));
	temp.push_back(Rect(0, 0, 42, 28));

	this->listAnimation[SWEEPING_WALL].Create(SWEEP_WALL_PATH, temp.size(), temp, 0.05f, LEFT);
	temp.clear();

	//SWEEPING_WALL_ATTACK
	temp.push_back(Rect(0, 66, 39, 97));
	temp.push_back(Rect(0, 0, 43, 32));
	temp.push_back(Rect(0, 33, 42, 65));

	this->listAnimation[SWEEPING_WALL_ATTACK].Create(SWEEP_WALL_ATTACK_PATH, temp.size(), temp, 0.05f, LEFT);
	temp.clear();

	//JUMPING_FROM_WALL
	temp.push_back(Rect(0, 0, 39, 30));
	temp.push_back(Rect(0, 62, 44, 89));
	temp.push_back(Rect(33, 31, 74, 54));
	temp.push_back(Rect(0, 90, 42, 117));
	temp.push_back(Rect(40, 0, 78, 24));
	temp.push_back(Rect(0, 31, 32, 61));

	this->listAnimation[JUMPING_FROM_WALL].Create(JUMP_FROM_WALL_PATH, temp.size(), temp, 0.01f, RIGHT);
	temp.clear();

	//JUMPING_FROM_WALL_ATTACK
	temp.push_back(Rect(75, 0, 113, 31));
	temp.push_back(Rect(0, 37, 39, 69));
	temp.push_back(Rect(33, 0, 74, 31));
	temp.push_back(Rect(0, 70, 42, 101));
	temp.push_back(Rect(40, 32, 78, 62));
	temp.push_back(Rect(0, 0, 32, 36));

	this->listAnimation[JUMPING_FROM_WALL_ATTACK].Create(JUMP_FROM_WALL_ATTACK_PATH, temp.size(), temp, 0.01f, RIGHT);
	temp.clear();

	//FALLING
	temp.push_back(Rect(0, 31, 42, 58));
	temp.push_back(Rect(0, 59, 38, 83));
	temp.push_back(Rect(0, 0, 32, 30));

	this->listAnimation[FALLING].Create(JUMP_PATH, temp.size(), temp, 0.01f, RIGHT);
	temp.clear();

	//FALLING_ATTACK
	temp.push_back(Rect(0, 37, 42, 68));
	temp.push_back(Rect(33, 0, 71, 30));
	temp.push_back(Rect(0, 0, 32, 36));

	this->listAnimation[FALLING_ATTACK].Create(JUMP_ATTACK_PATH, temp.size(), temp, 0.05f, RIGHT);
	temp.clear();

	//HURT
	temp.push_back(Rect(0, 0, 36, 26));
	temp.push_back(Rect(0, 27, 36, 53));

	this->listAnimation[HURT].Create(HURT_PATH, temp.size(), temp, 0.01f, RIGHT);
	temp.clear();
}

Animation* MegaManCharacters::GetListAnimation() {
	return this->listAnimation;
}

MegaManCharacters::~MegaManCharacters() {
}

MegaManData* MegaManCharacters::GetMegaManData() {
	return this->megaManData;
}

void MegaManCharacters::CreateBullet(int level) {
	int distancey1, distancey2, distancey3, distancex;
	switch (currentState)
	{
	case STANDING_ATTACK:
		distancey1 = 43;
		distancey2 = 35;
		distancey3 = 25;
		distancex = 10;
		break;
	case SWEEPING_ATTACK:
		distancey1 = 25;
		distancey2 = 15;
		distancey3 = 5;
		distancex = 35;
		break;
	default:
		distancey1 = 50;
		distancey2 = 40;
		distancey3 = 30;
		distancex = 10;
		break;
	}

	PlayerBullets *bullet;
	if (level == 1) {
		bullet = new BulletLv1(VT3(this->position.x + direct * distancex, this->position.y + distancey1, 0), 1500 * direct, direct);
		listBullet.push_back(bullet);
	}
	else if (level == 2) {
		bullet = new BulletLv2(VT3(this->position.x + direct * distancex, this->position.y + distancey2, 0), 1500 * direct, direct);
		listBullet.push_back(bullet);
	}
	else if (level == 3) {
		bullet = new BulletLv3(VT3(this->position.x + direct * distancex, this->position.y + distancey3, 0), 1500 * direct, direct);
		listBullet.push_back(bullet);
	}
}

void MegaManCharacters::AddSmokeEffect(VT3 smokePosition) {
	SmokeEffect *smoke = new SmokeEffect(smokePosition);
	this->listSmokeEff.push_back(smoke);
}

void MegaManCharacters::AddPosition(VT3 distance) {
	this->position.x += distance.x;
	this->position.y += distance.y;
}

void MegaManCharacters::SubLife(int sub) {
	if (!this->isUndying) {
		this->Life -= sub;
		if (this->Life <= 0) {
			this->Life = 0;
		}
		this->healthDraw->SetHealth(this->Life);
		this->isUndying = true;
	}
	if (this->Life == 0) {
		this->isDestroying = true;
		this->destroyedEffect = new DestroyedEffect(VT3(position.x, position.y + 40, 0));
	}
	else {
		this->SetState(new HurtState(this->megaManData));
	}
}

void MegaManCharacters::AddLife(int sub) {
	if (currentState != HURT) {
		this->Life += sub;
		if (this->Life >= 16) {
			this->Life = 16;
		}
		this->healthDraw->SetHealth(this->Life);
	}
}

