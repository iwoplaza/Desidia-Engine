[VERTEX]

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;

uniform mat4 uMMatrix;
uniform mat4 uPMatrix;

out vec3 normal;

void main(void) {
    gl_Position = uPMatrix * uMMatrix * vec4(aVertexPosition, 1.0);
	normal = aVertexNormal;
}

[FRAGMENT]

layout(location = 0) out vec4 color;

in vec3 normal;

void main(void) {
	color = vec4(normal.xyz, 0);
}