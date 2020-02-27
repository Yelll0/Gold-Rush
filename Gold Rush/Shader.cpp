#include "stdafx.h"

Shader::Shader()
{
}

Shader::~Shader()
{
}

bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
	// Get file
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open())
	{
		// Load file into string
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		// Try to compile shader
		outShader = glCreateShader(shaderType);
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);

		if (!IsCompiled(outShader))
		{
			SDL_Log("Unable to compile shader %s", fileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Shader file not found: %s", fileName.c_str());
		return false;
	}
	return true;
}

bool Shader::IsCompiled(GLuint shader)
{
	GLint status;
	// Request compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("Unable to compile GLSL:\n%s", buffer);
		return false;
	}
	return true;
}

bool Shader::IsValidProgram()
{
	GLint status;
	// Request program status
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
		SDL_Log("Unable to link shaders:\n%s", buffer);
		return false;
	}
	return true;
}

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
	// Compile shaders
	if (!CompileShader(vertName, GL_VERTEX_SHADER, mVertexShader) || !CompileShader(fragName, GL_FRAGMENT_SHADER, mFragShader))
	{
		return false;
	}

	// Combine both shader programs into one program
	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragShader);
	glLinkProgram(mShaderProgram);

	// Make sure linking was succesful
	if (!IsValidProgram())
	{
		return false;
	}
	return true;
}

void Shader::SetActive()
{
	glUseProgram(mShaderProgram);
}

void Shader::Unload()
{
	glDeleteProgram(mShaderProgram);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragShader);
}

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
	// Find uniform
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	// Copy matrix to uniform
	glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr());
}