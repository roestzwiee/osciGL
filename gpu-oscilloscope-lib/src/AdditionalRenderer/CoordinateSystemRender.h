#pragma once
#include "GLManager.h"
#include "CoordinateSystemRenderSettings.h"

class CoordinateSystemRender
{
public:
	CoordinateSystemRender(CoordinateSystemRenderSettings* settings)
	{
		this->settings = settings;
	}

	void render();
	void drawCoordinates();
	void drawGrid() const;

	
private:
	CoordinateSystemRenderSettings* settings;
};

