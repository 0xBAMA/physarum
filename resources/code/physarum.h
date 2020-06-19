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
	
	void create_window();
	void draw_everything();
	
	void quit();
	
	bool pquit;
		
};

#endif
