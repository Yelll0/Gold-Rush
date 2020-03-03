#include "stdafx.h"

Button::Button(class UIScreen* menu, int texC, const Vector2& pos, const Vector2& dim, std::function<void()> fun) : mMenu(menu), 
	mTexCode(texC),
	mPos(pos),
	mDimensions(dim),
	mFunction(fun),
	mHL(false)
{
}

Button::~Button()
{
}

bool Button::ContainsPoint(const Vector2& pt)
{
	bool no = pt.x < (mPos.x - mDimensions.x / 2.f) || 
		pt.x > (mPos.x + mDimensions.x / 2.f) ||
		pt.y*-1 < (mPos.y - mDimensions.y / 2.f) ||
		pt.y*-1 > (mPos.y + mDimensions.y / 2.f);
	return !no;
}