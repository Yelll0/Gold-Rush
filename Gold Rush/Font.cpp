#include "stdafx.h"

Font::Font()
{
}

Font::~Font()
{
}

bool Font::Load(const std::string& fileName)
{
	// Initialize SDL_ttf
	if (TTF_Init() != 0)
	{ 
		SDL_Log("Failed to initialize SDL_ttf");
		return 1;
	}

	// Support these font sizes
	std::vector<int> fontSizes = {
		8, 9, 10, 11, 12, 14, 16, 18
	};

	for (auto& size : fontSizes)
	{
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
		if (font == nullptr)
		{
			SDL_Log("Failed to load font %s in size %d: %s", fileName.c_str(), size, TTF_GetError());
			return false;
		}
		mFontData.emplace(size, font);
	}
	return true;
}

void Font::Unload()
{
}

class Texture* Font::RenderText(const std::string& text, const Vector3& color, int pointSize)
{
	Texture* texture = new Texture("Bruh momentum", false);
	// Convert to SDL_Color
	SDL_Color sdlColor;
	sdlColor.r = color.x * 255;
	sdlColor.g = color.y * 255;
	sdlColor.b = color.z * 255;
	sdlColor.a = 255;
	// Find font data
	auto iter = mFontData.find(pointSize);
	if (iter != mFontData.end())
	{
		TTF_Font* font = iter->second;
		// Draw to surface
		SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), sdlColor);
		if (surf)
		{
			// Convert from surface to texture
			texture = new Texture("No lole", false);
			texture->CreateFromSurface(surf);
			SDL_FreeSurface(surf);
		}
	}
	else
	{
		SDL_Log("Point size %d is not supported", pointSize);
	}
	return texture;
}