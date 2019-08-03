// GLSL 3.3
#version 330

// Vertex attributes
in vec3 inPosition;

void main()
{
	// Pass inPosition into gll_Position
	gl_Position = vec4(inPosition, 1.0);
}