#pragma once

#include "../gpu-oscilloscope-lib/src/Headers/IUserControls.h"
#include "gmock/gmock.h"


class MockUserControls : public IUserControls
{
public:
	MOCK_METHOD4(keyboard, void (int, int, int, int));
	MOCK_METHOD3(mouse, void (int, int, int));
	MOCK_METHOD2(scroll, void (double, double));
	MOCK_METHOD2(motion, void (double, double));
	MOCK_METHOD1(timerEvent, void (int));
	MOCK_METHOD0(getCameraPosition, Position ());

};
