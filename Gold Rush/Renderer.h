#pragma once

#include "stdafx.h"

class Renderer
{
public: 
	// Constructor and destructor
	Renderer(class Game* game, class Player* player);
	~Renderer();

	// Initialize renderer
	bool Init();

	void Draw();

	void ComputeViewTransform();

private:
	// Member variables
	class Game* mGame;
	class Player* mPlayer;
	class Shader* mShader;
	class VertexArray* mVertArray;
	bool mRecomputeViewTransform;
	Matrix4 mViewTransform;
	// Quad vertex arrays and buffers
	float mQuadVerts[12] = {
		-10.f,  10.f, 0.0f,
		 10.f,  10.f, 0.0f,
		 10.f, -10.f, 0.0f,
		-10.f, -10.f, 0.0f
	};
	unsigned int mQuadBuffer[6] = {
		0, 1, 2,
		2, 3, 0
	};
};