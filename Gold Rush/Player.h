#pragma once

#include "stdafx.h"

enum Action
{
	EIdle,
	EWalk,
	EMine
};

enum State
{
	EActive,
	EPaused, 
	EDead
};

class Player
{
public: 
	// Constructor and destructor
	Player(class Game* game);
	~Player();

	// Update the player state
	void Update(float deltaTime);

	// Compute the world transform
	void ComputeWorldTransform();
	Matrix4 GetWorldTransform() { return mWorldTransform; }

private:
	// Member variables
	class Game* mGame;
	enum State mState;
	enum Action mAction;
	Vector2 mPos;
	float mScale;
	bool mFacing; // true = right, false = left
	Matrix4 mWorldTransform;
	bool mRecomputeWorldTransform;
};