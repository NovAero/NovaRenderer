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
	if(gl_FrontFacing){
		vec3 norm = normalize(normal);
		vec3 light = normalize(lightDir);

		float lambertTerm = max( 0, min( 1, dot( norm, -light ) ) );

		vec3 albedo = texture(albedoMap, uvs).rgb;

		vec3 diffuse = lightColour.xyz * lightIntensity * lambertTerm;
		vec3 ambient = ambientColour.xyz;
	
		FragColour = vec4(albedo * (diffuse + ambient), 1.0);
	}
}