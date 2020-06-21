#version 430 core

in vec2 v_pos;

out vec4 fragment_output;

// uniform layout( r16ui ) uimage2D previous;
// uniform layout( r16ui ) uimage2D current;

layout( binding = 1, r32ui ) uniform uimage2D current;

void main()
{
	uint s = imageLoad(current, ivec2(imageSize(current)*(0.5*(v_pos+vec2(1))))).r;
	
	fragment_output = vec4(0.0001*s,0.00006*s,0,1);
}
