#version 460

layout( location = 0 ) in vec3 position;

uniform vec4 faceColour;
uniform mat4 ProjectionViewModel;

out vec4 colour;

void main() {
      vec4 posVec4 = vec4(position, 1);

      colour = faceColour;

      gl_Position = ProjectionViewModel * posVec4;
}