
#include <iostream>
#include "OsciBuilder.h"
#include "AudioComputation.h"


int main(int argc, char* argv[])
{

	std::cout << "Hello World!\n";
	
	OsciBuilder * osciBuilder = new OsciBuilder();

	//osciBuilder->setComputationInbuild();

	osciBuilder->setComputation(new AudioComputation);
	osciBuilder->setControlsInbuild();
	
	osciBuilder->initOsci(argc, argv);


}
