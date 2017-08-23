[VERTEX]

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;

uniform mat4 uMMatrix;
uniform mat4 uPMatrix;

out vec4 vertex;
out vec3 normal;

void main(void) {
	vertex = uPMatrix * uMMatrix * vec4(aVertexPosition, 1.0);
    gl_Position = vertex;
	normal = aVertexNormal;
}

[FRAGMENT]

layout(location = 0) out vec4 color;

in vec4 vertex;
in vec3 normal;

void main(void) {
	vec3 lightSource = vec3(5, 10, 2);

	vec3 L = normalize(lightSource.xyz);
	vec3 diffuseColor = vec3(1, 1, 1) * (dot(normal, L)*0.5 + 0.5);
	diffuseColor = clamp(diffuseColor, 0.0, 1.0);

	color = vec4(diffuseColor, 1);
}