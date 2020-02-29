#include "stdafx.h"

HUD::HUD(Game* game, Controller* controller, Player* player) : UIScreen(game, controller), mPlayer(player)
{
	mButtons.emplace(mButtons.end(), new Button(this, 9, Vector2(219.f, 234.f), Vector2(30.f, 30.f), [this]() { mGame->SetState(0); }));
	mButtons.emplace(mButtons.end(), new Button(this, 2, Vector2(219.f, -234.f), Vector2(30.f, 30.f), [this]() { mPlayer->GetInv()->UpgradePick(); }));
	mButtons.emplace(mButtons.end(), new Button(this, 7, Vector2(184.f, -234.f), Vector2(30.f, 30.f), [this]() { mPlayer->GetInv()->C4Action(); }));
	mButtons.emplace(mButtons.end(), new Button(this, 11, Vector2(124.f, -199.f), Vector2(0.f, 0.f), NULL));
	mButtons.emplace(mButtons.end(), new Button(this, 12, Vector2(64.f, -199.f), Vector2(0.f, 0.f), NULL));
	mButtons.emplace(mButtons.end(), new Button(this, 13, Vector2(4.f, -199.f), Vector2(0.f, 0.f), NULL));
	mButtons.emplace(mButtons.end(), new Button(this, 14, Vector2(-56.f, -199.f), Vector2(0.f, 0.f), NULL));
	mButtons.emplace(mButtons.end(), new Button(this, 15, Vector2(-116.f, -199.f), Vector2(0.f, 0.f), NULL));
	mButtons.emplace(mButtons.end(), new Button(this, 10, Vector2(-176.f, -199.f), Vector2(0.f, 0.f), NULL));
}

HUD::~HUD()
{
}
