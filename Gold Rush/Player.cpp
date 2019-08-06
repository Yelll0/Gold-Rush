#include "Player.h"

Player::Player(class Game* game, class Controller* controller) 
	: mGame(game),
	mController(controller),
	mPos(Vector2(105.f, 530.f)),
	mScale(3.f),
	mFacing(true),
	mRecomputeWorldTransform(true)
{
	mControls.emplace('R', SDL_SCANCODE_RIGHT);
	mControls.emplace('L', SDL_SCANCODE_LEFT);
	mControls.emplace('D', SDL_SCANCODE_DOWN);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	// Move according to keys pressed
	if (mController->GetKeyValue(mControls['R']))
	{
		SetFacing(true);
		mPos.x += 3.5f * deltaTime;
		mRecomputeWorldTransform = true;
	} 
	else if (mController->GetKeyValue(mControls['L']))
	{
		SetFacing(false);
		mPos.x -= 3.5f * deltaTime;
		mRecomputeWorldTransform = true;
	}
	// Make sure player doens't exit world boundaries
	if (mPos.x > 199) { mPos.x = 199; } else if (mPos.x < 0) { mPos.x = 0; }
	// [TEMP] Log position
	std::cout << mPos.x << std::endl;
	// Calculate world transform
	mPixPos = mPos * 60.f;
	ComputeWorldTransform();
}

void Player::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;
		// Scale and translate
		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateTranslation(Vector3(mPixPos.x, mPixPos.y, 0.f));
	}
}