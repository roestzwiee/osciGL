#pragma once

#include "GlutManager.h"

class oScopeID
{
public:
	oScopeID() {};

public:

	__declspec(dllexport) void initScope(int argc, char* argv[]);
	__declspec(dllexport) void initEmpyt();
	
	
};

