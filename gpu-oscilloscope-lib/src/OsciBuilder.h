#pragma once

#include "Headers/ICudaInput.h"
// #include "IUserControls.h"



#include "GLManager.h"

#include "Examples/ExampleInput.h"
#include "UserInterfaces/UserControls.h"

class __declspec(dllexport) OsciBuilder
{
public:
	OsciBuilder() {};

public:

	void setInputExample();
	 void setInputSource();

	void setControlsInbuild();
	
	void setComputationInbuild();
	void setComputation(ICudaInput* computation);
	
	void initOsci(int argc, char* argv[]);

private:
	GLManager glManager;
	
};

