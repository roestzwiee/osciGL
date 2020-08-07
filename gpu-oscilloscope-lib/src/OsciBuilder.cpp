#include "OsciBuilder.h"


void OsciBuilder::setInputExample()
{
	
}


void OsciBuilder::setInputSource()
{

}

void OsciBuilder::setComputationInbuild()
{
	glManager.setComputationCore(new CudaComputation);
}

void OsciBuilder::setComputation(IComputation* computation)
{
	glManager.setComputationCore(computation);
}


void OsciBuilder::setControlsInbuild()
{
	glManager.setControls(new UserControls);
}

void OsciBuilder::initOsci(int argc, char* argv[])
{
	// TODO: Check if all requirements are met...
	glManager.initialize(argc, argv);
}

