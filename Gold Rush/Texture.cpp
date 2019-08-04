#include "Texture.h"

Texture::Texture()
	: mWidth(NULL),
	mHeight(NULL),
	mTextureID(NULL)
{
}


Texture::~Texture()
{
}

bool Texture::Load(const std::string& fileName)
{
	// Load image from hard drive
	int channels = 0;
	unsigned char* image = SOIL_load_image(
		fileName.c_str(),
		&mWidth,
		&mHeight,
		&channels,
		SOIL_LOAD_AUTO
	);

	if (!image)
	{
		SDL_Log("SOIL unable to load image: %s: %s", fileName.c_str(), SOIL_last_result());
		return false;
	}

	int format = GL_RGB;
	if (channels == 4)
	{
		format = GL_RGBA;
	}
	// Create OpenGL texture
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	// Copy image data onto texture
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		format,
		mWidth,
		mHeight,
		0,
		format,
		GL_UNSIGNED_BYTE,
		image
	);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}