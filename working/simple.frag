#version 460

in vec3 normal; //world space hopefully
in vec2 uvs;

out vec4 FragColour;

uniform vec3 lightDir;
uniform float lightIntensity;
uniform vec4 lightColour;
uniform vec4 ambientColour;
uniform sampler2D albedoMap;

void main()
{
	FragColour = vec4(1);
}