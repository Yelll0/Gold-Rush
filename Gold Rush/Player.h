#pragma once

#include "stdafx.h"

class Player
{
public: 
	// Constructor and destructor
	Player(class Game* game);
	~Player();

	void Update(float deltaTime);

	void ComputeWorldTransform();
	Matrix4 GetWorldTransform() const { return mWorldTransform; }

	// Getters and Setters
	Vector2 GetPos() const { return mPos; }

private:
	// Member variables
	class Game* mGame;
	Vector2 mPos;
	float mScale;
	bool mFacing; // True = right
	bool mRecomputeWorldTransform;
	Matrix4 mWorldTransform;
};