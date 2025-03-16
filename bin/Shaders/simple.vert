#version 460

layout( location = 0 ) in vec4 Position;

uniform vec4 faceColour;
uniform mat4 ProjectionViewModel;

out vec4 colour;

void main() {
      colour = faceColour * Position + 0.5;
      gl_Position = ProjectionViewModel * Position;
}