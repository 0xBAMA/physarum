#version 430 core

uniform layout( r16ui ) uimage2D previous;
uniform layout( r16ui ) uimage2D current;

layout( binding = 0, std430 ) buffer agent_data
{
	vec2 data[];	// [position0, direction0], [position1, direction1], ...
};

void main()
{
	int index = gl_VertexID * 2;
	
	vec2 position = data[index];
	vec2 direction = data[index+1];

	// gl_Position = vec4(position.x, position.y, 0, 1);
	gl_Position = vec4(0,0,0,1);
}
