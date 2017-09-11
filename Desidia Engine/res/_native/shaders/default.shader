[VERTEX]

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out vec4 vVertex;
out vec3 vNormal;
smooth out vec2 vTexCoord;
out vec3 vTangent;
out vec3 vBitangent;

uniform mat4 uMMatrix;
uniform mat4 uVMatrix;
uniform mat4 uPMatrix;
uniform mat4 uNMatrix;

void main(void) {
	vVertex = uPMatrix * uVMatrix * uMMatrix * vec4(aPosition, 1.0);
	gl_Position = vVertex;
	vNormal = aNormal;
	vTexCoord = aTexCoord;
	vTangent = aTangent;
	vBitangent = aBitangent;
}

[FRAGMENT]

layout(location = 0) out vec4 color;

in vec4 vVertex;
in vec3 vNormal;
smooth in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBitangent;

struct Material {
	bool diffuseTextured;
	sampler2D diffuseMap;
	vec4 diffuseColor;
};

uniform Material uMaterial;

void main(void) {
	vec3 lightSource = vec3(5, 10, 2);

	vec3 L = normalize(lightSource.xyz);
	vec3 diffuseColor = vec3(1, 1, 1) * (dot(vNormal, L)*0.5 + 0.5);
	diffuseColor = clamp(diffuseColor, 0.0, 1.0);

	if (uMaterial.diffuseTextured) {
		vec4 textureColor = texture2D(uMaterial.diffuseMap, vTexCoord)*vec4(diffuseColor, 1.0);
		color = textureColor * uMaterial.diffuseColor;
	} else {
		color = vec4(diffuseColor, 1)  * uMaterial.diffuseColor;
	}
}