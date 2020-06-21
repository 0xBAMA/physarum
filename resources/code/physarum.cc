#include "physarum.h"
#include "debug.h"
// This contains the very high level expression of what's going on

physarum::physarum()
{
    pquit = false;

    create_window();
    gl_debug_enable();
    gl_setup();

    while(!pquit)
    {
        sim_tick();
        draw_everything();
    }
}

physarum::~physarum()
{
    quit();
}
