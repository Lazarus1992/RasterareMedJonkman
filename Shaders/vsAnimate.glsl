#version 430
layout(location=0) in vec3 inPosition;
layout(location=1) in vec2 inTexcoord;
layout(location=2) in vec3 inNormal;
layout(location=3) in vec4 inWeights;
layout(location=4) in ivec4 inJointIndices;
layout(location=5) in vec3 inTangents;
layout(location=6) in vec3 inBinormals;


layout(location=0) out vec2 fTexcoord;
layout(location=1) out vec3 fNormal;
layout(location=2) out vec3 fLight;
layout(location=3) out vec3 fVertexRelativePosition;
layout(location=4) out vec4 fPointLightColour;
layout(location=5) out float fPointLightIntensity;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uNormalsRot;
uniform vec4 uLight;
uniform vec4 uPointLightColour;
uniform float uPointLightIntensity;
uniform mat4 uJointTransforms[21];
uniform mat4 uBindPoseJointTransform[21];
uniform vec4 uPosition;

void main()
{
	vec4 totalLocalPos = vec4(0.0);
	vec4 totalNormal = vec4(0.0);
	
	//Change each vertex's world position depending on weight to joints
	for(int i = 0; i < 4; i++) //Can have up to 4 weights
	{
		int curJointIndex = int(inJointIndices[i]);
		mat4 jointTransform = uJointTransforms[inJointIndices[i]]; //Store transform for current weight
		mat4 bindPoseJointTransform = uBindPoseJointTransform[curJointIndex];

		vec4 vertexPosition = jointTransform * inverse(bindPoseJointTransform) * vec4(inPosition, 1.0) * inWeights[i];
		totalLocalPos += vertexPosition;

		vec4 worldNormal = jointTransform * inverse(bindPoseJointTransform) * vec4(inNormal, 0.0);
		totalNormal += worldNormal * inWeights[i];
	}

	

	mat3 toTangentSpace = mat3 (
		inTangents.x, inBinormals.x, totalNormal.x,
		inTangents.y, inBinormals.y, totalNormal.y,
		inTangents.z, inBinormals.z, totalNormal.z
	);

	//fNormal = (uNormalsRot * totalNormal).xyz;
	fNormal = totalNormal.xyz;
	fLight = uLight.xyz;
	fPointLightColour = uPointLightColour;
	fPointLightIntensity = uPointLightIntensity;
	fVertexRelativePosition = (uView * uModel * totalLocalPos).xyz;
	fVertexRelativePosition = toTangentSpace * fVertexRelativePosition;

	fTexcoord = inTexcoord;
	gl_Position = uProjection * uView * uModel * totalLocalPos;

};