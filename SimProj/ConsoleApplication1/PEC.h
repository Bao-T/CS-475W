#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "PCB.h"

class PEC {
private:
	int processControlBlock;

public:
	enum State;

	std::map <int, PCB> PID;
	std::vector<int> dataRegion;
	std::vector<std::string> textregion;

	int returnPCB() {
		return processControlBlock;

	}

	PEC(int x, PCB y) {
		PID[x] = y;
	}
};
