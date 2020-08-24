#ifndef H_IUserInput
#define H_IUserInput
#pragma once

class IUserControls
{
public:

	/*
	 * Callback Functions
	 */
	virtual void keyboard(int key, int scanCode, int action, int mods) = 0;
	virtual void mouse(int button, int action, int mods) = 0;
	virtual void scroll(double xOffset, double yOffset) = 0;
	virtual void motion(double x, double y) = 0;
	virtual void timerEvent(int value) = 0;

	virtual double getTranslationInX() = 0;
	virtual double getTranslationInY() = 0;
	virtual double getTranslationInZ() = 0;


	virtual double getRotationInX() = 0;
	virtual double getRotationInY() = 0;
};

#endif
