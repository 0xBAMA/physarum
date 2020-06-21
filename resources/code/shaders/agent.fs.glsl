#version 430 core

layout( binding = 1, r32ui ) uniform uimage2D current;

in vec2 v_pos;
out vec4 fragment_output;

void main()
{
	imageAtomicAdd(current, ivec2(imageSize(current)*(0.5*(v_pos+vec2(1)))), 1);
	fragment_output = smoothstep(vec4(1,0,0,1), vec4(0,0,0,0), vec4(2*distance(gl_PointCoord, vec2(0.5,0.5))));	
}
