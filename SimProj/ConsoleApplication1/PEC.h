#include <iostream>
#include <vector>
#include <string>
#include "PCB.h"

using namespace std;

class PEC {

private:
	string textregion;
	int PID;
	int processControlBlock;


public:
	enum State;

	vector<int> dataRegion;



	string returntextregion()
	{
		return textregion;
	}

	int returnPID()
	{
		return PID;
	}

};
