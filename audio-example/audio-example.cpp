
#include <iostream>
#include "OsciBuilder.h"


void poo();

int main(int argc, char* argv[])
{

	std::cout << "Hello World!\n";
	
	OsciBuilder * osciBuilder = new OsciBuilder();

	osciBuilder->setComputationInbuild();
	osciBuilder->setControlsInbuild();
	
	osciBuilder->initOsci(argc, argv);


}
