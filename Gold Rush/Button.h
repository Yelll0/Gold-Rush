#pragma once

#include "stdafx.h"

class Button
{
public:
	// Constructor and destructor
	Button(class PauseMenu* menu, class Texture* tex, const Vector2& pos, const Vector2& dim, std::function<void()> fun);
	~Button();

	bool ContainsPoint(const Vector2& pt);
	
	// Function to execute on click
	std::function<void()> mFunction;

	// Getters and setters
	class Texture* GetTex() const { return mTex; }
	Vector2 GetPos() const { return mPos; }
	Vector2 GetDimensions() const { return mDimensions; }

private:
	class PauseMenu* mMenu;
	class Texture* mTex;
	Vector2 mPos;
	Vector2 mDimensions;
};

