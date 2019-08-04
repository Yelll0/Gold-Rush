#include "Renderer.h"

Renderer::Renderer(class Game* game, class Player* player)
{
	mGame = game;
	mPlayer = player;
	mRecomputeViewTransform = true;
}

Renderer::~Renderer()
{

}

bool Renderer::Init()
{
	// Load shaders
	mShader = new Shader();
	if (!mShader->Load("Shaders/Transform.vert", "Shaders/Basic.frag"))
	{
		return false;
	}
	mShader->SetActive();

	// Load vertex array
	mVertArray = new VertexArray(mQuadVerts, 4, mQuadBuffer, 6);

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
	// Activate vertex array and shader program
	mShader->SetActive();
	mVertArray->SetActive();
	
	ComputeViewTransform();
	Matrix4 worldTransform = mPlayer->GetWorldTransform();
	mShader->SetMatrixUniform("uWorldTransform", worldTransform);

	// Draw quads
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}