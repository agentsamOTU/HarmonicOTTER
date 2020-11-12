#version 410

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inUV;
layout(location = 2) in vec3 inNormal;

layout(location = 0) out vec3 outPos;
layout(location = 1) out vec3 outUV;
layout(location = 2) out vec3 outNormal;
layout(location = 3) out vec3 outColor;

uniform vec2 offset;
uniform mat4 scale;


void main() {

	gl_Position = scale * vec4(inPosition.x+offset.x,-inPosition.z+offset.y,inPosition.y, 1.0);

	// Lecture 5
	// Pass vertex pos in world space to frag shader
	outPos = gl_Position.xyz;

	// Normals
	outNormal = inNormal;

	///////////
	outColor = vec3(1.0,1.0,1.0);
	outUV = inUV;
}

