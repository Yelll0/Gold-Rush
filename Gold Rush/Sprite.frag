// GLSL 3.3
#version 330

// Frag coord from vertex shader
in vec2 fragTexCoord;

out vec4 outColor;

uniform sampler2D uTexture;

void main()
{
	outColor = texture(uTexture, fragTexCoord);
}