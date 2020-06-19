#version 430 core

out vec4 fragment_output;

void main()
{
	fragment_output = smoothstep(vec4(1,0,0,1), vec4(0,0,0,0), vec4(2*distance(gl_PointCoord, vec2(0.5,0.5))));	
}
