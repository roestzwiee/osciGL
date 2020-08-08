#ifndef H_UserControls
#define H_UserControls

#include "headers/IUserControls.h"

class UserControls : public IUserControls
{
public:
	UserControls()
	{
	};

private:
	/**
	 * Mouse Controls
	 */
	double mouse_old_x = 0, mouse_old_y = 0;
	int active_mouse_buttons = 0;
	double rotate_x = 0.0, rotate_y = 0.0;
	double translate_x = 0.0, translate_y = 0.0, translate_z = -3.0;

public:
	/*
	 * Callback Functions
	 */
	void keyboard(int key, int scanCode, int action, int mods) override;
	void mouse(int button, int action, int mods) override;
	void motion(double x, double y) override;
	void scroll(double xOffset, double yOffset) override;
	void timerEvent(int value) override;

	double getTranslationInX() override
	{
		return translate_x;
	}

	double getTranslationInY() override
	{
		return translate_y;
	}

	double getTranslationInZ() override
	{
		return translate_z;
	}

	double getRotationInX() override
	{
		return rotate_x;
	}

	double getRotationInY() override
	{
		return rotate_y;
	}
};

#endif
