#include "Player.h"

Player::Player(class Game* game)
{
	mGame = game;
	mPos = Vector2(500.f, 500.f);
	mScale = 1;
	mState = EActive;
}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{
	if (mState == EActive)
	{
		ComputeWorldTransform();
	}
}

void Player::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;
		// Transform
		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateTranslation(Vector3(mPos.x, mPos.y, 0.f));
	}
}