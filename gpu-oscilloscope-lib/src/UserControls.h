#ifndef H_UserControls
#define H_UserControls

#include "headers/IUserControls.h"
#include "GlutManager.h"

class UserControls : public IUserControls
{
	
public:
	UserControls(){};
	
private:
	/**
	 * Mouse Controls
	 */
	int mouse_old_x, mouse_old_y;
	int mouse_buttons = 0;
	float rotate_x = 0.0, rotate_y = 0.0;
	float translate_x = 0.0, translate_y = 0.0, translate_z = -3.0;

public: 
	/*
	 * Callback Functions
	 */	
	void keyboard(unsigned char key, int x, int y) override;
	void mouse(int button, int state, int x, int y) override;
	void motion(int x, int y) override;
	void timerEvent(int value) override;

	float getTranslationInX() override
	{
		return translate_x;
	}

	float getTranslationInY() override
	{
		return translate_y;
	}

	float getTranslationInZ() override
	{
		return translate_z;
	}
	
	float getRotationInX() override
	{
		return rotate_x;
	}

	float getRotationInY() override
	{
		return rotate_y;
	}

	
};

#endif