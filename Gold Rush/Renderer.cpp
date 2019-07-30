#include "Renderer.h"

Renderer::Renderer(Game* game)
{
	mGame = game;
}

Renderer::~Renderer()
{

}

bool Renderer::Init()
{
	// Load shaders
	mShader = new Shader();
	if (!mShader->Load("Basic.vert", "Basic.frag"))
	{
		return false;
	}
	mShader->SetActive();
	
	// [TEMP] Vertex arrays and buffers
	float vertexBuffer[] = {
		-0.5, 0.5, 0.0,
		0.5, 0.5, 0.0,
		0.5, -0.5, 0.0,
		-0.5, -0.5, 0.0
	};
	unsigned int indexBuffer[] = {
		0, 1, 2,
		2, 3, 0
	};

	// Load vertex array
	mVertArray = new VertexArray(vertexBuffer, 4, indexBuffer, 6);

	return true;
}

void Renderer::Draw() 
{
	// Activate vertex array and shader program
	mShader->SetActive();
	mVertArray->SetActive();
	// Draw scene
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}