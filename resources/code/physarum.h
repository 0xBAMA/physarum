#ifndef PHYSARUM
#define PHYSARUM

#include "includes.h"

class physarum
{
public:

	physarum();
	~physarum();
	
private:

	SDL_Window * window;
	SDL_GLContext GLcontext;
	
	ImVec4 clear_color;
	
	
	float sense_angle;
	float sense_distance;
	// other sim params ... 
	
	GLuint agent_shader;
	GLuint continuum_shader;
	GLuint diffuse_and_decay_shader;
	
	GLuint continuum_vao;
	GLuint continuum_vbo;
	
	GLuint agent_ssbo;
	
	GLuint continuum_textures[2];
			
	void create_window();
	void gl_setup();
	void sim_tick();
	void draw_everything();
	
	
	bool pquit;	 // main loop control variable
	void quit();	
};

#endif
