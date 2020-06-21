#version 430 core

// uniform layout( r16ui ) uimage2D previous;
layout( binding = 1, r32ui ) uniform uimage2D current;

layout( binding = 0, std430 ) buffer agent_data
{
	vec2 data[];	// [position0, direction0], [position1, direction1], ...
};

float amt = 0.001;
out vec2 v_pos;

//takes argument in radians
vec2 rotate(vec2 v, float a) 
{
	float s = sin(a);
	float c = cos(a);
	mat2 m = mat2(c, -s, s, c);
	return m * v;
}

void main()
{
	int index = gl_VertexID * 2;
	
	vec2 position = data[index];
	vec2 direction = data[index+1];
	
	// do the simulation logic to update the value of position
	
		// take your samples
		// make a decision on whether to turn left, right, go straight, or a random direction
	
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
	

	v_pos = new_position;
	
	gl_Position = vec4(new_position.x, new_position.y, 0, 1);
}
