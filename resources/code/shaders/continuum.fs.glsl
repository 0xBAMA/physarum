#version 430 core

in vec4 v_color;
out vec4 fragment_output;

void main()
{
	fragment_output = v_color;
}
