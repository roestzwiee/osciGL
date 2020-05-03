

#include <iostream>
#include "OsciBuilder.h"

int main(int argc, char* argv[])
{

	std::cout << "Hello World!\n";
	
	OsciBuilder * osciBuilder = new OsciBuilder();

	osciBuilder->setComputationInbuild();
	osciBuilder->setControlsInbuild();
	
	osciBuilder->initOsci(argc, argv);

}
