#version 460

layout(location = 0) in vec3 vertPos;

out vec3 fragPos;

uniform mat4 mvpMat;
uniform mat4 modelMat;

void main()
{
	fragPos = vertPos;

	vec4 transformedPos = mvpMat * vec4(vertPos, 1.0);
	gl_Position = transformedPos;
}