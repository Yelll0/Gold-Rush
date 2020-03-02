#include "stdafx.h"

HUD::HUD(Game* game, Controller* controller, Player* player) : UIScreen(game, controller), 
	mPlayer(player) 
{
	// Create buttons and icons
	mButtons.emplace(mButtons.end(), new Button(this, 9, Vector2(239.f, 239.f), Vector2(30.f, 30.f), [this]() { mGame->SetState(0); }));
	mButtons.emplace(mButtons.end(), new Button(this, 2, Vector2(168.f, -234.f), Vector2(30.f, 30.f), [this]() { mPlayer->GetInv()->UpgradePick(); }));
	mButtons.emplace(mButtons.end(), new Button(this, 8, Vector2(133.f, -234.f), Vector2(30.f, 30.f), [this]() { mPlayer->GetInv()->C4Action(); }));
	mButtons.emplace(mButtons.end(), new Button(this, 10, Vector2(92.f, -214.f), Vector2(0.f, 0.f), NULL));
	mButtons.emplace(mButtons.end(), new Button(this, 11, Vector2(54.f, -214.f), Vector2(0.f, 0.f), NULL));
	mButtons.emplace(mButtons.end(), new Button(this, 12, Vector2(14.f, -214.f), Vector2(0.f, 0.f), NULL));
	mButtons.emplace(mButtons.end(), new Button(this, 13, Vector2(-26.f, -214.f), Vector2(0.f, 0.f), NULL));
	mButtons.emplace(mButtons.end(), new Button(this, 14, Vector2(-66.f, -214.f), Vector2(0.f, 0.f), NULL));
	mButtons.emplace(mButtons.end(), new Button(this, 15, Vector2(-106.f, -214.f), Vector2(0.f, 0.f), NULL));
	mButtons.emplace(mButtons.end(), new Button(this, 20, Vector2(-146.f, -214.f), Vector2(0.f, 0.f), NULL));
	mButtons.emplace(mButtons.end(), new Button(this, 21, Vector2(-186.f, -234.f), Vector2(0.f, 0.f), NULL));
}

HUD::~HUD()
{
}

void HUD::Update(float deltaTime)
{
	if (mPlayer->GetIsAtCheckpoint())
	{
		mButtons[2]->SetTexCode(7);
	}
	else
	{
		mButtons[2]->SetTexCode(8);
	}
}