#include "Renderer.h"

Renderer::Renderer(Game* game)
{
	mGame = game;
	mShader = nullptr;
	mVertArray = nullptr;
}

Renderer::~Renderer()
{

}

bool Renderer::Init()
{
	// Load shaders
	mShader = new Shader();
	if (!mShader->Load("Transform.vert", "Basic.frag"))
	{
		return false;
	}
	mShader->SetActive();

	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1024.f, 768.f);
	mShader->SetMatrixUniform("uViewProj", viewProj);
	
	// [TEMP] Vertex arrays and buffers
	float playerVertexBuffer[] = {
		-5.f,  5.f, 0.f, 
		 5.f,  5.f, 0.f, 
		 5.f, -5.f, 0.f, 
		-5.f, -5.f, 0.f, 
	};
	unsigned int indexBuffer[] = {
		0, 1, 2,
		2, 3, 0
	};

	// Load vertex array
	mVertArray = new VertexArray(playerVertexBuffer, 4, indexBuffer, 6);

	return true;
}

void Renderer::Draw() 
{
	// Activate vertex array and shader program
	mShader->SetActive();
	mVertArray->SetActive();

	// Draw player
	Matrix4 playerPos = mGame->GetPlayer()->GetWorldTransform();

	mShader->SetMatrixUniform("uWorldTransform", playerPos);

	// TODO: Draw map

	// Draw scene
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}