#version 330 core

//deprecated
//varying vec2 v_TexCoord;
//varying vec3 v_Normal;
//varying vec3 v_FragPos;
//varying vec3 v_ViewPos;

out vec4 FragColor;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;
in vec3 v_ViewPos;

uniform sampler2D u_Texture;
                        
void main()               
{

	vec3 lightPos = vec3(10,10,-50);
	vec3 diffuseColor = vec3(1,1,1);
	vec3 specularColor = vec3(1,1,1);


	vec3 N = normalize(v_Normal);
	vec3 lightDir = normalize(lightPos - v_FragPos);
	vec3 viewDir = normalize(v_ViewPos - v_FragPos);
	//vec3 reflectDir = reflect(-lightDir, N);

	vec3 halfwayDir = normalize(lightDir + viewDir);

	float diff = max(dot(N,lightDir), 0.0);
	vec3 diffuse = diffuseColor * diff;
	float spec = pow(max(dot(viewDir, halfwayDir), 0.0), 32);
	vec3 specular = spec * specularColor;

	vec3 lighting = diffuse + specular;

	vec4 tex = texture2D(u_Texture, v_TexCoord);
	FragColor = vec4(lighting,1) * tex;

}