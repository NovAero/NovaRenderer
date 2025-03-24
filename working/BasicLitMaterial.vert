#version 460

layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec2 vertUVs;
layout(location = 2) in vec3 vertNormal;

uniform mat4 mvpMat;
uniform mat4 modelMat;

out vec3 position;
out vec3 normal;
out vec2 uvs;

void main()
{
	uvs = vertUVs;
	normal = (modelMat * vec4(vertNormal, 0.0)).xyz;
	vec4 transformedPos = mvpMat * vec4(vertPos, 1.0);
	position = transformedPos.xyz;
	gl_Position = transformedPos;
}