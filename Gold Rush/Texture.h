#pragma once

#include "stdafx.h"

class Texture
{
public:
	Texture();
	~Texture();

	// Load and unload texture
	bool Load(const std::string& fileName);
	void Unload();

	// Activate this texture
	void SetActive();

	// Good ol' getters
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

private:
	// OpenGL ID
	unsigned int mTextureID;

	// Dimensions
	int mWidth;
	int mHeight;
};