#include "Animation.h"


Animation::Animation() {
}

Animation::~Animation() {
}

void Animation::Create(char* filePath, int nFrame, std::vector<Rect> rect, double timeFrame, Direct direct)
{
	this->sprite = new GameSprite(filePath, C_XRGB(0, 0, 0));
	this->nFrame = nFrame;
	this->direct = direct;
	this->index = 0;
	this->totalTime = 0;
	this->deltaTime = timeFrame;
	this->rectSprite = rect;
}

int Animation::NextFrame(double time)
{
	this->totalTime += time;
	if (this->totalTime >= this->deltaTime)
	{
		this->index = (this->index + 1) % this->nFrame;
		this->totalTime = 0;
	}
	return this->index;
}

void Animation::Draw(VT3 position, Direct direct, double time, VT2 scale, VT2 translation, COLOR transcolor)
{
	if (direct == this->direct) {
		this->sprite->Draw(position, translation, this->rectSprite.at(this->index).GetCenter(), this->rectSprite.at(this->index), scale, 0.0f, VT2(position.x, position.y), transcolor);
	}
	else {
		this->sprite->Draw(position, translation, this->rectSprite.at(this->index).GetCenter(), this->rectSprite.at(this->index), VT2(-scale.x, scale.y), 0.0f, VT2(position.x, position.y), transcolor);
	}
	this->index = NextFrame(time);
}

int Animation::GetIndex()
{
	return this->index;
}

void Animation::SetIndex(int inx)
{
	this->index = inx;
}

int Animation::GetTotalFrame()
{
	return this->nFrame;
}

