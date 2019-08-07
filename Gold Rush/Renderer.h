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

	void ComputeWorldTransform(float scale, Vector2 pixPos, Matrix4& worldTransform);
	void ComputeViewTransform();

private:
	// Member variables
	class Game* mGame;
	class Player* mPlayer;
	class World* mWorld;
	class Shader* mShader;
	class Texture* mPlayerTex;
	std::map<int, class Texture*> mTex;
	class VertexArray* mVertArray;
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