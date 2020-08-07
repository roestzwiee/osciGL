#include "UserControls.h"
#include <cstdio>

// hard coupling to glfw3.h only needed cuz i'm to lazy to define keys by my own
// copy key definitions to get rid of it!
#include <GLFW/glfw3.h>
#include <cstdlib>

void UserControls::keyboard(int key, int scancode, int action, int mods)
{
    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        exit(EXIT_SUCCESS);
    }
}

void UserControls::mouse(int button, int action, int mods)
{
	
    if(action == GLFW_PRESS)
    {
        active_mouse_buttons |= 1 << button;
    	
    } else if (action == GLFW_RELEASE)
    {
        active_mouse_buttons = 0;
    }

}

void UserControls::motion(double x, double y)
{
	if(active_mouse_buttons & 1 << GLFW_MOUSE_BUTTON_LEFT)
	{
		double dx, dy;
	    dx = x - mouse_old_x;
	    dy = y - mouse_old_y;

	    translate_x -= dx * 0.002f;
	    translate_y += dy * 0.002f;
	}

    mouse_old_x = x;
    mouse_old_y = y;
}

void UserControls::scroll(double xOffset, double yOffset)
{
    const double translate_z_new = translate_z + yOffset * 0.2;
	
    if (-0.1 > translate_z_new && translate_z_new > -10)
    {
        translate_z = translate_z_new;
    }
}


void UserControls::timerEvent(int value)
{
	// FIXME!
    // if (glutGetWindow()) 
    // {
    //     glutPostRedisplay();
    //     glutTimerFunc(REFRESH_DELAY, TimerCallback, 0);
    // }
}