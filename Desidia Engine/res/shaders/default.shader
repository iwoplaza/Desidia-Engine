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

uniform sampler2D uDiffuseMap;

void main(void) {
	vec3 lightSource = vec3(5, 10, 2);

	vec3 L = normalize(lightSource.xyz);
	vec3 diffuseColor = vec3(1, 1, 1) * (dot(normal, L)*0.5 + 0.5);
	diffuseColor = clamp(diffuseColor, 0.0, 1.0);

	vec4 textureColor = texture2D(uDiffuseMap, texCoord)*vec4(diffuseColor, 1.0);
	if (textureColor.a <= 0.1) {
		color = vec4(textureColor.rgb, 0.5);
	}
	else if (textureColor.a <= 0.5) {
		//Body
		color = vec4(textureColor.rgb, 1);
	}
	else if (textureColor.a <= 0.8) {
		color = vec4(texture2D(uDiffuseMap, texCoord).rgb, 1);
	}
	else {
		color = vec4(textureColor.rgb, 1);
	}
}