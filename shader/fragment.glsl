#version 430 core
out vec4 FragColor;

uniform vec4 customColor;

void main() {
    FragColor = customColor;
}
