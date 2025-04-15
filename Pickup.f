#version 330 core

out vec4 FragColor;

in vec3 v_Normal;
in vec3 v_FragPos;

uniform vec3 u_LightColor;


void main()
{


	FragColor = vec4(u_LightColor, 1.0);

}

