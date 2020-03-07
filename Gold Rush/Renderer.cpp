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
	mVertArrayWindow = new VertexArray(mWindowVerts, 4, mQuadBuffer, 6);
	mVertArrayOneNum = new VertexArray(mOneNumVerts, 4, mQuadBuffer, 6);
	mVertArrayTwoNum = new VertexArray(mTwoNumVerts, 4, mQuadBuffer, 6);
	mVertArrayThreeNum = new VertexArray(mThreeNumVerts, 4, mQuadBuffer, 6);
	mVertArrayFourNum = new VertexArray(mFourNumVerts, 4, mQuadBuffer, 6);
	mVertArrayFiveNum = new VertexArray(mFiveNumVerts, 4, mQuadBuffer, 6);
	mVertArrayLogo = new VertexArray(mLogoVerts, 4, mQuadBuffer, 6);

	// Player textures
	mPlayerTex = new Texture("Sprites/miner/miner.png", true);
	mBGTex = new Texture("Sprites/bg.png", true);
	mMBGTex = new Texture("Sprites/mbg.png", true);
	mPlayerIdleTex.emplace_back(new Texture("Sprites/miner/miner.png", true));
	mPlayerIdleTex.emplace_back(new Texture("Sprites/miner/miner-idle.png", true));
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
	mPlayerMineUpTex.emplace_back(new Texture("Sprites/miner/miner-mine-u1.png", true));
	mPlayerMineUpTex.emplace_back(new Texture("Sprites/miner/miner-mine-u2.png", true));
	mPlayerMineUpTex.emplace_back(new Texture("Sprites/miner/miner-mine-u3.png", true));
	mPlayerMineUpTex.emplace_back(new Texture("Sprites/miner/miner-mine-u4.png", true));
	mPlayerMineUpTex.emplace_back(new Texture("Sprites/miner/miner-mine-u5.png", true));
	mPlayerMineUpTex.emplace_back(new Texture("Sprites/miner/miner-mine-u6.png", true));
	mPlayerMineUpTex.emplace_back(new Texture("Sprites/miner/miner-mine-u7.png", true));
	mPlayerMineUpTex.emplace_back(new Texture("Sprites/miner/miner-mine-u8.png", true));

	mDamTex.emplace_back(new Texture("Sprites/dam1.png", true));
	mDamTex.emplace_back(new Texture("Sprites/dam2.png", true));
	mDamTex.emplace_back(new Texture("Sprites/dam3.png", true));

	mTex.emplace(0, new Texture("Sprites/air.png", true));
	mTex.emplace(1, new Texture("Sprites/grass.png", true));
	mTex.emplace(2, new Texture("Sprites/stone.png", true));
	mTex.emplace(3, new Texture("Sprites/coal.png", true));
	mTex.emplace(4, new Texture("Sprites/copper.png", true));
	mTex.emplace(5, new Texture("Sprites/iron.png", true));
	mTex.emplace(6, new Texture("Sprites/titanium.png", true));
	mTex.emplace(7, new Texture("Sprites/mithril.png", true));
	mTex.emplace(8, new Texture("Sprites/gold.png", true));
	mTex.emplace(10, new Texture("Sprites/sky.png", true));
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
	mUITex.emplace(102, new Texture("Sprites/upgrade-pick-hl.png", true));
	mUITex.emplace(3, new Texture("Sprites/play.png", true));
	mUITex.emplace(103, new Texture("Sprites/play-hl.png", true));
	mUITex.emplace(4, new Texture("Sprites/sound.png", true));
	mUITex.emplace(104, new Texture("Sprites/sound-hl.png", true));
	mUITex.emplace(5, new Texture("Sprites/mute.png", true));
	mUITex.emplace(105, new Texture("Sprites/mute-hl.png", true));
	mUITex.emplace(6, new Texture("Sprites/home.png", true));
	mUITex.emplace(106, new Texture("Sprites/home-hl.png", true));
	mUITex.emplace(7, new Texture("Sprites/craft-bomb.png", true));
	mUITex.emplace(107, new Texture("Sprites/craft-bomb-hl.png", true));
	mUITex.emplace(8, new Texture("Sprites/use-bomb.png", true));
	mUITex.emplace(108, new Texture("Sprites/use-bomb-hl.png", true));
	mUITex.emplace(9, new Texture("Sprites/pause.png", true));
	mUITex.emplace(109, new Texture("Sprites/pause-hl.png", true));
	mUITex.emplace(10, new Texture("Sprites/gold-ingot.png", true));
	mUITex.emplace(11, new Texture("Sprites/coal-frag.png", true));
	mUITex.emplace(12, new Texture("Sprites/copper-ingot.png", true));
	mUITex.emplace(13, new Texture("Sprites/iron-ingot.png", true));
	mUITex.emplace(14, new Texture("Sprites/titanium-ingot.png", true));
	mUITex.emplace(15, new Texture("Sprites/mithril-ingot.png", true));
	mUITex.emplace(20, new Texture("Sprites/bomb.png", true));
	mUITex.emplace(21, new Texture("Sprites/default-pickaxe.png", true));
	mUITex.emplace(22, new Texture("Sprites/copper-pickaxe.png", true));
	mUITex.emplace(23, new Texture("Sprites/iron-pickaxe.png", true));
	mUITex.emplace(24, new Texture("Sprites/titanium-pickaxe.png", true));
	mUITex.emplace(25, new Texture("Sprites/mithril-pickaxe.png", true));
	mUITex.emplace(100, new Texture("Sprites/logo.png", true));
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
	100 - Logo
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
	if (mGame->GetState() > -1)
	{
		// Draw background
		mVertArrayWindow->SetActive();
		mBGTex->SetActive();
		ComputeWorldTransform(3.f, Vector2(0, 0), mTempWorldTransform);
		ComputeViewTransform();
		mShader->SetMatrixUniform("uViewTransform", mViewTransform);
		mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		// Draw world
		mVertArray->SetActive();
		Vector2 playerPos = mPlayer->GetPos();
		for (int y = playerPos.y - 6; y <= playerPos.y + 6; y++)
		{
			for (int x = playerPos.x - 6; x <= playerPos.x + 6; x++)
			{
				int b = mGame->GetWorld()->GetBlock(x, y);
				mTex[b]->SetActive();
				ComputeWorldTransform(3.f, Vector2(x * 60, y * 60), mTempWorldTransform);
				ComputeObjViewTransform();
				mShader->SetMatrixUniform("uViewTransform", mViewTransform);
				mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

				float d = mGame->GetWorld()->GetBlockDamage(x, y);
				if (d < 1 && d > 0.25f && b > 0)
				{
					mDamTex[floor(d * 4 - 1)]->SetActive();
					mShader->SetMatrixUniform("uViewTransform", mViewTransform);
					mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
				}
			}
		}

		// Draw player
		// Flip the player according to its face direction
		if (mPlayer->GetFacing())
		{
			mVertArrayM->SetActive();
		}

		mCurrFrame += 16 * deltaTime;

		if (mPlayer->GetIsWalking())
		{
			while (mCurrFrame > 10)
			{
				mCurrFrame = 0;
			}
			mPlayerWalkTex[mCurrFrame]->SetActive();
		}
		else if (mPlayer->GetIsMiningUp())
		{
			while (mCurrFrame > 8)
			{
				mCurrFrame = 0;
			}
			mPlayerMineUpTex[mCurrFrame]->SetActive();
		}
		else if (mPlayer->GetIsMining())
		{
			while (mCurrFrame > 5)
			{
				mCurrFrame = 0;
			}
			mPlayerMineTex[mCurrFrame]->SetActive();
		}
		else
		{
			while (mCurrFrame > 6)
			{
				mCurrFrame = 0;
			}
			mPlayerIdleTex[mCurrFrame / 3]->SetActive();
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

		// Draw numbers 
		for (int i = 0; i <= 6; i++)
		{
			Vector2 pos = Vector2(94, -254);
			pos.x -= i * 40;
			Texture * t = mFont->RenderText(std::to_string(mPlayer->GetInv()->GetAmountOfItem(i)), Vector3(1.f, 1.f, 1.f), 16);
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
		mVertArrayS->SetActive();
		for (int i = 0; i <= mGame->GetHUD()->GetNumButtons() - 1; i++)
		{
			class Button* b = mGame->GetHUD()->GetButton(i);
			mUITex[b->GetTexCode()]->SetActive();
			ComputeWorldTransform(3.f, b->GetPos(), mTempWorldTransform);
			ComputeViewTransform();
			mShader->SetMatrixUniform("uViewTransform", mViewTransform);
			mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
		// Draw score
		// Text
		Texture* ts = mFont->RenderText("SCORE", Vector3(1.f, 1.f, 1.f), 16);
		mVertArrayFiveNum->SetActive();
		ComputeWorldTransform(3.f, Vector2(-186.f, 239.f), mTempWorldTransform);
		ComputeViewTransform();
		mShader->SetMatrixUniform("uViewTransform", mViewTransform);
		mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		ts->Unload();
		// Number
		int s = mPlayer->GetInv()->GetScore();
		Texture* tsc = mFont->RenderText(std::to_string(s), Vector3(1.f, 1.f, 1.f), 16);
		tsc->SetActive();
		if (s >= 10000)
		{
			mVertArrayFiveNum->SetActive();
		}
		else if (s >= 1000)
		{
			mVertArrayFourNum->SetActive();
		}
		else if (s >= 100)
		{
			mVertArrayThreeNum->SetActive();
		}
		else if (s >= 10)
		{
			mVertArrayTwoNum->SetActive();
		}
		else
		{
			mVertArrayOneNum->SetActive();
		}
		ComputeWorldTransform(3.f, Vector2(-186.f, 209.f), mTempWorldTransform);
		ComputeViewTransform();
		mShader->SetMatrixUniform("uViewTransform", mViewTransform);
		mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		tsc->Unload();

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
		// If game is over 
		if (mGame->GetState() == 2)
		{
			for (int i = 0; i <= 0; i++)
			{
				mVertArrayButton->SetActive();
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
	// Draw main menu
	else
	{
		// Draw background
		mVertArrayWindow->SetActive();
		mMBGTex->SetActive();
		ComputeWorldTransform(3.f, Vector2(0, 0), mTempWorldTransform);
		ComputeViewTransform();
		mShader->SetMatrixUniform("uViewTransform", mViewTransform);
		mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		// Draw logo
		mVertArrayLogo->SetActive();
		mUITex[100]->SetActive();
		ComputeWorldTransform(3.f, Vector2(0.f, 74.f), mTempWorldTransform);
		ComputeViewTransform();
		mShader->SetMatrixUniform("uViewTransform", mViewTransform);
		mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		// Draw buttons
		for (int i = 0; i <= 0; i++)
		{
			mVertArrayButton->SetActive();
			class Button* b = mGame->GetUI()->GetButton(i);
			mUITex[b->GetTexCode()]->SetActive();
			ComputeWorldTransform(3.f, b->GetPos(), mTempWorldTransform);
			ComputeViewTransform();
			mShader->SetMatrixUniform("uViewTransform", mViewTransform);
			mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	}
}