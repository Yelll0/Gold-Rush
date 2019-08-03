#pragma once

#include "stdafx.h"

class Shader
{
public:
	// Constructor and destructor
	Shader();
	~Shader();

	// Load shader files
	bool Load(const std::string& vertName, const std::string& fragName);
	// Activate this shader program
	void SetActive();
	// Unload this shader
	void Unload();
	
	void SetMatrixUniform(const char* name, const Matrix4& matrix);

private:
	// Compile GLSL code
	bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
	// Check if the shader compiled properly
	bool IsCompiled(GLuint shader);
	// Check if the shaders link
	bool IsValidProgram();
	
	// Shader IDs
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};