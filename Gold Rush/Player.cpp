#include "Player.h"

Player::Player(class Game* game, class Controller* controller) 
	: mGame(game),
	mController(controller),
	mPos(Vector2(105.f, 537.f)),
	mVel(Vector2(0.f, 0.f)),
	mScale(3.f),
	mFacing(true),
	mRecomputeWorldTransform(true),
	mOxygen(10.f),
	mAtCheckpoint(true)
{
	mControls.emplace('R', SDL_SCANCODE_RIGHT);
	mControls.emplace('L', SDL_SCANCODE_LEFT);
	mControls.emplace('D', SDL_SCANCODE_DOWN);
	mControls.emplace('U', SDL_SCANCODE_UP);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	// Move according to keys pressed
	if (mController->GetKeyValue(mControls['D']))
	{
		// Mine block if it's not air
		if (mGame->GetWorld()->GetBlock(round(mPos.x), round(mPos.y - 0.6)) != 0.f)
		{
			if (mGame->GetWorld()->GetBlockDamage(round(mPos.x), round(mPos.y - 0.6)) >= 1.f) {
				mGame->GetWorld()->SetBlock(round(mPos.x), round(mPos.y - 0.6), 0);
			}
			else {
				mGame->GetWorld()->DamageBlock(round(mPos.x), round(mPos.y - 0.6), 5 * deltaTime);
			}
		}
	}
	else if (mController->GetKeyValue(mControls['U']))
	{
		// Mine block if it's not air
		if (mGame->GetWorld()->GetBlock(round(mPos.x), round(mPos.y + 0.6)) != 0.f)
		{
			if (mGame->GetWorld()->GetBlockDamage(round(mPos.x), round(mPos.y + 0.6)) >= 1.f) {
				mGame->GetWorld()->SetBlock(round(mPos.x), round(mPos.y + 0.6), 0);
			}
			else {
				mGame->GetWorld()->DamageBlock(round(mPos.x), round(mPos.y + 0.6), 5 * deltaTime);
			}
		}
	}
	else if (mController->GetKeyValue(mControls['R']))
	{
		// Face right
		SetFacing(true);
		// Move player according to delta time
		mPos.x += 4.5f * deltaTime;
		// Query for block in front of player
		int rightBlock = mGame->GetWorld()->GetBlock(round(mPos.x + 0.6), mPos.y);
		int rightBlockDamage = mGame->GetWorld()->GetBlockDamage(round(mPos.x + 0.6), mPos.y);
		// Stop moving if it's not air
		if (rightBlock != 0.f)
		{
			mPos.x = round(mPos.x);
		}
		// Mine block if it's not air
		if (rightBlock != 0)
		{
			if (rightBlockDamage >= 1.f) {
				mGame->GetWorld()->SetBlock(mPos.x + 1, mPos.y, 0);
			}
			else {
				mGame->GetWorld()->DamageBlock(mPos.x + 1, mPos.y, 5 * deltaTime);
			}
		}

		mRecomputeWorldTransform = true;
	} 
	else if (mController->GetKeyValue(mControls['L']))
	{
		// Face left
		SetFacing(false);
		// Move player according to delta time
		mPos.x -= 4.5f * deltaTime;
		// Query for block in front of player
		int leftBlock = mGame->GetWorld()->GetBlock(round(mPos.x - 0.6), mPos.y);
		int leftBlockDamage = mGame->GetWorld()->GetBlockDamage(round(mPos.x - 0.6), mPos.y);
		// Stop moving if it's not air
		if (leftBlock != 0.f)
		{
			mPos.x = round(mPos.x);
		}
		// Mine block if it's not air
		if (leftBlock != 0)
		{
			if (leftBlockDamage >= 1.f) {
				mGame->GetWorld()->SetBlock(mPos.x - 1, mPos.y, 0);
			}
			else {
				mGame->GetWorld()->DamageBlock(mPos.x - 1, mPos.y, 5 * deltaTime);
			}
		}

		mRecomputeWorldTransform = true;
	} 

	// Query for blocks underneath player
	int underBlockR = mGame->GetWorld()->GetBlock(ceil(mPos.x), ceil(mPos.y - 1));
	int underBlockL = mGame->GetWorld()->GetBlock(floor(mPos.x), ceil(mPos.y - 1));

	// Gravity
	if (underBlockR == 0 && underBlockL == 0)
	{
		// Accelerate by 2*g until 10m/s (terminal velocity)
		if (mVel.y < 10.f) {
			mVel.y -= 19.6f * deltaTime;
		}
		mPos += mVel * deltaTime;

		mRecomputeWorldTransform = true;
	} else { mVel *= 0; }
	// Re query for blocks underneath player
	underBlockR = mGame->GetWorld()->GetBlock(ceil(mPos.x), ceil(mPos.y - 1));
	underBlockL = mGame->GetWorld()->GetBlock(floor(mPos.x), ceil(mPos.y - 1));
	// Stop if it's not air
	if (underBlockR != 0 && underBlockL !=0) 
	{ 
		mPos.y = round(mPos.y); 

		mRecomputeWorldTransform = true; 
	}

	// Make sure player doens't exit world boundaries
	if (mPos.x > 204) { mPos.x = 204; } else if (mPos.x < 5) { mPos.x = 5; }
	// Calculate world transform
	mPixPos = mPos * 60.f;
	ComputeWorldTransform();

	if (mGame->GetWorld()->GetIsCheckpoint(round(mPos.y))) { mAtCheckpoint = true; } else { mAtCheckpoint = false; }
	if (mAtCheckpoint) { mOxygen = 10.f; } else { mOxygen -= deltaTime; }
	std::cout << mOxygen << std::endl;
	if (mOxygen <= 0.f) { mGame->SetState(-1); }

	if (mPos.y < 205.f) { mGame->SetState(-1); }
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