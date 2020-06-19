#include "physarum.h"
// This contains the very high level expression of what's going on

physarum::physarum()
{
    pquit = false;

    create_window();

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
