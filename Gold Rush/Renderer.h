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

	void Draw(float deltaTime);

	void ComputeWorldTransform(float scale, Vector2 pixPos, Matrix4& worldTransform);
	void ComputeObjViewTransform();
	void ComputeViewTransform();
	void DrawTexture(class Shader* shader, class Texture* texture, const Vector2& offset = Vector2::Zero, float scale = 1.f);

private:
	// Member variables
	class Game* mGame;
	class Player* mPlayer;
	class World* mWorld;
	class Shader* mShader;
	class Texture* mPlayerTex;
	std::vector<class Texture*> mPlayerWalkTex;
	std::vector<class Texture*> mPlayerMineTex;
	float mCurrFrame = 0;
	std::map<int, class Texture*> mTex;
	class Texture* mPauseMenu;
	class Texture* mHUDTex;
	std::map<int, class Texture*> mUITex; 
	class Font* mFont;
	class VertexArray* mVertArray;
	class VertexArray* mVertArrayM;
	class VertexArray* mVertArrayS;
	class VertexArray* mVertArrayButton;
	class VertexArray* mVertArrayPauseMenu;
	class VertexArray* mVertArrayHUD;
	class VertexArray* mVertArrayOneNum;
	class VertexArray* mVertArrayTwoNum;
	Matrix4 mViewTransform;
	Matrix4 mTempWorldTransform;
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
	float mSmallQuadVerts[20] = {
		-5.f,  5.f, 0.0f, 0.f, 0.f,
		 5.f,  5.f, 0.0f, 1.f, 0.f,
		 5.f, -5.f, 0.0f, 1.f, 1.f,
		-5.f, -5.f, 0.0f, 0.f, 1.f
	};
	float mOneNumVerts[20] = {
		-3.f,  4.f, 0.0f, 0.f, 0.f,
		 3.f,  4.f, 0.0f, 1.f, 0.f,
		 3.f, -4.f, 0.0f, 1.f, 1.f,
		-3.f, -4.f, 0.0f, 0.f, 1.f
	};
	float mTwoNumVerts[20] = {
		-6.f,  4.f, 0.0f, 0.f, 0.f,
		 6.f,  4.f, 0.0f, 1.f, 0.f,
		 6.f, -4.f, 0.0f, 1.f, 1.f,
		-6.f, -4.f, 0.0f, 0.f, 1.f
	};
	float mButtonVerts[20] = {
		-12.f,  12.f, 0.0f, 0.f, 0.f,
		 12.f,  12.f, 0.0f, 1.f, 0.f,
		 12.f, -12.f, 0.0f, 1.f, 1.f,
		-12.f, -12.f, 0.0f, 0.f, 1.f
	};
	float mPauseMenuVerts[20] = {
		-43.f,  15.f, 0.0f, 0.f, 0.f,
		 43.f,  15.f, 0.0f, 1.f, 0.f,
		 43.f, -15.f, 0.0f, 1.f, 1.f,
		-43.f, -15.f, 0.0f, 0.f, 1.f
	};
	float mHUDVerts[20] = {
		-67.f,  14.f, 0.0f, 0.f, 0.f,
		 67.f,  14.f, 0.0f, 1.f, 0.f,
		 67.f, -14.f, 0.0f, 1.f, 1.f,
		-67.f, -14.f, 0.0f, 0.f, 1.f
	};
	unsigned int mQuadBuffer[6] = {
		0, 1, 2,
		2, 3, 0
	};
};