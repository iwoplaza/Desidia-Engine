[VERTEX]

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoord;

uniform mat4 uMMatrix;
uniform mat4 uVMatrix;
uniform mat4 uPMatrix;

smooth out vec2 texCoord;
out vec3 vertex;

void main(void) {
	gl_Position = uPMatrix * uVMatrix * uMMatrix * vec4(aVertexPosition, 1.0);
	texCoord = aVertexTexCoord;
	vertex = (uPMatrix * uVMatrix * uMMatrix * vec4(aVertexPosition, 1.0)).xyz;
}

[FRAGMENT]

layout(location = 0) out vec4 color;

uniform sampler2D uDiffuseMap;

smooth in vec2 texCoord;
in vec3 vertex;

void main(void) {
	color = texture2D(uDiffuseMap, texCoord);
}