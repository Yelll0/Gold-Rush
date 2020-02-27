#pragma once

#include "stdafx.h"

class VertexArray
{
public:
	// Constructor and destructor
	VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndicies);
	~VertexArray();

	// Activate vertex array to draw
	void SetActive();

	// Getters and setters
	unsigned int GetNumIndicies() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }

private:
	// Amount of vertices and indices
	unsigned int mNumVerts;
	unsigned int mNumIndices;

	// OpenGL IDs
	unsigned int mVertexBuffer;
	unsigned int mIndexBuffer;
	unsigned int mVertexArray;
};