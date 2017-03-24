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
struct CompBurst
{
	bool operator()(const PEC* a, const PEC* b) {
		return a->getPCB().BurstList.front() > b->getPCB().BurstList.front();
	}
};
struct Processor
{
public:
	vector<PEC*> FBQueue[4];
	vector<PEC*> waitingQueue;
	PEC* CurrProccess;
	double executionTimeNeeded;
	double processorTimeAllowed = 0;
};
priority_queue<PEC*, vector<PEC*>, Comp> PECList;
vector<PEC*> PECComplete;
//map<int, PCB*> currentProcessTable;
vector<PEC*> PECReadyQueue;
//pair<PEC*, double> nextEvent;
double currentTime;

void FCFS(PEC* nextE, const Processor &processor)
{
	nextE->state = waiting;
	for (auto fbQ : processor[nextE->inProcessor].FBQueue)
	{
		for (auto proc : fbQ)
		{
			if (proc != nextE)
			{
				proc->increaseWaitTimeTotal(proc->getPCB().BurstList.front()); // increase wait for all other processes
			}
			else
			{
				proc->increaseExecutionTimeTotal(proc->getPCB().BurstList.front()); // increase execution time
			}
		}
		nextE->getPCB().BurstList.pop(); // remove execution time from list.
	}
	if (nextE->getPCB().BurstList.empty())
	{
		nextE->setEndTime();
		PECComplete.push_back(nextE);
		processor[nextE->inProcessor].FBQueue[nextE->inFBQueue].erase(remove(processor[nextE->inProcessor].waitingQueue.begin(), processor[nextE->inProcessor].waitingQueue.end(), nextE), processor[nextE->inProcessor].waitingQueue.end());

	}
	else
	{
		processor[nextE->inProcessor].waitingQueue.push_back(nextE);
		processor[nextE->inProcessor].FBQueue[nextE->inFBQueue].erase(remove(processor[nextE->inProcessor].waitingQueue.begin(), processor[nextE->inProcessor].waitingQueue.end(), nextE), processor[nextE->inProcessor].waitingQueue.end());
	}
	for (auto fbQ : processor[nextE->inProcessor].FBQueue)
	{
		if (!fbQ.empty())
		{
			processor[nextE->inProcessor].CurrProccess = fbQ[0];
			break;
		}
	}

}
