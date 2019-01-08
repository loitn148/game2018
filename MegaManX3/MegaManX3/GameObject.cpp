#include "GameObject.h"
#include "Camera.h"


GameObject::GameObject() {
	this->vx = 0;
	this->vy = 0;
	this->isDead = false;
}

GameObject::~GameObject() {

}

Object GameObject::GetId() {
	return this->id;
}

double GameObject::GetV0() {
	return this->v0;
}

double GameObject::GetVx() {
	return this->vx;
}

double GameObject::GetVy() {
	return this->vy;
}

double GameObject::GetAx() {
	return this->ax;
}

double GameObject::GetAy() {
	return this->ay;
}

Rect GameObject::GetRect() {
	if (this->isDead) {
		return Rect(0, 0, 0, 0);
	}
	return this->rectBound;
}

Direct GameObject::GetDirect() {
	return this->direct;
}

int GameObject::GetWidth() {
	return this->width;
}

int GameObject::GetHeight() {
	return this->height;
}

bool GameObject::GetIsDead() {
	return this->isDead;
}

bool GameObject::checkCamera()
{
	return Collision::IsColliding(rectBound, Camera::GetInstance()->GetRect());
}

VT3 GameObject::GetPosition() {
	return this->position;
}

VT3 GameObject::GetCenterPosition() {
	VT3 center = VT3(this->position.x + this->width / 2, this->position.y + this->height / 2, 0);
	return center;
}

VT3 GameObject::GetPositionInViewport() {
	return Viewport::GetInstance()->GetPositionInViewport(this->position);
}

void GameObject::SetId(Object id) {
	this->id = id;
}

void GameObject::SetPosition(VT3 position) {
	this->position = position;
}

void GameObject::SetV0(double v0) {
	this->v0 = v0;
}

void GameObject::SetVx(double vx) {
	this->vx = vx;
}

void GameObject::SetVy(double vy) {
	this->vy = vy;
}

void GameObject::SetAx(double ax) {
	this->ax = ax;
}

void GameObject::SetAy(double ay) {
	this->ay = ay;
}

void GameObject::SetHeight(int height) {
	this->height = height;
}

void GameObject::SetWidth(int width) {
	this->width = width;
}

void GameObject::SetRect(Rect rect) {
	this->rectBound = rect;
}

void GameObject::SetDirect(Direct direct) {
	this->direct = direct;
}

void GameObject::SetIsDead(bool isDead) {
	this->isDead = isDead;
}

void GameObject::Update(double time) {
	this->position.x += this->vx*time;
	this->position.y += this->vy*time;
}

void GameObject::Draw(double time) {}

void GameObject::UpdateRect() {
	this->rectBound.top = this->position.y + this->height;
	this->rectBound.left = this->position.x - this->width / 2;
	this->rectBound.bottom = this->position.y;
	this->rectBound.right = this->rectBound.left + this->width;
}

void GameObject::Create(VT3 position, int width, int height, Rect rect) {
	/*this->position = position;
	this->width = width;
	this->height = height;
	this->vx = 0;
	this->vy = 0;
	this->direct = RIGHT;
	this->rectBound = rect;*/
}