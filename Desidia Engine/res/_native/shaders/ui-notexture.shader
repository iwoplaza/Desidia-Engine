[VERTEX]

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoord;

out vec4 vertex;
out vec3 normal;
smooth out vec2 texCoord;

uniform mat4 uMMatrix;
uniform mat4 uVMatrix;
uniform mat4 uPMatrix;

void main(void) {
	vertex = uPMatrix * uVMatrix * uMMatrix * vec4(aVertexPosition, 1.0);
	gl_Position = vertex;
	normal = aVertexNormal;
	texCoord = aVertexTexCoord;
}

[FRAGMENT]

layout(location = 0) out vec4 color;

in vec4 vertex;
in vec3 normal;
smooth in vec2 texCoord;

void main(void) {
	color = vec4(0, 0, 0.5, 1);
}