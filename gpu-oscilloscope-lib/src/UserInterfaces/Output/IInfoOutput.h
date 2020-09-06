#pragma once
#include <string>
#include <list>

using namespace std;

struct InfoData
{
	string label;
	string value;
};

/*
 * Whatever class implements IInfoOutput can be registered at the ConsoleView. This results in all its
 * InfoData to be displayed. 
 */
class IInfoOutput
{
public:
	virtual ~IInfoOutput() = default;

	virtual list<InfoData> getInfoData() = 0;
};