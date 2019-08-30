#pragma once

#include "stdafx.h"

class Button
{
public:
	Button(Vector2 pos, int h, int w, class MenuScreen* menu);
	~Button();

private:
	Vector2 mPos;
	int mHeight;
	int mWidth;
	class MenuScreen* mMenu;
};