#version 460

in vec3 fragPos;
in vec3 normal;
in vec2 uvs;

out vec4 FragColour;

uniform sampler2D albedoMap;

struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct DirLight
{
	vec4 lightVec; //xyz are direction, w is strength;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
}

uniform int numPntLights;

uniform DirLight dirLight;
uniform PointLight pntLights[numPntLights];

void main()
{
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(viewPos - fragPos);

	vec3 result = CalcDirLights
}