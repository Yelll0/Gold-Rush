#pragma once

#include "stdafx.h"

class Renderer
{
public: 
	// Constructor and destructor
	Renderer(class Game* game);
	~Renderer();

	// Initialize renderer
	bool Init();

	void Draw();

private:
	// Member variables
	class Game* mGame;
	class Shader* mShader;
	class VertexArray* mVertArray;
};