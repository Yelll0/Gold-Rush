#include "stdafx.h"

Renderer::Renderer(class Game* game, class Player* player)
	: mGame(game),
	mPlayer(player),
	mPlayerTex(nullptr),
	mShader(nullptr),
	mVertArray(nullptr)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Init()
{
	// Load shaders
	mShader = new Shader();
	if (!mShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}
	mShader->SetActive();

	// Load vertex array
	mVertArray = new VertexArray(mQuadVertsM, 4, mQuadBuffer, 6);
	mVertArrayM = new VertexArray(mQuadVerts, 4, mQuadBuffer, 6);
	mVertArrayS = new VertexArray(mSmallQuadVerts, 4, mQuadBuffer, 6);
	mVertArrayButton = new VertexArray(mButtonVerts, 4, mQuadBuffer, 6);
	mVertArrayPauseMenu = new VertexArray(mPauseMenuVerts, 4, mQuadBuffer, 6);
	mVertArrayHUD = new VertexArray(mHUDVerts, 4, mQuadBuffer, 6);
	mVertArrayOneNum = new VertexArray(mOneNumVerts, 4, mQuadBuffer, 6);
	mVertArrayTwoNum = new VertexArray(mTwoNumVerts, 4, mQuadBuffer, 6);

	// Player textures
	mPlayerTex = new Texture("Sprites/miner/miner.png", true);
	mPlayerWalkTex.emplace_back(new Texture("Sprites/miner/miner.png", true));
	mPlayerWalkTex.emplace_back(new Texture("Sprites/miner/miner-move1.png", true));
	mPlayerWalkTex.emplace_back(new Texture("Sprites/miner/miner-move2.png", true));
	mPlayerWalkTex.emplace_back(new Texture("Sprites/miner/miner-move3.png", true));
	mPlayerWalkTex.emplace_back(new Texture("Sprites/miner/miner-move4.png", true));
	mPlayerWalkTex.emplace_back(new Texture("Sprites/miner/miner-move5.png", true));
	mPlayerWalkTex.emplace_back(new Texture("Sprites/miner/miner-move6.png", true));
	mPlayerWalkTex.emplace_back(new Texture("Sprites/miner/miner-move7.png", true));
	mPlayerWalkTex.emplace_back(new Texture("Sprites/miner/miner-move8.png", true));
	mPlayerWalkTex.emplace_back(new Texture("Sprites/miner/miner-move9.png", true));
	mPlayerMineTex.emplace_back(new Texture("Sprites/miner/miner-mine-s1.png", true));
	mPlayerMineTex.emplace_back(new Texture("Sprites/miner/miner-mine-s2.png", true));
	mPlayerMineTex.emplace_back(new Texture("Sprites/miner/miner-mine-s3.png", true));
	mPlayerMineTex.emplace_back(new Texture("Sprites/miner/miner-mine-s4.png", true));
	mPlayerMineTex.emplace_back(new Texture("Sprites/miner/miner-mine-s5.png", true));
	mPlayerMineTex.emplace_back(new Texture("Sprites/miner/miner-mine-s6.png", true));

	mTex.emplace(0, new Texture("Sprites/air.png", true));
	mTex.emplace(1, new Texture("Sprites/grass.png", true));
	mTex.emplace(2, new Texture("Sprites/stone.png", true));
	mTex.emplace(3, new Texture("Sprites/coal.png", true));
	mTex.emplace(4, new Texture("Sprites/copper.png", true));
	mTex.emplace(5, new Texture("Sprites/iron.png", true));
	mTex.emplace(6, new Texture("Sprites/titanium.png", true));
	mTex.emplace(7, new Texture("Sprites/mithril.png", true));
	mTex.emplace(8, new Texture("Sprites/gold.png", true));
	/*
	0 = Air
	1 = Grass/dirt
	2 = Stone
	3 = Coal
	4 = Copper
	5 = Iron
	6 = Titanium
	7 = Mithril
	8 = Gold
	*/
	mUITex.emplace(0, new Texture("Sprites/oxygen.png", true));
	mUITex.emplace(1, new Texture("Sprites/oxygentxt.png", true));
	mUITex.emplace(2, new Texture("Sprites/upgrade-pick.png", true));
	mUITex.emplace(3, new Texture("Sprites/play.png", true));
	mUITex.emplace(4, new Texture("Sprites/sound.png", true));
	mUITex.emplace(5, new Texture("Sprites/mute.png", true));
	mUITex.emplace(6, new Texture("Sprites/home.png", true));
	mUITex.emplace(7, new Texture("Sprites/craft-bomb.png", true));
	mUITex.emplace(8, new Texture("Sprites/use-bomb.png", true));
	mUITex.emplace(9, new Texture("Sprites/pause.png", true));
	mUITex.emplace(10, new Texture("Sprites/gold-ingot.png", true));
	mUITex.emplace(11, new Texture("Sprites/coal-frag.png", true));
	mUITex.emplace(12, new Texture("Sprites/copper-frag.png", true));
	mUITex.emplace(13, new Texture("Sprites/iron-ingot.png", true));
	mUITex.emplace(14, new Texture("Sprites/titanium-ingot.png", true));
	mUITex.emplace(15, new Texture("Sprites/mithril-frag.png", true));
	mUITex.emplace(20, new Texture("Sprites/bomb.png", true));
	mUITex.emplace(21, new Texture("Sprites/default-pickaxe.png", true));
	mUITex.emplace(22, new Texture("Sprites/copper-pickaxe.png", true));
	mUITex.emplace(23, new Texture("Sprites/iron-pickaxe.png", true));
	mUITex.emplace(24, new Texture("Sprites/titanium-pickaxe.png", true));
	mUITex.emplace(25, new Texture("Sprites/mithril-pickaxe.png", true));
	/*
	0 - Oxygen bar
	1 - Oxygen text
	2 - Upgrade pickaxe button
	3 - Play button
	4 - Sound button
	5 - Mute button
	6 - Home button
	7 - Craft C4 button
	8 - Use C4 button
	9 - Pause button
	10 - Gold icon
	11 - Coal icon
	12 - Copper icon
	13 - Iron icon
	14 - Titanium icon
	15 - Mithril icon
	20 - Bomb icon
	21 - Default pick
	22 - Copper pick
	23 - Iron pick
	24 - Titanium pick
	25 - Mithril pick
	*/

	mPauseMenu = new Texture("Sprites/pause-menu.png", true);
	mHUDTex = new Texture("Sprites/HUD.png", true);

	mFont = new Font();
	mFont->Load("Sprites/8_bit_pusab/8-bit-pusab.ttf");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void Renderer::ComputeWorldTransform(float scale, Vector2 pixPos, Matrix4& worldTransform)
{
	worldTransform = Matrix4::CreateScale(scale);
	worldTransform *= Matrix4::CreateTranslation(Vector3(pixPos.x, pixPos.y, 0.f));
}

void Renderer::ComputeObjViewTransform()
{
	// Recenter around player
	Vector2 p = mPlayer->GetPixPos();
	mViewTransform = Matrix4::CreateTranslation(Vector3(-1.f * p.x, -1.f * p.y, 0.f)) * Matrix4::CreateSimpleViewProj(576.f, 576.f);
}

void Renderer::ComputeViewTransform()
{
	mViewTransform = Matrix4::CreateSimpleViewProj(576.f, 576.f);
}

void Renderer::DrawTexture(Shader* shader, Texture* texture, const Vector2& offset, float scale)
{
}

void Renderer::Draw(float deltaTime)
{
	// Activate shader program
	mShader->SetActive();
	// TODO: Expand world horizontally by 4 blocks
	// Draw world
	mVertArray->SetActive();
	Vector2 playerPos = mPlayer->GetPos();
	for (int y = playerPos.y - 6; y <= playerPos.y + 6; y++)
	{
		for (int x = playerPos.x - 6; x <= playerPos.x + 6; x++)
		{
			mTex[mGame->GetWorld()->GetBlock(x, y)]->SetActive();

			ComputeWorldTransform(3.f, Vector2(x * 60, y * 60), mTempWorldTransform);
			mShader->SetMatrixUniform("uViewTransform", mViewTransform);
			mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	}

	// Draw player
	// Flip the player according to its face direction
	if (mPlayer->GetFacing())
	{
		mVertArrayM->SetActive();
	}
	mCurrFrame += 830 * deltaTime;
	if (mPlayer->GetIsWalking())
	{
		while (mCurrFrame > mPlayerWalkTex.size())
		{
			mCurrFrame = 0;
		}
		mPlayerWalkTex[mCurrFrame]->SetActive();
	}
	else if (mPlayer->GetIsMining())
	{
		while (mCurrFrame > mPlayerMineTex.size())
		{
			mCurrFrame = 0;
		}
		mPlayerMineTex[mCurrFrame]->SetActive();
	}
	else
	{
		// Activate player texture
		mPlayerTex->SetActive();
	}
	// Apply matrices
	ComputeObjViewTransform();
	mShader->SetMatrixUniform("uViewTransform", mViewTransform);
	mShader->SetMatrixUniform("uWorldTransform", mPlayer->GetWorldTransform());
	// Draw quads
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	// Draw HUD
	mVertArrayHUD->SetActive();
	mHUDTex->SetActive();
	ComputeWorldTransform(3.f, Vector2(-8.f, -234.f), mTempWorldTransform);
	ComputeViewTransform();
	mShader->SetMatrixUniform("uViewTransform", mViewTransform);
	mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	// Draw oxygen bar
	mVertArrayS->SetActive();
	for (int i = floor(mPlayer->GetOxygen() / 5.f); i >= 0; i--)
	{
		mUITex[0]->SetActive();

		ComputeWorldTransform(3.f, Vector2(239.f, -234.f + i * 30), mTempWorldTransform);
		ComputeViewTransform();
		mShader->SetMatrixUniform("uViewTransform", mViewTransform);
		mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
	// Draw oxygen icon
	mUITex[1]->SetActive();
	ComputeWorldTransform(3.f, Vector2(239.f, -264.f), mTempWorldTransform);
	ComputeViewTransform();
	mShader->SetMatrixUniform("uViewTransform", mViewTransform);
	mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	// Draw HUD buttons
	for (int i = 0; i <= 10; i++)
	{
		class Button* b = mGame->GetHUD()->GetButton(i);
		mUITex[b->GetTexCode()]->SetActive();
		ComputeWorldTransform(3.f, b->GetPos(), mTempWorldTransform);
		ComputeViewTransform();
		mShader->SetMatrixUniform("uViewTransform", mViewTransform);
		mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
	// Draw numbers
	for (int i = 0; i <= 6; i++)
	{
		Vector2 pos = Vector2(94, -254);
		pos.x -= i * 40;
		Texture* t = mFont->RenderText(std::to_string(mPlayer->GetInv()->GetAmountOfItem(i)), Vector3(1.f, 1.f, 1.f), 16);
		t->SetActive();
		if (mPlayer->GetInv()->GetAmountOfItem(i) >= 10)
		{
			mVertArrayTwoNum->SetActive();
		}
		else
		{
			mVertArrayOneNum->SetActive();
		}
		ComputeWorldTransform(3.f, pos, mTempWorldTransform);
		ComputeViewTransform();
		mShader->SetMatrixUniform("uViewTransform", mViewTransform);
		mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		t->Unload();
		delete t;
	}
	// Draw pause menu
	if (!mGame->GetState())
	{
		mVertArrayPauseMenu->SetActive();
		mPauseMenu->SetActive();
		ComputeWorldTransform(3.f, Vector2(0.f, 0.f), mTempWorldTransform);
		ComputeViewTransform();
		mShader->SetMatrixUniform("uViewTransform", mViewTransform);
		mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		mVertArrayButton->SetActive();
		for (int i = 0; i <= 2; i++)
		{
			class Button* b = mGame->GetUI()->GetButton(i);
			mUITex[b->GetTexCode()]->SetActive();
			ComputeWorldTransform(3.f, b->GetPos(), mTempWorldTransform);
			ComputeViewTransform();
			mShader->SetMatrixUniform("uViewTransform", mViewTransform);
			mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	}
	ComputeObjViewTransform();
}