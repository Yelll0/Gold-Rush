// GLSL 3.3
#version 330

// Uniform (constant) matrices
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

// Vertex attributes
in vec3 inPosition;
void main()
{
	// Convert position to a vec4
	vec4 pos = vec4(inPosition, 1.0);
	gl_Position = pos * uWorldTransform * uViewProj;
}