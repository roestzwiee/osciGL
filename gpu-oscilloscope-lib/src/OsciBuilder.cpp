#include "OsciBuilder.h"


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
	setControls(new UserControls);
}

void OsciBuilder::initOsci(int argc, char* argv[])
{
	// TODO: Check if all requirements are met...
	initialize(argc, argv);
}

