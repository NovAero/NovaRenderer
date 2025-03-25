#version 460

in vec3 position;
in vec3 normal;
in vec2 uvs;

out vec4 FragColour;

uniform sampler2D albedoMap;

layout (std140, binding = 0) uniform Lights
{
	vec3 lightVec;
	vec4 colour;

} lights[4];

	uniform vec4 ambientColour;
	uniform int numLights;

vec3 CalculateLighting(vec3 fragPos, vec3 normal)
{
	vec3 diffuse = vec3(0.0);

    for (int i = 0; i < numLights && i < 4; i++)
    {
        vec3 lightDir = normalize(lights[i].lightVec);
		float diff = max(0.0, dot(normal, lightDir));
		
		diffuse += lightDir * (diff * lights[i].lightVec);
    }

    return diffuse;
}

void main()
{
	if(gl_FrontFacing){
		vec3 albedo = texture(albedoMap, uvs).rgb;
		vec3 norm = normalize(normal);

		vec3 diffuse = lights[0].lightVec; //CalculateLighting(position, norm);
		vec3 ambient = ambientColour.xyz;
	
		FragColour = vec4(albedo * diffuse, 1.0);
	}
}