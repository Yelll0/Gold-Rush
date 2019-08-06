#include "Player.h"

Player::Player(class Game* game, class Controller* controller) 
	: mGame(game),
	mController(controller),
	mPos(Vector2(105.f, 540.f)),
	mVel(Vector2(0.f, 0.f)),
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
	// TODO: More reliable mining and collision detection
	if (mController->GetKeyValue(mControls['R']))
	{
		SetFacing(true);
		mPos.x += 3.5f * deltaTime;
		if (mGame->GetWorld()->GetBlock(floor(mPos.x + 1), mPos.y) != 0)
		{
			mPos.x = round(mPos.x);
		}
		if (mGame->GetWorld()->GetBlock(mPos.x + 1, mPos.y) != 0)
		{
			if (mMineTime > 0.5) {
				mGame->GetWorld()->SetBlock(mPos.x + 1, mPos.y, 0);
				mMineTime = 0.f;
			}
			else {
				mMineTime += deltaTime;
			}
		}
		mRecomputeWorldTransform = true;
	} 
	else if (mController->GetKeyValue(mControls['L']))
	{
		SetFacing(false);
		mPos.x -= 3.5f * deltaTime;
		if (mGame->GetWorld()->GetBlock(ceil(mPos.x - 1), mPos.y) != 0)
		{
			mPos.x = round(mPos.x);
		}
		if (mGame->GetWorld()->GetBlock(mPos.x - 1, mPos.y) != 0)
		{
			if (mMineTime > 0.5) {
				mGame->GetWorld()->SetBlock(mPos.x - 1, mPos.y, 0);
				mMineTime = 0.f;
			}
			else {
				mMineTime += deltaTime;
			}
		}
		mRecomputeWorldTransform = true;
	}
	if (mController->GetKeyValue(mControls['D']))
	{
		if (mGame->GetWorld()->GetBlock(mPos.x, mPos.y - 1) != 0)
		{
			if (mMineTime > 0.5) {
				mGame->GetWorld()->SetBlock(mPos.x, mPos.y - 1, 0);
				mMineTime = 0.f;
			}
			else {
				mMineTime += deltaTime;
			}
		}
	}

	// Gravity
	if (mGame->GetWorld()->GetBlock(mPos.x, ceil(mPos.y - 1)) == 0) {
		if (mVel.y < 10.f) {
			mVel.y -= 9.8f * deltaTime;
		}
		mPos += mVel * deltaTime;
		mRecomputeWorldTransform = true;
	} 
	if (mGame->GetWorld()->GetBlock(mPos.x, ceil(mPos.y - 1)) != 0) 
	{ 
		mPos.y = round(mPos.y); 
		mRecomputeWorldTransform = true; 
	}

	// Make sure player doens't exit world boundaries
	if (mPos.x > 204) { mPos.x = 204; } else if (mPos.x < 5) { mPos.x = 5; }
	// [TEMP] Log position
	std::cout << mPos.x << std::endl << mPos.y << std::endl;
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