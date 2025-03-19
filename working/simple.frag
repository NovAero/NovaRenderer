#version 460

in vec3 normal; //world space hopefully
in vec2 uvs;

out vec4 PixelColour;

uniform sampler2D albedoMap;

void main()
{
	vec3 sunDirection = normalize(vec3(-0.3, -0.1, 0.2));
	
	vec3 albedo = texture(albedoMap, uvs).rgb;
	
	PixelColour = vec4(normal * 0.5 + 0.5, 1.0);
	//float illumination = dot(-sunDirection, normalize(normal));
	
	PixelColour = vec4(albedo, 1.0);
	//PixelColour = vec4(uvs, 0.0, 1.0);
}