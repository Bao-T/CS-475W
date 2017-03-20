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
	double waitTime;
	double endTime;
	double throughput; // reseaarch

public:
	std::map <double, double> burstTimeMap;
	std::vector <double> cpuBurstT;
	std::vector <double> ioBurstT;

	PCB::PCB(int p, long int pc, double a1) {
		priority = p;
		programCounter = pc;
		arrivalTime = a1;
	}

	void setTimeLimit(double t1) { timeLimit = t1; }// bao was here
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