#include "stdafx.h"

Button::Button(class PauseMenu* menu, class Texture* tex, const Vector2& pos, const Vector2& dim, std::function<void()> fun) : mMenu(menu), 
	mTex(tex),
	mPos(pos),
	mDimensions(dim),
	mFunction(fun)
{
}

Button::~Button()
{
}

bool Button::ContainsPoint(const Vector2& pt)
{
	bool no = pt.x < (mPos.x - mDimensions.x / 2.f) || 
		pt.x > (mPos.x + mDimensions.x / 2.f) ||
		pt.y < (mPos.y - mDimensions.y / 2.f) ||
		pt.y > (mPos.y + mDimensions.y / 2.f);
	return !no;
}