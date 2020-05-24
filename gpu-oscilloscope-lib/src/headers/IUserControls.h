#ifndef H_IUserInput
#define H_IUserInput
#pragma once
class IUserControls
{

public:
	
	/*
	 * Callback Functions
	 */
	virtual void keyboard(unsigned char key, int x, int y) = 0;
	virtual void mouse(int button, int state, int x, int y) = 0;
	virtual void motion(int x, int y) = 0;
	virtual void timerEvent(int value) = 0;

	virtual float getTranslationInZ() = 0;

	virtual float getRotationInX() = 0;

	virtual float getRotationInY() = 0;


};

#endif