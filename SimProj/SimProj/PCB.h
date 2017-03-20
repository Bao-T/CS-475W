#pragma once
#include <iostream> 
#include <vector> 
#include <map>

class PCB {
private:
	int priority;
	long int programCounter;
	double timeLimit;
	double arrivalTime;

public:
	std::map <double, double> burstTimeMap;
	std::vector <double> cpuBurstT;
	std::vector <double> ioBurstT;

	PCB::PCB(int p, long int pc, double a1) {
		priority = p;
		programCounter = pc;
		arrivalTime = a1;
	}

	void setCPUBurst(double cpu) {
		cpuBurstT.push_back(cpu);
	}

	void setIOBurst(double io) {
		ioBurstT.push_back(io);
	}

	int getPriority() {
		return priority;
	}

	int getProgramCounter() {
		return programCounter;
	}

	double getTimeLimit() {
		return timeLimit;
	}

	double getArrivalTime() {
		return arrivalTime;
	}
};