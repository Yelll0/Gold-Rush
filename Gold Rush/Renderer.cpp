#include "Renderer.h"

Renderer::Renderer(class Game* game, class Player* player, class World* world)
	: mGame(game),
	mPlayer(player),
	mWorld(world),
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

	mStoneTex = new Texture();
	mStoneTex->Load("Sprites/stone.png");

	return true;
}

void Renderer::ComputeWorldTransform(float scale, Vector2 pixPos, Matrix4& worldTransform)
{
	worldTransform = Matrix4::CreateScale(scale);
	worldTransform *= Matrix4::CreateTranslation(Vector3(pixPos.x, pixPos.y, 0.f));
}

void Renderer::ComputeViewTransform()
{
	// Recenter around player
	Vector2 p = mPlayer->GetPixPos();
	mViewTransform = Matrix4::CreateTranslation(Vector3(-1.f * p.x, -1.f * p.y, 0.f)) * Matrix4::CreateSimpleViewProj(540.f, 540.f);
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
	
	// Apply matrices
	ComputeViewTransform();
	mShader->SetMatrixUniform("uViewTransform", mViewTransform);
	mShader->SetMatrixUniform("uWorldTransform", mPlayer->GetWorldTransform());

	// Draw quads
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	
	mVertArray->SetActive();
	mShader->SetActive();
	mStoneTex->SetActive();
	Matrix4 tempWorldTransform;
	ComputeWorldTransform(3.f, Vector2(6300.f, 32160.f), tempWorldTransform);
	ComputeViewTransform();
	mShader->SetMatrixUniform("uViewTransform", mViewTransform);
	mShader->SetMatrixUniform("uWorldTransform", tempWorldTransform);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}