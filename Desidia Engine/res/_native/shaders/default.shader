[VERTEX]

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out vec4 vVertex;
out vec3 vPosition;
smooth out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vTangent;
out vec3 vBitangent;
out mat3 vTBNMatrix;

uniform mat4 uMMatrix;
uniform mat4 uVMatrix;
uniform mat4 uPMatrix;
uniform mat4 uMVPMatrix;
uniform mat3 uMV3x3Matrix;

void main(void) {
	vPosition = (uMMatrix * uVMatrix * vec4(aPosition, 1.0)).xyz;
	vVertex = uMVPMatrix * vec4(aPosition, 1.0);
	vTexCoord = aTexCoord;
	vNormal = normalize(uMV3x3Matrix * normalize(aNormal));
	vTangent = (uMV3x3Matrix * normalize(aTangent));
	vBitangent = (uMV3x3Matrix * normalize(aBitangent));
	vTBNMatrix = transpose(mat3(vTangent, vBitangent, vNormal));

	gl_Position = vVertex;
}

[FRAGMENT]

layout(location = 0) out vec4 color;

in vec4 vVertex;
in vec3 vPosition;
smooth in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vTangent;
in vec3 vBitangent;
in mat3 vTBNMatrix;

struct Material {
	bool diffuseMapped;
	bool normalMapped;
	sampler2D diffuseMap;
	sampler2D normalMap;
	vec4 diffuseColor;
	int shininess;
};
uniform Material uMaterial;

const int MAX_LIGHTS = 10;
struct LightSource {
	vec3 location;
	vec4 color;
};
uniform LightSource uLightSources[MAX_LIGHTS];
uniform int uLightCount;

uniform mat3 uMV3x3Matrix;

vec3 getLightDiffuseColor(int idx, vec3 normal, vec3 L, float att) {
	vec3 diffuseColor = uLightSources[idx].color.rgb * ((dot(normal, L)));
	return diffuseColor * att * att;
}

/*
*	L - light's direction
*/
vec3 getLightSpecularColor(int idx, vec3 normal, vec3 L, vec3 E) {
	vec3 R = reflect(-L, normal);
	float cosAlpha = clamp(dot(E, R), 0, 1);
	vec3 specularColor = uLightSources[idx].color.rgb * pow(cosAlpha, uMaterial.shininess) * uMaterial.shininess * 0.1;
	return specularColor;
}

void main(void) {
	vec3 diffuseColor = vec3(0, 0, 0);
	vec3 specularColor = vec3(0, 0, 0);

	for (int i = 0; i < 1; ++i) {
		vec3 lightSource = uLightSources[i].location - vPosition;
		float att = 1-clamp(length(lightSource) * 0.05, 0.0, 1.0);
		vec3 L = normalize(lightSource.xyz);
		vec3 E = vec3(0, 0, 1);
		vec3 normal = vNormal;

		if (uMaterial.normalMapped) {
			normal = normalize(texture2D(uMaterial.normalMap, vTexCoord).rgb*2.0 - 1.0);
			L = vTBNMatrix * L;
			E = vTBNMatrix * E;
		}

		diffuseColor += getLightDiffuseColor(i, normal, L, att);
		specularColor += getLightSpecularColor(i, normal, L, E);
	}

	diffuseColor = clamp(diffuseColor, 0.0, 1.0);
	if (uMaterial.diffuseMapped) {
		vec4 textureColor = texture2D(uMaterial.diffuseMap, vTexCoord) * vec4(diffuseColor, 1.0);
		color = vec4(textureColor.rgb * diffuseColor.rgb * uMaterial.diffuseColor.rgb + specularColor, 1.0);
	}
	else {
		color = vec4(diffuseColor.rgb * uMaterial.diffuseColor.rgb + specularColor, 1.0);
	}

	//color = vec4(normalize(vTangent)*0.5 + 0.5, 1.0);
}