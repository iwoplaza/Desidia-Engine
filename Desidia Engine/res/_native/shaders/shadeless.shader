[VERTEX]

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

smooth out vec2 vTexCoord;

uniform mat4 uMMatrix;
uniform mat4 uVMatrix;
uniform mat4 uPMatrix;
uniform mat4 uMVPMatrix;
uniform mat3 uMV3x3Matrix;

void main(void) {
	vTexCoord = aTexCoord;
	gl_Position = uMVPMatrix * vec4(aPosition, 1.0);
}

[FRAGMENT]

layout(location = 0) out vec4 color;

smooth in vec2 vTexCoord;

struct Material {
	bool diffuseMapped;
	bool normalMapped;
	sampler2D diffuseMap;
	sampler2D normalMap;
	vec4 diffuseColor;
	int shininess;
};

uniform Material uMaterial;
uniform mat3 uMV3x3Matrix;

void main(void) {
	if (uMaterial.diffuseMapped) {
		vec4 textureColor = texture2D(uMaterial.diffuseMap, vTexCoord);
		color = vec4(textureColor.rgb * uMaterial.diffuseColor.rgb, 1.0);
	}
	else {
		color = vec4(uMaterial.diffuseColor.rgb, 1);
	}
}