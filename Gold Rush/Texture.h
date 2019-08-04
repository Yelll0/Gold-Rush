#pragma once

#include "stdafx.h"

class Texture
{
public:
	Texture();
	~Texture();

	bool Load(const std::string& fileName);
	void Unload();
	
	void SetActive();

	// Getters and setters
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

private:
	// OpenGL ID
	unsigned int mTextureID;
	// Dimensions of texture
	int mWidth;
	int mHeight;
};

