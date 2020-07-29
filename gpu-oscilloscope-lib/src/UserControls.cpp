#include "UserControls.h"
#include <cstdio>

void UserControls::keyboard(unsigned char key, int x, int y)
{
	// FIXME
    switch (key)
    {
    case (27):
#if defined(__APPLE__) || defined(MACOSX)
        exit(EXIT_SUCCESS);
#else
        //glfwDestroyWindow(window);
        return;
#endif
    }
}

void UserControls::mouse(int button, int state, int x, int y)
{
	
    // if (state == GLFW_MOUSE_BUTTON_LEFT)
    // {
    //     mouse_buttons |= 1 << button;
    // }
    // else if (state == GLF)
    // {
    //     mouse_buttons = 0;
    // }

    mouse_old_x = x;
    mouse_old_y = y;


	// TODO: Make values match with z depth in gluPerspective
    if ((button == 3) || (button == 4)) // It's a wheel event
    {
    	if(button == 3)
        {
            translate_z = translate_z * 0.9f;
    	}
    	else
    	{
            translate_z = translate_z * 1.1f;
        
    	}
        printf("Translation in z is: %f", translate_z);
    }

}

void UserControls::motion(int x, int y)
{
    float dx, dy;
    dx = (float)(x - mouse_old_x);
    dy = (float)(y - mouse_old_y);

    if (mouse_buttons & 1)
    {
        translate_x -= dx * 0.002f;
        translate_y += dy * 0.002f;
    }
    // else if (mouse_buttons & 4)
    // {
    //     translate_z += dy * 0.01f;
    // }

    mouse_old_x = x;
    mouse_old_y = y;
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