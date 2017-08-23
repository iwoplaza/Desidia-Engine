[VERTEX]

layout(location = 0) in vec3 aVertexPosition;

void main(void) {
    gl_Position = vec4(aVertexPosition, 1.0);
}

[FRAGMENT]

layout(location = 0) out vec4 color;

void main(void) {
	color = vec4(0, 1, 1, 0);
}