#pragma once
#include "../Headers/IUserControls.h"
#include "../UserInterfaces/Output/IInfoOutput.h"

#include <math.h>

#define M_PI           3.14159265358979323846  /* pi */

struct FieldOfView
{
	double maxX, minX, maxY, minY;
};

class CoordinateSystemRenderSettings : public IInfoOutput
{
public:
	CoordinateSystemRenderSettings(IUserControls* userControls)
	{
		this->userControls = userControls;

		// // TODO: improve caching and initialization
		getFieldOfView();
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
		// TODO: Cache value and de-bounce calculation for further performance!

		// TODO: use View Angle here!
		double tanFactor = tan(45 * M_PI / 180);

		Position cp = userControls->getCameraPosition();

		fieldOfView = FieldOfView {

		tanFactor * cp.z / 2.0 + cp.x,
		-tanFactor * cp.z / 2.0 + cp.x,
		tanFactor * cp.z / 2.0 + cp.y,
		-tanFactor * cp.z / 2.0 + cp.y

		};

		return fieldOfView;
	}

	list<InfoData> getInfoData() override
	{
		auto infoList = list<InfoData>();
	
		infoList.push_back(InfoData{ "maxX", std::to_string(fieldOfView.maxX) });
		infoList.push_back(InfoData{ "minX", std::to_string(fieldOfView.minX) });
		infoList.push_back(InfoData{ "maxY", std::to_string(fieldOfView.maxY) });
		infoList.push_back(InfoData{ "minY", std::to_string(fieldOfView.minX) });
	
		return infoList;
	};
	
private:
	bool drawCoordinateSystem = true;

	FieldOfView fieldOfView;

	IUserControls* userControls;
};

