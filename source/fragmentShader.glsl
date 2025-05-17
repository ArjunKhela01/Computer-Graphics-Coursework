#version 330 core

in vec2 UV;
out vec3 fragmentColour;

uniform sampler2D diffuseMap;

void main()
{
    fragmentColour = texture(diffuseMap, UV).rgb;
}
