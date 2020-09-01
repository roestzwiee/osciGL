#pragma once
#include "../GLManager.h"
#include <math.h>

#define M_PI           3.14159265358979323846  /* pi */

class CoordinateSystemRenderSettings
{
public:
	CoordinateSystemRenderSettings(IUserControls* userControls)
	{
		this->userControls = userControls;
	}
	
	/*
	 * Settings getters
	 */
	bool getDrawCoordinateSystem() const
	{
		return drawCoordinateSystem;
	}

	/*
	 * Settings setters
	 */
	void setDrawCoordinateSystem(bool drawCoordinateSystem)
	{
		this->drawCoordinateSystem = drawCoordinateSystem;
	}

	double getBiggestDisplayedX()
	{
		return -tan(45 * M_PI / 180) * userControls->getTranslationInZ() - userControls->getTranslationInX();
	}

	double getSmallestDisplayedX()
	{
		return tan(45 * M_PI / 180) * userControls->getTranslationInZ() - userControls->getTranslationInX();
	}

	double getBiggestDisplayedY()
	{
		return -tan(45 * M_PI / 180) * userControls->getTranslationInZ() - userControls->getTranslationInY();
	}

	double getSmallestDisplayedY()
	{
		return tan(45 * M_PI / 180) * userControls->getTranslationInZ() - userControls->getTranslationInY();
	}

private:
	bool drawCoordinateSystem = true;

	IUserControls* userControls;
};

