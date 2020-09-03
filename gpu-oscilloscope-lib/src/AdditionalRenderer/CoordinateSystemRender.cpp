#include "CoordinateSystemRender.h"

void CoordinateSystemRender::render()
{
	glScalef(1.0, 1.0, 1.0);
	drawCoordinates();

	drawGrid();

	glFlush();
}

void CoordinateSystemRender::drawCoordinates()
{
	// draw some lines
	glColor3f(1.0, 0.0, 0.0); // red x
	glBegin(GL_LINES);
	// x aix

	glVertex3f(-4.0, 0.0f, 0.0f);
	glVertex3f(4.0, 0.0f, 0.0f);

	glVertex3f(4.0, 0.0f, 0.0f);
	glVertex3f(3.8, 0.1f, 0.0f);

	glVertex3f(4.0, 0.0f, 0.0f);
	glVertex3f(3.8, -0.1f, 0.0f);
	glEnd();
}

void CoordinateSystemRender::drawGrid() const
{
	glPushAttrib(GL_ENABLE_BIT);
	glColor3f(0.95f, 0.95f, 0.95f);
	glLineStipple(1, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);

	const FieldOfView fov = settings->getFieldOfView();
	
	const double smallestX = fov.minX - 1.5;
	const double biggestX = fov.maxX + 1;
	const double smallestY = fov.minY - 1.5;
	const double biggestY = fov.maxY + 1;

	for (double i = ceil(smallestX); i <= ceil(biggestX); i+= 0.5)
	{
		glVertex3f(i, smallestY, 0.0f);
		glVertex3f(i, biggestY, 0.0f);
	}

	for (double i = ceil(smallestY); i <= ceil(biggestY); i+= 0.5)
	{
		glVertex3f(smallestX, i, 0.0f);
		glVertex3f(biggestX, i, 0.0f);
	}

	glEnd();
	glPopAttrib();
}
