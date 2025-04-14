#version 330 core

out vec4 FragColor;

in vec2 v_TexCoords;

uniform sampler2D renderTexture;

void main()
{
	FragColor = texture(renderTexture, v_TexCoords);

}

