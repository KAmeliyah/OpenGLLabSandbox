uniform sampler2D u_Texture;

//maybe swap this out for an attribute
uniform vec3 u_LightPos;



varying vec2 v_TexCoord;
varying vec3 v_Normal;
varying vec3 v_FragPos;

                        
void main()               
{
	
	vec3 diffuseColor = vec3(1,1,1);

	vec3 N = normalize(v_Normal);
	vec3 lightDir = normalize(u_LightPos - v_FragPos);
	float diff = max(dot(N,lightDir), 0.0);
	vec3 diffuse = diffuseColor * diff;

	vec3 lighting = diffuse;

	vec4 tex = texture2D(u_Texture, v_TexCoord);
	gl_FragColor = vec4(lighting,1) * tex;
	
}