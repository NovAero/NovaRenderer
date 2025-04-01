#version 460

in vec3 fragPos;
in vec3 normal;
in vec2 uvs;

out vec4 FragColour;

uniform vec3 viewPos;

uniform sampler2D albedoMap;

struct Material {
    vec3 ambient;
	vec3 diffuse;
	vec3 specular;
    float shininess;
};

struct PointLight
{
	vec3 position;

	vec3 conLinQuad;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct DirLight
{
	vec4 lightVec; //xyz are direction, w is strength

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define NM_PNT_LIGHTS 1

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pntLights[NM_PNT_LIGHTS];

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);  

void main()
{

    vec3 albedo = texture(albedoMap, uvs).rgb;
    vec3 result;

    // properties
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);

    // phase 1: Directional lighting
    //result = CalcDirLight(dirLight, norm, viewDir);
  
    // phase 2: Point lights
    for(int i = 0; i < NM_PNT_LIGHTS; i++) {
        result += CalcPointLight(pntLights[i], norm, fragPos, viewDir);
    }
    
    FragColour = vec4(albedo * result, 1.0);
}



vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.lightVec.xyz);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient;
    vec3 diffuse  = light.diffuse  * diff;
    vec3 specular = light.specular * spec;
    return (ambient + diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.conLinQuad.x + light.conLinQuad.y * distance + 
  			     light.conLinQuad.z * (distance * distance));
    
    // combine results
    vec3 ambient  = light.ambient;
    vec3 diffuse  = light.diffuse  * diff;
    vec3 specular = light.specular * spec;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}