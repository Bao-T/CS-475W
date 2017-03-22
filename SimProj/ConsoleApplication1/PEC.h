#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "PCB.h"

using namespace std;

class PEC {

private:
	int processControlBlock;


public:
	enum State;

	vector<int> dataRegion;
	vector<string> textregion;

	int returnPCB()
	{
		return processControlBlock;

	}

	map <int, PCB> PID;

	PEC(int x, PCB y)
	{
		PID[x] = processControlBlock;
		
		PID[x, y];

	}

	

};
