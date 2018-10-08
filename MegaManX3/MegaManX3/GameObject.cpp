#include "GameObject.h"


GameObject::GameObject() {
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
	return this->rectBound;
}

int GameObject::GetWidth() {
	return this->width;
}

int GameObject::GetHeight() {
	return this->height;
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

void GameObject::SetRect(Rect rect) {
	this->rectBound = rect;
}

void GameObject::UpdateRect() {
	this->rectBound.top = this->position.y + this->height;
	this->rectBound.left = this->position.x - this->width / 2;
	this->rectBound.bottom = this->position.y;
	this->rectBound.right = this->rectBound.left + this->width;
}

void GameObject::Create(VT3 position, int width, int height, Rect rect) {
	this->position = position;
	this->width = width;
	this->height = height;
	this->vx = 0;
	this->vy = 0;
	this->direct = RIGHT;
	this->rectBound = rect;
}