#include "Renderer.h"

Renderer::Renderer(class Game* game, class Player* player)
	: mGame(game),
	mPlayer(player),
	mRecomputeViewTransform(true),
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

	mPlayerTex = new Texture();
	mPlayerTex->Load("Sprites/miner.png");

	return true;
}

void Renderer::ComputeViewTransform()
{
	if (mRecomputeViewTransform)
	{
		mRecomputeViewTransform = false;
		// Recenter around player
		Vector2 p = mPlayer->GetPos();
		mViewTransform = Matrix4::CreateTranslation(Vector3(-1.f * p.x, -1.f * p.y, 0.f)) * Matrix4::CreateSimpleViewProj(540.f, 540.f);
		mShader->SetMatrixUniform("uViewTransform", mViewTransform);
	}
}

void Renderer::Draw() 
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Flip the player according to its face direction
	mVertArray->SetVertexBuffer(mQuadVertsM, 4, mQuadBuffer, 6);
	if (mPlayer->GetFacing()) 
	{
		mVertArray->SetVertexBuffer(mQuadVerts, 4, mQuadBuffer, 6);
	}
	// Activate vertex array and shader program
	mVertArray->SetActive();
	mShader->SetActive();
	mPlayerTex->SetActive();
	
	ComputeViewTransform();
	Matrix4 worldTransform = mPlayer->GetWorldTransform();
	mShader->SetMatrixUniform("uWorldTransform", worldTransform);

	// Draw quads
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}