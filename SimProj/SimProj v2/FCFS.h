#pragma once
#include <iostream>
#include "DataFileGen.h"
#include "PEC.h"
#include <vector>
#include <map>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>
using std::vector;
using std::cout;
using std::map;

vector<PEC> PECreferences;
struct Comp
{
	bool operator()(const PEC* a, const PEC* b) {
		return a->getPCB().arrivalTime > b->getPCB().arrivalTime;
	}
};
priority_queue<PEC*, vector<PEC*>, Comp> PECList;
vector<PEC*> PECComplete;
//map<int, PCB*> currentProcessTable;
vector<PEC*> PECReadyQueue;
//pair<PEC*, double> nextEvent;
double currentTime;

struct Processor
{
public:
	vector<PEC*> FBQueue[4];
	vector<PEC*> waitingQueue;
	PEC* CurrProccess;
	double executionTimeNeeded;
	double processorTimeAllowed = 0;
};


//Have no idea if this is correct
void FCFS(PEC &PEC, int currentprocess, int currentqueue) {
	if (PECReadyQueue[0].getPCB().executionTotalTime == 0) {
		PECComplete.push_back(PECReadyQueue[0].getPCB().erase);
	}

	else if (PECReadyQueue[0].getPCB().executionTotalTime > 0) {
		PECReadyQueue[0].getPCB().waitTotalTime + randBurst();
		PECReadyQueue[0].getPCB().executionTotalTime - randBurst();
	}

	for (int i = 0; i < PECReadyQueue.size(); i++) {
		PECReadyQueue[i].waitTotaltime + randBurst();
	}
}