#include "OsciBuilder.h"
// #include "CudaComputation.h"
// #include "UserInput.h"


void OsciBuilder::setInputExample()
{
	
}


void OsciBuilder::setInputSource()
{

}

void OsciBuilder::setComputationInbuild()
{
	setComputationCore(new CudaComputation);
}

void OsciBuilder::setControlsInbuild()
{
	setControls(new UserInput);
}

void OsciBuilder::initOsci(int argc, char* argv[])
{
	// TODO: Check if all requirements are met...
	initialize(argc, argv);
}

