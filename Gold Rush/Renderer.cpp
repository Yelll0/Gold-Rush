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
	mVertArray = new VertexArray(mQuadVerts, 4, mQuadBuffer, 6);

	mPlayerTex = new Texture("Sprites/miner.png");

	// 0 = Air
	// 1 = Grass/dirt
	// 2 = Stone
	// 3 = Coal
	// 4 = Copper
	// 5 = Iron
	// 6 = Titanium
	// 7 = Mithril
	// 8 = Gold
	mTex.emplace(0, new Texture("Sprites/air.png"));
	mTex.emplace(1, new Texture("Sprites/grass.png"));
	mTex.emplace(2, new Texture("Sprites/stone.png"));
	mTex.emplace(8, new Texture("Sprites/gold.png"));

	mOxygenTex = new Texture("Sprites/oxygen.png");
	mOxygenTextTex = new Texture("Sprites/oxygentxt.png");

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
	mViewTransform = Matrix4::CreateTranslation(Vector3(-1.f * p.x, -1.f * p.y, 0.f)) * Matrix4::CreateSimpleViewProj(540.f, 540.f);
}

void Renderer::ComputeViewTransform()
{
	mViewTransform = Matrix4::CreateSimpleViewProj(540.f, 540.f);
}

void Renderer::Draw() 
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw world
	// Activate vertex array and shader program
	// TODO: Comments
	mVertArray->SetActive();
	mShader->SetActive();
	Matrix4 tempWorldTransform;
	Vector2 playerPos = mPlayer->GetPos();

	for (int y = playerPos.y - 5; y <= playerPos.y + 5; y++)
	{
		for (int x = playerPos.x - 5; x <= playerPos.x + 5; x++)
		{
			mTex[mGame->GetWorld()->GetBlock(x, y)]->SetActive();
			
			ComputeWorldTransform(3.f, Vector2(x * 60, y * 60), tempWorldTransform);
			mShader->SetMatrixUniform("uViewTransform", mViewTransform);
			mShader->SetMatrixUniform("uWorldTransform", tempWorldTransform);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	}

	mVertArray->SetVertexBuffer(mSmallQuadVerts, 4, mQuadBuffer, 6);

	// Draw oxygen bar
	for (int i = floor(mPlayer->GetOxygen() / 5.f); i >= 0; i--)
	{
		mOxygenTex->SetActive();

		ComputeWorldTransform(3.f, Vector2(-219.f, -204.f + i*30), tempWorldTransform);
		ComputeViewTransform();
		mShader->SetMatrixUniform("uViewTransform", mViewTransform);
		mShader->SetMatrixUniform("uWorldTransform", tempWorldTransform);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
	// Draw oxygen icon
	mOxygenTextTex->SetActive();
	ComputeWorldTransform(3.f, Vector2(-219.f, -234.f), tempWorldTransform);
	ComputeViewTransform();
	mShader->SetMatrixUniform("uViewTransform", mViewTransform);
	mShader->SetMatrixUniform("uWorldTransform", tempWorldTransform);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	// Draw player
	// Flip the player according to its face direction
	mVertArray->SetVertexBuffer(mQuadVertsM, 4, mQuadBuffer, 6);
	if (mPlayer->GetFacing())
	{
		mVertArray->SetVertexBuffer(mQuadVerts, 4, mQuadBuffer, 6);
	}
	// Activate player texture
	mPlayerTex->SetActive();

	// Apply matrices
	ComputeObjViewTransform();
	mShader->SetMatrixUniform("uViewTransform", mViewTransform);
	mShader->SetMatrixUniform("uWorldTransform", mPlayer->GetWorldTransform());

	// Draw quads
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}