#pragma once

#include "stdafx.h"

class Font
{
public:
	Font();
	~Font();

	bool Load(const std::string& fileName);
	void Unload();

	// Render string in font onto a texture
	class Texture* RenderText(const std::string& text,
		const Vector3& color,
		int pointSize);

private: 
	std::unordered_map<int, TTF_Font*> mFontData;
};