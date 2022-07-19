#version 430 core

out vec4 color;

void main(void) {
	color = vec4(sin(gl_FragCoord.x * 0.25) * 0.5 + 0.5, 
				cos(gl_FragCoord.y * 0.25) * 0.5 + 0.5,
				sin(gl_FragCoord.x * 0.15) * cos(gl_FragCoord.y *  0.15), 1.0);
}

// This shader is used to test out how gl_FragCoord can be used to generate a color for a fragment.