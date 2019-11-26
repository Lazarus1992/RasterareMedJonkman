#version 430
layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexcoord;
layout(location=2) in vec3 inNormal;

layout(location=0) out vec2 fTexcoord;
layout(location=1) out vec3 fNormal;
layout(location=2) out vec3 fLight;
layout(location=3) out vec3 fVertexRelativePosition;
layout(location=4) out vec4 fPointLightColour;
layout(location=5) out float fPointLightIntensity;

uniform mat4 uMVP;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uNormalsRot;
uniform vec4 uLight;
uniform vec4 uPointLightColour;
uniform float uPointLightIntensity;
void main()
{
	fNormal = (uNormalsRot * vec4(inNormal, 1.0)).xyz;
	fTexcoord = inTexcoord;
	fLight = uLight.xyz;
	fPointLightColour = uPointLightColour;
	fPointLightIntensity = uPointLightIntensity;
	fVertexRelativePosition = (uView * uModel * vec4(inPosition, 1.0)).xyz;

	gl_Position = uMVP * vec4(inPosition, 1.0);
};