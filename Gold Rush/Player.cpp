#include "stdafx.h"

Player::Player(class Game* game, class Controller* controller) 
	: mGame(game),
	mController(controller),
	mInventory(new Inventory(this, controller, mGame)),
	mPos(Vector2(107.f, 616.f)),
	mVel(Vector2(0.f, 0.f)),
	mScale(3.f),
	mFacing(true),
	mRecomputeWorldTransform(true),
	mOxygen(60.f),
	mAtCheckpoint(true),
	mIsDead(false)
{
	// Bind default controls
	mControls.emplace('R', SDL_SCANCODE_RIGHT);
	mControls.emplace('L', SDL_SCANCODE_LEFT);
	mControls.emplace('D', SDL_SCANCODE_DOWN);
	mControls.emplace('U', SDL_SCANCODE_UP);
	mControls.emplace('P', SDL_SCANCODE_RSHIFT);
	mControls.emplace('B', SDL_SCANCODE_RCTRL);
}

Player::~Player()
{
	delete mInventory;
}

void Player::Update(float deltaTime)
{
	if (mGame->GetState() == 1)
	{
		// Update according to controls
		Control(deltaTime);
		// Apply gravity
		Gravity(deltaTime);

		// Calculate world transform
		mPixPos = mPos * 60.f;
		if (mRecomputeWorldTransform)
		{
			ComputeWorldTransform();
		}

		// Update oxygen stats
		UpdateOxygen(deltaTime);
		mTime += deltaTime;

		// Calculate score
		mInventory->CalcScore();
	}
}

