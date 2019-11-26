#version 430
layout(location=0) in vec2 fTexcoord;
layout(location=1) in vec3 fNormal;
layout(location=2) in vec3 fLight;
layout(location=3) in vec3 fVertexRelativePosition;
layout(location=4) in vec4 fPointLightColour;
layout(location=5) in float fPointLightIntensity;
layout(location=6) in vec4 fDebugColor;

out vec4 outColor;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform sampler2D normalMap;

void main()
{
	vec4 normalMapValue = 2.0 * texture(normalMap, fTexcoord, -1) -1.0;

	//vec3 N = normalize(fNormal);  //N == normal
	vec3 N = normalize(normalMapValue.rgb);  //N == normal
	vec3 L = normalize((fLight-fVertexRelativePosition)); //L == pixelToLight

	vec3 E = normalize(-fVertexRelativePosition); //E == pixelToCamera
	vec3 H = normalize(L + E); //H == halfvector

	float diffuse_intensity = max(dot(N, L), 0.0);
	vec4 diffuse_final = diffuse_intensity * texture(diffuseMap, fTexcoord);
	//vec4 diffuse_final = diffuse_intensity * vec4(0.6, 0.0, 0.0, 1.0);

	float spec_intensity = pow(max(dot(N, H), 0.0), 150);
	vec4 spec_final = spec_intensity * texture(specularMap, fTexcoord) * fPointLightIntensity;
	//vec4 spec_final = spec_intensity * vec4(0.5, 0.5, 0.5, 1.0) * fPointLightIntensity;

	outColor = diffuse_final + spec_final;
	//outColor = texture(diffuseMap, fTexcoord);
	//outColor = texture(specularMap, fTexcoord);
	//outColor = texture(normalMap, fTexcoord);
};