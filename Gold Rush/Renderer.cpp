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

	mPlayerTex = new Texture("Sprites/miner.png");

	mTex.emplace(0, new Texture("Sprites/air.png"));
	mTex.emplace(1, new Texture("Sprites/grass.png"));
	mTex.emplace(2, new Texture("Sprites/stone.png"));
	mTex.emplace(3, new Texture("Sprites/coal.png"));
	mTex.emplace(4, new Texture("Sprites/copper.png"));
	mTex.emplace(5, new Texture("Sprites/iron.png"));
	mTex.emplace(6, new Texture("Sprites/titanium.png"));
	mTex.emplace(7, new Texture("Sprites/mithril.png"));
	mTex.emplace(8, new Texture("Sprites/gold.png"));
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
	mUITex.emplace(0, new Texture("Sprites/oxygen.png"));
	mUITex.emplace(1, new Texture("Sprites/oxygentxt.png"));
	mUITex.emplace(2, new Texture("Sprites/upgrade-pick.png"));
	mUITex.emplace(3, new Texture("Sprites/play.png"));
	mUITex.emplace(4, new Texture("Sprites/sound.png"));
	mUITex.emplace(5, new Texture("Sprites/mute.png"));
	mUITex.emplace(6, new Texture("Sprites/home.png"));
	mUITex.emplace(7, new Texture("Sprites/craft-bomb.png"));
	mUITex.emplace(8, new Texture("Sprites/bomb.png"));
	mUITex.emplace(9, new Texture("Sprites/pause.png"));
	mUITex.emplace(10, new Texture("Sprites/gold-ingot.png"));
	mUITex.emplace(11, new Texture("Sprites/coal-frag.png"));
	mUITex.emplace(12, new Texture("Sprites/copper-frag.png"));
	mUITex.emplace(13, new Texture("Sprites/iron-ingot.png"));
	mUITex.emplace(14, new Texture("Sprites/titanium-ingot.png"));
	mUITex.emplace(15, new Texture("Sprites/mithril-frag.png"));
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
	*/

	mPauseMenu = new Texture("Sprites/pause-menu.png");

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

void Renderer::Draw()
{
	// Activate shader program
	// TODO: Comments
	mShader->SetActive();

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
	// Activate player texture
	mPlayerTex->SetActive();
	// Apply matrices
	ComputeObjViewTransform();
	mShader->SetMatrixUniform("uViewTransform", mViewTransform);
	mShader->SetMatrixUniform("uWorldTransform", mPlayer->GetWorldTransform());
	// Draw quads
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	// Draw HUD
	// Draw oxygen bar
	mVertArrayS->SetActive();
	for (int i = floor(mPlayer->GetOxygen() / 5.f); i >= 0; i--)
	{
		mUITex[0]->SetActive();

		ComputeWorldTransform(3.f, Vector2(219.f, -174.f + i * 30), mTempWorldTransform);
		ComputeViewTransform();
		mShader->SetMatrixUniform("uViewTransform", mViewTransform);
		mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
	// Draw oxygen icon
	mUITex[1]->SetActive();
	ComputeWorldTransform(3.f, Vector2(219.f, -204.f), mTempWorldTransform);
	ComputeViewTransform();
	mShader->SetMatrixUniform("uViewTransform", mViewTransform);
	mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	// Draw HUD buttons
	for (int i = 0; i <= 8; i++)
	{
		class Button* b = mGame->GetHUD()->GetButton(i);
		mUITex[b->GetTexCode()]->SetActive();
		ComputeWorldTransform(3.f, b->GetPos(), mTempWorldTransform);
		ComputeViewTransform();
		mShader->SetMatrixUniform("uViewTransform", mViewTransform);
		mShader->SetMatrixUniform("uWorldTransform", mTempWorldTransform);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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