void Player::Control(float deltaTime)
{
	// Move according to keys pressed
	if (mController->GetKeyValue(mControls['D']))
	{
		float faceN;
		if (mFacing) { faceN = 0.4; } else { faceN = -0.4; }
		// Query for block below player
		int downBlock = mGame->GetWorld()->GetBlock(round(mPos.x + faceN), round(mPos.y - 0.6));
		float downBlockDamage = mGame->GetWorld()->GetBlockDamage(round(mPos.x + faceN), round(mPos.y - 0.6));

		// Mine block if it's not air
		if (downBlock > 0.f && downBlock < 10)
		{
			if (downBlockDamage >= 1.f) {
				// Add item to inventory
				mInventory->AddItem(mGame->GetWorld()->GetItemForBlock(downBlock), 1);
				// Break block
				mGame->GetWorld()->SetBlock(round(mPos.x + faceN), round(mPos.y - 0.6), 0);
			}
			else {
				mGame->GetWorld()->DamageBlock(round(mPos.x + faceN), round(mPos.y - 0.6), mMineSpeed * deltaTime);
			}
		}
		mIsWalking = false;
		mIsMiningUp = false;
		mIsMining = true;
	}
	else if (mController->GetKeyValue(mControls['U']))
	{
		if (!mAtCheckpoint)
		{
			// Query for block above player
			int upBlock = mGame->GetWorld()->GetBlock(round(mPos.x), round(mPos.y + 0.6));
			float upBlockDamage = mGame->GetWorld()->GetBlockDamage(round(mPos.x), round(mPos.y + 0.6));
			// Mine block if it's not air
			if (upBlock > 0 && upBlock < 10)
			{
				if (upBlockDamage >= 1.f) {
					// Add item to inventory
					mInventory->AddItem(mGame->GetWorld()->GetItemForBlock(upBlock), 1);
					mGame->GetWorld()->SetBlock(round(mPos.x), round(mPos.y + 0.6), 0);
				}
				else {
					mGame->GetWorld()->DamageBlock(round(mPos.x), round(mPos.y + 0.6), mMineSpeed * deltaTime);
				}
			}
		}
		mIsWalking = false;
		mIsMining = false;
		mIsMiningUp = true;
	}
	else if (mController->GetKeyValue(mControls['R']))
	{
		// Face right
		SetFacing(true);
		// Move player according to delta time
		mPos.x += 4.5f * deltaTime;
		// Query for block in front of player
		int rightBlock = mGame->GetWorld()->GetBlock(round(mPos.x + 0.6), mPos.y);
		float rightBlockDamage = mGame->GetWorld()->GetBlockDamage(round(mPos.x + 0.6), mPos.y);

		// Stop moving and mine block if it's not air
		if (rightBlock > 0 && rightBlock < 10)
		{
			mPos.x = round(mPos.x);
			if (rightBlockDamage >= 1.f) {
				// Add item to inventory
				mInventory->AddItem(mGame->GetWorld()->GetItemForBlock(rightBlock), 1);
				mGame->GetWorld()->SetBlock(mPos.x + 1, mPos.y, 0);
			}
			else {
				mGame->GetWorld()->DamageBlock(mPos.x + 1, mPos.y, mMineSpeed * deltaTime);
			}
			mIsWalking = false;
			mIsMiningUp = false;
			mIsMining = true;
		}
		else 
		{ 
			mIsMining = false;
			mIsMiningUp = false;
			mIsWalking = true;
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
		float leftBlockDamage = mGame->GetWorld()->GetBlockDamage(round(mPos.x - 0.6), mPos.y);

		// Stop moving and mine block if it's not air
		if (leftBlock > 0 && leftBlock < 10)
		{
			mPos.x = round(mPos.x);
			if (leftBlockDamage >= 1.f) {
				// Add item to inventory
				mInventory->AddItem(mGame->GetWorld()->GetItemForBlock(leftBlock), 1);
				mGame->GetWorld()->SetBlock(mPos.x - 1, mPos.y, 0);
			}
			else {
				mGame->GetWorld()->DamageBlock(mPos.x - 1, mPos.y, mMineSpeed * deltaTime);
			}
			mIsWalking = false;
			mIsMiningUp = false;
			mIsMining = true;
		}
		else 
		{
			mIsMiningUp = false;
			mIsMining = false;
			mIsWalking = true; 
		}
		mRecomputeWorldTransform = true;
	}
	else 
	{
		mIsMiningUp = false;
		mIsWalking = false;
		mIsMining = false;
	}
	if (mController->GetKeyState(mControls['P']) == EPressed) { mInventory->UpgradePick(); }
	if (mController->GetKeyState(mControls['B']) == EPressed) { mInventory->C4Action(); }

	// Make sure player doens't exit world boundaries
	if (mPos.x > 202) { mPos.x = 202; }
	else if (mPos.x < 7) { mPos.x = 7; }
}

void Player::Gravity(float deltaTime)
{
	// Query for blocks underneath player
	int underBlockR = mGame->GetWorld()->GetBlock(ceil(mPos.x - 0.1), ceil(mPos.y - 1));
	int underBlockL = mGame->GetWorld()->GetBlock(floor(mPos.x + 0.1), ceil(mPos.y - 1));

	if ((underBlockR == 0 || underBlockR == 10) && (underBlockL == 0 || underBlockL == 10))
	{
		// Accelerate by 2*g until 10m/s (terminal velocity)
		if (mVel.y < 10.f) {
			mVel.y -= 19.6f * deltaTime;
		}
		mPos += mVel * deltaTime;

		mRecomputeWorldTransform = true;
	}
	else { mVel *= 0; }
	// Re query for blocks underneath player
	underBlockR = mGame->GetWorld()->GetBlock(ceil(mPos.x - 0.1), ceil(mPos.y - 1));
	underBlockL = mGame->GetWorld()->GetBlock(floor(mPos.x + 0.1), ceil(mPos.y - 1));
	// Stop if it's not air
	if (underBlockR != 0 && underBlockL != 0)
	{
		mPos.y = round(mPos.y);

		mRecomputeWorldTransform = true;
	}
}

void Player::UpdateOxygen(float deltaTime)
{
	// Restore/deplete depending on whether the player is at a checkpoint
	if (mPos.y < 616.f)
	{
		if (mGame->GetWorld()->GetIsCheckpoint(round(mPos.y))) { mAtCheckpoint = true; }
		else { mAtCheckpoint = false; } 
		if (mAtCheckpoint) { mOxygen = 5.f; }
		else { mOxygen -= deltaTime; }
		// Die
		if (mOxygen <= 0.f) { 
			mGame->SetState(2);
			mIsDead = true;
		}
		// Win
		if (mPos.y <= 6.f) { mGame->SetState(2); }

		if (!mAtCheckpoint) { mTime += deltaTime; }
	}
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