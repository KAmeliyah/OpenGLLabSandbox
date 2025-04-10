attribute vec3 a_Position;


varying vec3 v_TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	
	v_TexCoords = a_Position;
	gl_Position = projection * view * vec4(a_Position, 1.0);

}
