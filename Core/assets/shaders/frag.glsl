#version 330 core
out vec4 oColor;
in vec3 vColor;

void main() {
    oColor = vec4(vColor, 1.0f);
}