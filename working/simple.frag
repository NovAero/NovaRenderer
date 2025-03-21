#version 460

in vec3 normal; //world space hopefully
in vec2 uvs;

out vec4 PixelColour;

uniform vec3 lightDir;
uniform sampler2D albedoMap;

void main()
{
	vec3 sunDirection = normalize(lightDir);
	vec3 albedo = texture(albedoMap, uvs).rgb;
	
	float illumination = dot(-sunDirection, normalize(normal));
	
	PixelColour = vec4(albedo, 1.0);
    //PixelColour = vec4(uvs.x, uvs.y, 0,1);
}