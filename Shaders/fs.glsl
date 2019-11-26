#version 430
layout(location=0) in vec2 fTexcoord;
layout(location=1) in vec3 fNormal;
layout(location=2) in vec3 fLight;
layout(location=3) in vec3 fVertexRelativePosition;
layout(location=4) in vec4 fPointLightColour;
layout(location=5) in float fPointLightIntensity;

out vec4 outColor;

uniform sampler2D texSampler;

void main()
{
	vec3 N = normalize(fNormal);
	vec3 L = normalize((fLight-fVertexRelativePosition));

	vec3 E = normalize(-fVertexRelativePosition);
	vec3 H = normalize(L + E);


	//Specular + diffuse code
	float diffuse_intensity = max(dot(N, L), 0.0);
	vec4 diffuse_final = diffuse_intensity * fPointLightColour;

	float spec_intensity = pow(max(dot(N, H), 0.0), 30);
	vec4 spec_final = spec_intensity * vec4(0.1, 0.1, 0.1, 1.0) * fPointLightIntensity;

	//outColor = vec4(0.6f, 0.3f, 0.0f, 1.0f);
	outColor = diffuse_final + spec_final;
	//outColor = texture(texSampler, fTexcoord);
	//float gamma = 2.2;
	//outColor = pow(texture(texSampler, fTexcoord), vec4(vec3(gamma), 1.0));
};