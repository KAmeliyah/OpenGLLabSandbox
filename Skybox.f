attribute vec3 a_TexCoords;

uniform samplerCube skybox;

void main()
{
	gl_FragColor = texture(skybox, TexCoords);

}