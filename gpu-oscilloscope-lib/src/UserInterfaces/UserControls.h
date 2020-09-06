#ifndef H_UserControls
#define H_UserControls

#include "Output/IInfoOutput.h"
#include "../Headers/IUserControls.h"

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
	Position cameraPosition;

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
		cameraPosition = Position{
			translate_x,
			translate_y,
			translate_z
		}.Negate();

		return cameraPosition;
	}

	list<InfoData> getInfoData() override
	{
		auto infoList = list<InfoData>();

		infoList.push_back(InfoData{ "translationX", std::to_string(cameraPosition.x) });
		infoList.push_back(InfoData{ "translationY", std::to_string(cameraPosition.y) });
		infoList.push_back(InfoData{ "translationZ", std::to_string(cameraPosition.z) });

		return infoList;
	};
};

#endif
