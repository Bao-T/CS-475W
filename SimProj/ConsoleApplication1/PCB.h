#include <iostream> 
#include <vector> 

class PCB {
private:
	int priority;
	long int programCounter;
	double timeLimit;

public:
	std::vector <double, double> cpuBurstT;
	std::vector <double, double> ioBurstT;

	int getPriority() {
		return priority;
	}

	int getProgramCounter() {
		return programCounter;
	}

	double getTimeLimit() {
		return timeLimit;
	}
};