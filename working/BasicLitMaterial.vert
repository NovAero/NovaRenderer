#version 460

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec2 vertUVs;
layout(location = 2) in vec3 vertNormal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

uniform mat4 mvpMat;
uniform mat4 modelMat;

out vec3 fragPos;
out vec3 normal;
out vec2 uvs;
out vec3 vTangent;
out vec3 vBiTangent;

void main()
{
	fragPos = (modelMat * vec4(vertPos, 1.0)).xyz;
	uvs = vertUVs;
	normal = (modelMat * vec4(vertNormal, 0.0)).xyz;
	vTangent = (modelMat * vec4(tangent, 0)).xyz;
	vBiTangent = (modelMat * vec4(bitangent, 0)).xyz;

	vec4 transformedPos = mvpMat * vec4(vertPos, 1.0);
	gl_Position = transformedPos;
}