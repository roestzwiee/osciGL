#ifndef H_SounidRuntime
#define H_SounidRuntime

#include <helper_gl.h>
#include <GL/freeglut.h>

#pragma once
class UserInput
{
	
public:
	UserInput(){};
	
public:
	/**
	 * Mouse Controls
	 */
	int mouse_old_x, mouse_old_y;
	int mouse_buttons = 0;
	float rotate_x = 0.0, rotate_y = 0.0;
	float translate_z = -3.0;

	/*
	 * Callback Functions
	 */	
	void keyboard(unsigned char key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void motion(int x, int y);
	void timerEvent(int value);
	
};

#endif