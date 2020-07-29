
#include <iostream>
#include "OsciBuilder.h"
#include "AudioComputation.h"


int main(int argc, char* argv[])
{
	
	OsciBuilder * osciBuilder = new OsciBuilder();

	//osciBuilder->setComputationInbuild();

	osciBuilder->setComputation(new AudioComputation);
	osciBuilder->setControlsInbuild();
	
	osciBuilder->initOsci(argc, argv);

	delete osciBuilder;

}
