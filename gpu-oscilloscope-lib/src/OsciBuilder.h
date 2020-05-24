#pragma once

// #include "IComputation.h"
// #include "IUserControls.h"



#include "GlutManager.h"

#include "CudaComputation.h"
#include "UserControls.h"

class OsciBuilder
{
public:
	OsciBuilder() {};

public:

	__declspec(dllexport) void setInputExample();
	__declspec(dllexport) void setInputSource();

	__declspec(dllexport) void setControlsInbuild();
	
	__declspec(dllexport) void setComputationInbuild();
	
	__declspec(dllexport) void initOsci(int argc, char* argv[]);
	
};

