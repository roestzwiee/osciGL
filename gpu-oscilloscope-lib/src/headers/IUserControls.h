#ifndef H_IUserInput
#define H_IUserInput
#pragma once

struct Position
{
	double x, y, z;

	Position Negate () const
	{
		return Position{ -x, -y, -z };
	}
};

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

	virtual Position getCameraPosition() = 0;
	
};

#endif
