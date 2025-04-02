#version 460

in vec3 fragPos;

out vec4 FragColour;

void main()
{
    FragColour = vec4(fragPos * 0.5, 1.0);
}
