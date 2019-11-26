#version 430
layout(location=0) in vec2 fTexcoord;
layout(location=1) in vec3 fNormal;
layout(location=2) in vec3 fLight;
layout(location=3) in vec3 fVertexPosition;
layout(location=4) in vec4 fPointLightColour;
layout(location=5) in float fPointLightIntensity;

out vec4 outColor;

uniform sampler2D texSampler;

void main()
{
	vec3 N = normalize(fNormal);
	vec3 L = normalize((fLight-fVertexPosition));

	vec3 E = normalize(-fVertexPosition);
	vec3 H = normalize(L + E);


	//Specular + diffuse code
	float diffuse_intensity = max(dot(N, L), 0.0);
	vec4 diffuse_final = diffuse_intensity * fPointLightColour;

	float spec_intensity = pow(max(dot(N, H), 0.0), 300);
	vec4 spec_final = spec_intensity * vec4(0.1, 0.1, 0.1, 1.0) * fPointLightIntensity;

	outColor = diffuse_final + spec_final;
	//outColor = vec4(1.0, 0.1, 0.1, 1.0);
};