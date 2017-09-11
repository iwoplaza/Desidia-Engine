[VERTEX]

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out vec4 vVertex;
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
};

uniform Material uMaterial;
uniform mat3 uMV3x3Matrix;

void main(void) {
	vec3 lightSource = uMV3x3Matrix * vec3(5, 10, 2);
	vec3 L =  vTBNMatrix * normalize(lightSource.xyz);
	vec3 lightColor = vec3(1, 1, 1);
	vec3 normal = vec3(0, 0, 1);
	if (uMaterial.normalMapped) {
		normal = normalize(texture2D(uMaterial.normalMap, vTexCoord).rgb*2.0 - 1.0);
	}
	vec3 E = vTBNMatrix * vec3(0, 0, 1);
	vec3 R = reflect(-L, normal);
	float cosAlpha = clamp( dot(E, R), 0, 1 );
	
	vec3 diffuseColor = lightColor * (dot(normal, L));
	diffuseColor = clamp(diffuseColor, 0.0, 1.0);
	vec3 specularColor = vec3(1, 1, 1) * pow(cosAlpha, 15);
	if (uMaterial.diffuseMapped) {
		vec4 textureColor = texture2D(uMaterial.diffuseMap, vTexCoord)*vec4(diffuseColor, 1.0);
		color = vec4(textureColor.rgb * uMaterial.diffuseColor.rgb + specularColor, 1.0);
	}
	else {
		color = vec4(diffuseColor.rgb * uMaterial.diffuseColor.rgb + specularColor, 1.0);
	}

	//color = vec4(normalize(vTangent)*0.5 + 0.5, 1.0);
}