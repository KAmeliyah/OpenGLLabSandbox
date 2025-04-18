#version 330 core
// Includes multiple lights and directional light
// Can include some funky stuff from other shaders


//ins and outs
out vec4 FragColor;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;
in vec3 v_ViewPos;

//Any RBO textures


const int MAX_LIGHTS = 4;

//structs
struct DirectionalLight {

	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};


//Pickups, regular lights

struct PointLight {

	vec3 position;
	vec3 color;

};


//functions declarations
vec3 CalculateDirLight(vec3 _n, vec3 _fragPos ,vec3 _viewDir);
vec3 CalculatePointLight(vec3 _n, vec3 _fragPos, vec3 _viewDir);


//uniforms
uniform vec3 u_DirLight;	//direction of directional light
uniform vec3 u_PLightPos;	//position of point light
uniform vec3 u_PLightColor;	//color of point light

uniform int u_PointLightCount;
uniform PointLight u_PointLights[MAX_LIGHTS];

uniform sampler2D u_Texture;



void main()
{
	vec3 n = normalize(v_Normal);
	vec3 viewDir = normalize(v_ViewPos - v_FragPos);

	vec3 result = CalculateDirLight(n, v_FragPos, viewDir);

	result += CalculatePointLight(n, v_FragPos, viewDir);

	vec4 tex = texture(u_Texture, v_TexCoord);

	FragColor = vec4(result,1) * tex;

}


//functions

vec3 CalculateDirLight(vec3 _n, vec3 _fragPos, vec3 _viewDir)
{

	//these will be moved later
	
	vec3 diffuseColor = vec3(1,1,1);
	vec3 specularColor = vec3(1,1,1);

	vec3 lightDir = normalize(u_DirLight - _fragPos);
	vec3 halfwayDir = normalize(lightDir + _viewDir);

	vec3 ambient = diffuseColor * 0.3;

	float diff = max(dot(_n,lightDir), 0.0);
	vec3 diffuse = diffuseColor * diff;

	float spec = pow(max(dot(_viewDir, halfwayDir), 0.0), 32);
	vec3 specular = spec * specularColor;

	vec3 lighting = ambient + diffuse + specular;

	return lighting;

}

vec3 CalculatePointLight(vec3 _n, vec3 _fragPos, vec3 _viewDir)
{

	//attenuation values - distance = 32
	float constant = 1.0;
	float linear = 0.14;
	float quadratic = 0.07;

	float distance = length(u_PLightPos - _fragPos);
	float att = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

	vec3 lightDir = normalize (u_PLightPos - _fragPos);
	vec3 halfwayDir = normalize(lightDir + _viewDir);

	float diff = max(dot(_n, lightDir), 0.0);
	vec3 diffuse = diff * u_PLightColor;

	float spec = pow(max(dot(_viewDir, halfwayDir), 0.0), 32);
	vec3 specular = spec * u_PLightColor;

	specular *= att;
	diffuse *= att;

	vec3 lighting = specular + diffuse;

	return lighting;

}