#pragma once
#include "../GLManager.h"
#include <math.h>

#define M_PI           3.14159265358979323846  /* pi */

struct FieldOfView
{
	double maxX;
	double minX;
	double maxY;
	double minY;
};

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

	FieldOfView getFieldOfView()
	{
		// TODO: Cache value and debounce calculation for further performance!

		// TODO: use View Angle here!
		double tanFactor = tan(45 * M_PI / 180);

		Position cp = userControls->getCameraPosition();

		FieldOfView fieldOfView{

		tanFactor * cp.z + cp.x,
		-tanFactor * cp.z + cp.x,
		tanFactor * cp.z + cp.y,
		-tanFactor * cp.z + cp.y

		};

		return fieldOfView;
	}
	
private:
	bool drawCoordinateSystem = true;

	IUserControls* userControls;
};

