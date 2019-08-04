#include "Player.h"

Player::Player(class Game* game) 
	: mGame(game),
	mPos(Vector2(6300.f, 31800.f)),
	mScale(3.f),
	mFacing(false),
	mRecomputeWorldTransform(true)
{
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	ComputeWorldTransform();
}

void Player::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;
		// Scale and translate
		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateTranslation(Vector3(mPos.x, mPos.y, 0.f));
	}
}