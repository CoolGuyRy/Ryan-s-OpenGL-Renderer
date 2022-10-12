#version 430 core

layout (vertices = 3) out;

void main(void) {
	if (gl_InvocationID == 0) {
		gl_TessLevelInner[0] = 5.0;
		gl_TessLevelOuter[0] = 5.0;
		gl_TessLevelOuter[1] = 5.0;
		gl_TessLevelOuter[2] = 5.0;
	}
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}

// This shader is used to test the tessellation control shader.
// Not entirely sure how this works yet but it is just for exposure to the tessellation control shader.