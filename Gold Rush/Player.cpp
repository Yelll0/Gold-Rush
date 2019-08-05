#include "Player.h"

Player::Player(class Game* game, class Controller* controller) 
	: mGame(game),
	mController(controller),
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
	// Move according to keys pressed
	if (mController->GetKeyValue(SDL_SCANCODE_RIGHT))
	{
		SetFacing(true);
		mPos.x += 90.f * deltaTime;
	} 
	else if (mController->GetKeyValue(SDL_SCANCODE_LEFT))
	{
		SetFacing(false);
		mPos.x -= 90.f * deltaTime;
	}
	// Make sure player doens't exit world boundaries
	if (mPos.x > 12000) { mPos.x = 12000; } else if (mPos.x < 600) { mPos.x = 600; }
	// [TEMP] Log position
	std::cout << mPos.x << std::endl;
	// Calculate world transform
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