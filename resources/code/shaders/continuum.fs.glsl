#version 430 core

in vec2 v_pos;

out vec4 fragment_output;

uniform layout( r16ui ) uimage2D previous;
uniform layout( r16ui ) uimage2D current;

void main()
{
	// fragment_output = vec4(v_pos.xy,0,1.0);
	fragment_output = vec4(0,0,0,1);
}
