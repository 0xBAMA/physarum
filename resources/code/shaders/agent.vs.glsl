#version 430 core

uniform layout( r16ui ) uimage2D previous;
uniform layout( r16ui ) uimage2D current;

layout( binding = 0, std430 ) buffer agent_data
{
	vec2 data[];	// [position0, direction0], [position1, direction1], ...
};

float amt = 0.01;

void main()
{
	int index = gl_VertexID * 2;
	
	vec2 position = data[index];
	vec2 direction = data[index+1];
	
	// do the simulation logic to update the value of position
	vec2 new_position = (position + amt * direction);
	
	if(new_position.x > 1.0)
		new_position.x = -1.0;
		
	if(new_position.x < -1.0)
		new_position.x = 1.0;
		
	if(new_position.y > 1.0)
		new_position.y = -1.0;
		
	if(new_position.y < -1.0)
		new_position.y = 1.0;
	
	data[index] = new_position;
	
	
	


	gl_Position = vec4(position.x, position.y, 0, 1);
}
