#pragma once

#include "stdafx.h"

class Button
{
public:
	// Constructor and destructor
	Button(class UIScreen* menu, int texC, const Vector2& pos, const Vector2& dim, std::function<void()> fun);
	~Button();

	bool ContainsPoint(const Vector2& pt);
	
	// Function to execute on click
	std::function<void()> mFunction;

	// Getters and setters
	int GetTexCode() const { return mTexCode; }
	Vector2 GetPos() const { return mPos; }
	Vector2 GetDimensions() const { return mDimensions; }
	void SetTexCode(int tex) { mTexCode = tex; }
	bool GetHL() const { return mHL; }
	void SetHL(bool hl) { mHL = hl; }

private:
	class UIScreen* mMenu;
	int mTexCode;
	Vector2 mPos;
	Vector2 mDimensions;
	bool mHL;
};

