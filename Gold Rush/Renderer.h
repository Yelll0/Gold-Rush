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
	class Texture* mPlayerTex;
	class VertexArray* mVertArray;
	bool mRecomputeViewTransform;
	Matrix4 mViewTransform;
	// Quad vertex arrays and buffers
	float mQuadVerts[20] = {
		-10.f,  10.f, 0.0f, 0.f, 0.f,
		 10.f,  10.f, 0.0f, 1.f, 0.f,
		 10.f, -10.f, 0.0f, 1.f, 1.f,
		-10.f, -10.f, 0.0f, 0.f, 1.f
	};
	float mQuadVertsM[20] = {
		-10.f,  10.f, 0.0f, 1.f, 0.f,
		 10.f,  10.f, 0.0f, 0.f, 0.f,
		 10.f, -10.f, 0.0f, 0.f, 1.f,
		-10.f, -10.f, 0.0f, 1.f, 1.f
	};
	unsigned int mQuadBuffer[6] = {
		0, 1, 2,
		2, 3, 0
	};
};