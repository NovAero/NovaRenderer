#version 460

in vec3 position;
in vec3 normal;
in vec2 uvs;

out vec4 FragColour;

uniform vec3 cameraPosition;

uniform sampler2D albedoMap;

uniform vec3 lightDir;
uniform float lightIntensity;
uniform vec4 lightColour;
uniform vec4 ambientColour;

uniform vec3 Ka; // ambient material colour
uniform vec3 Kd; // diffuse material colour
uniform vec3 Ks; // specular material colour
uniform float specExponent;

void main()
{
	// ensure normal and light direction are normalised
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);
	
	// calculate lambert term (negate light direction)
	float lambertTerm = max( 0, min( 1, dot( N, -L ) ) );
	
	// calculate view vector and reflection vector
	vec3 V = normalize(cameraPosition - position.xyz);
	vec3 R = reflect( L, N );
	
	// calculate specular term
	float specularTerm = pow( max( 0, dot( R, V ) ), specExponent );
	
	// calculate each colour property
	vec3 ambient = ambientColour.xyz * Ka;
	vec3 diffuse = lightColour.xyz * Kd * lambertTerm;
	vec3 specular = lightColour.xyz * Ks * specularTerm;
	
	vec3 albedo = texture(albedoMap, uvs).rgb;
	
	//Final colour state
	FragColour = vec4( albedo * (ambient + diffuse + specular), 1);
	//FragColour = vec4(specularTerm, 0, 0, 1);
}