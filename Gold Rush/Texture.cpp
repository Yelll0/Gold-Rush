#include "Texture.h"

Texture::Texture()
{

}

Texture::~Texture()
{

}

bool Texture::Load(const std::string& fileName)
{
	// Use SOIL to load image
	int channels = 0;
	unsigned char* image = SOIL_load_image(
		fileName.c_str(),
		&mWidth,
		&mHeight,
		&channels,
		SOIL_LOAD_AUTO
	);
	// Check for image
	if (!image)
	{
		SDL_Log("Unable to load image %s: %s", fileName.c_str(), SOIL_last_result());
		return false;
	}
	
	// RGB or RGBA
	int format = GL_RGB;
	if (channels == 4)
	{
		format = GL_RGBA;
	}

	// Generate the OpenGL texture object
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	// Copy image data into texture
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
	// Enable nearest neighbour filtering
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