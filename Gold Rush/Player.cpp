#include "Player.h"

Player::Player(class Game* game) 
{
	mGame = game;
	mPos = Vector2(0.f, 0.f);
	mScale = 3.f;
	mFacing = true;
	mRecomputeWorldTransform = true;
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