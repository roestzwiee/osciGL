
#include <iostream>
#include "OsciBuilder.h"
#include "AudioComputation.h"


int main(int argc, char* argv[])
{
	
	OsciBuilder osciBuilder;

	osciBuilder.setComputation(new AudioComputation);
	osciBuilder.setControlsInbuild();
	
	osciBuilder.initOsci(argc, argv);

}
