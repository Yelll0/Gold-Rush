#pragma once

#include "stdafx.h"

class Player
{
public: 
	// Constructor and destructor
	Player(class Game* game, class Controller* controller);
	~Player();

	void Update(float deltaTime);

	void ComputeWorldTransform();
	Matrix4 GetWorldTransform() const { return mWorldTransform; }

	// Getters and Setters
	Vector2 GetPos() const { return mPos; }
	Vector2 GetPixPos() const { return mPixPos; }
	bool GetRecomputeWorldTransform() const { return mRecomputeWorldTransform; }
	bool GetFacing() const { return mFacing; }
	class Inventory* GetInv() const { return mInventory; }
	void SetFacing(bool facing) { mFacing = facing; }
	int GetOxygen() const { return mOxygen; }
	void SetMineSpeed(float mineSpeed) { mMineSpeed = mineSpeed; }
	bool GetIsAtCheckpoint() const { return mAtCheckpoint; }
	bool GetIsWalking() const { return mIsWalking; }
	bool GetIsMining() const { return mIsMining; }
	bool GetIsMiningUp() const { return mIsMiningUp; }
	bool GetIsDead() const { return mIsDead; }

private:
	// Helper functions
	void Control(float deltaTime);
	void Gravity(float deltaTime);
	void UpdateOxygen(float deltaTime);
	// Member variables
	class Game* mGame;
	class Controller* mController;
	class Inventory* mInventory;
	Vector2 mPos;
	Vector2 mPixPos;
	Vector2 mVel;
	float mScale;
	bool mFacing; // true = right
	bool mRecomputeWorldTransform;
	Matrix4 mWorldTransform;
	std::map<char, SDL_Scancode> mControls;
	bool mAtCheckpoint;
	float mOxygen;
	int mGold = 0;
	float mTime = 0.f;
	float mMineSpeed; // How many blocks mined in 1 second
	bool mIsWalking;
	bool mIsMining;
	bool mIsMiningUp;
	bool mIsDead;
};