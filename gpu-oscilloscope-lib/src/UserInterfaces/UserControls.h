#ifndef H_UserControls
#define H_UserControls

#include "../Headers/IUserControls.h"
#include <string>

class UserControls : public IUserControls
{
public:
	UserControls() = default;

private:
	/**
	 * Mouse Controls
	 */
	double mouse_old_x = 0, mouse_old_y = 0;
	int active_mouse_buttons = 0;
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

	Position getCameraPosition() override
	{
		return Position{
			translate_x,
			translate_y,
			translate_z
		}.Negate();
	};
};

#endif
