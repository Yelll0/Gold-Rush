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
	void SetPlayer(class Player* player) { mPlayer = player; }
	void SetWorld(class World* world) { mWorld = world; }

private:
	// Member variables
	class Game* mGame;
	class Player* mPlayer;
	class World* mWorld;
	class Shader* mShader;
	class Texture* mPlayerTex;
	std::vector<class Texture*> mPlayerIdleTex;
	std::vector<class Texture*> mPlayerWalkTex;
	std::vector<class Texture*> mPlayerMineTex;
	std::vector<class Texture*> mPlayerMineUpTex;
	float mCurrFrame = 0;
	std::map<int, class Texture*> mTex;
	std::vector<class Texture*> mDamTex;
	class Texture* mPauseMenu;
	class Texture* mHUDTex;
	std::map<int, class Texture*> mUITex; 
	class Texture* mBGTex;
	class Texture* mMBGTex;
	class Texture* mEBGTex;
	class Font* mFont;
	class VertexArray* mVertArray;
	class VertexArray* mVertArrayM;
	class VertexArray* mVertArrayS;
	class VertexArray* mVertArrayButton;
	class VertexArray* mVertArrayPauseMenu;
	class VertexArray* mVertArrayWindow;
	class VertexArray* mVertArrayHUD;
	class VertexArray* mVertArrayLogo;
	class VertexArray* mVertArrayOneNum;
	class VertexArray* mVertArrayTwoNum;
	class VertexArray* mVertArrayThreeNum;
	class VertexArray* mVertArrayFourNum;
	class VertexArray* mVertArrayFiveNum;
	class VertexArray* mVertArrayGameOver;
	class VertexArray* mVertArrayYouWin;
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
	float mThreeNumVerts[20] = {
		-9.f,  4.f, 0.0f, 0.f, 0.f,
		 9.f,  4.f, 0.0f, 1.f, 0.f,
		 9.f, -4.f, 0.0f, 1.f, 1.f,
		-9.f, -4.f, 0.0f, 0.f, 1.f
	};
	float mFourNumVerts[20] = {
		-12.f,  4.f, 0.0f, 0.f, 0.f,
		 12.f,  4.f, 0.0f, 1.f, 0.f,
		 12.f, -4.f, 0.0f, 1.f, 1.f,
		-12.f, -4.f, 0.0f, 0.f, 1.f
	};
	float mFiveNumVerts[20] = {
		-15.f,  4.f, 0.0f, 0.f, 0.f,
		 15.f,  4.f, 0.0f, 1.f, 0.f,
		 15.f, -4.f, 0.0f, 1.f, 1.f,
		-15.f, -4.f, 0.0f, 0.f, 1.f
	};
	float mGameOverVerts[20] = {
		-54.f,  8.f, 0.0f, 0.f, 0.f,
		 54.f,  8.f, 0.0f, 1.f, 0.f,
		 54.f, -8.f, 0.0f, 1.f, 1.f,
		-54.f, -8.f, 0.0f, 0.f, 1.f
	};
	float mYouWinVerts[20] = {
		-42.f,  8.f, 0.0f, 0.f, 0.f,
		 42.f,  8.f, 0.0f, 1.f, 0.f,
		 42.f, -8.f, 0.0f, 1.f, 1.f,
		-42.f, -8.f, 0.0f, 0.f, 1.f
	};
	float mButtonVerts[20] = {
		-12.f,  12.f, 0.0f, 0.f, 0.f,
		 12.f,  12.f, 0.0f, 1.f, 0.f,
		 12.f, -12.f, 0.0f, 1.f, 1.f,
		-12.f, -12.f, 0.0f, 0.f, 1.f
	};
	float mLogoVerts[20] = {
		-46.f,  35.f, 0.0f, 0.f, 0.f,
		 46.f,  35.f, 0.0f, 1.f, 0.f,
		 46.f, -35.f, 0.0f, 1.f, 1.f,
		-46.f, -35.f, 0.0f, 0.f, 1.f
	};
	float mPauseMenuVerts[20] = {
		-43.f,  15.f, 0.0f, 0.f, 0.f,
		 43.f,  15.f, 0.0f, 1.f, 0.f,
		 43.f, -15.f, 0.0f, 1.f, 1.f,
		-43.f, -15.f, 0.0f, 0.f, 1.f
	};
	float mHUDVerts[20] = {
		-68.f,  14.f, 0.0f, 0.f, 0.f,
		 68.f,  14.f, 0.0f, 1.f, 0.f,
		 68.f, -14.f, 0.0f, 1.f, 1.f,
		-68.f, -14.f, 0.0f, 0.f, 1.f
	};
	float mWindowVerts[20] = {
		-100.f,  100.f, 0.0f, 0.f, 0.f,
		 100.f,  100.f, 0.0f, 1.f, 0.f,
		 100.f, -100.f, 0.0f, 1.f, 1.f,
		-100.f, -100.f, 0.0f, 0.f, 1.f
	};
	unsigned int mQuadBuffer[6] = {
		0, 1, 2,
		2, 3, 0
	};
};