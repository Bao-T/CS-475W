#include <iostream>
#include <vector>
#include <string>
#include "PCB.h"

using namespace std;

class PEC {

private:
	int PID;
	int processControlBlock;


public:
	enum State;

	vector<int> dataRegion;
	vector<string> textregion;

	int returnPCB()
	{
		return processControlBlock;
	}

	int returnPID()
	{
		return PID;
	}

};
