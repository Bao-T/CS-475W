#pragma once
#include <iostream>
#include "PCB.h"
#include "PEC.h"
#include "DataFileGen.h"
#include "PCB.h"
#include "PEC.h"
#include <vector>
#include <map>
#include <queue>

vector<PEC> allProcesses;
vector<PEC*> completedProcesses;
map<int, PCB*> currentProcessTable;
queue<PEC*> readyQueue;
queue<PEC*> waitingQueue;
PEC* processors[4];

void analysis()
{
	
}