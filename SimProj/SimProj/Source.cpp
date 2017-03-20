#include <iostream>
#include "DataFileGen.h"
#include "PCB.h"
#include "PEC.h"
#include <vector>
#include <map>
#include <queue>
using std::vector;
using std::cout;
using std::map;


vector<PEC> allProcesses;
vector<PEC*> completedProcesses;
map<int, PCB*> currentProcessTable;
queue<PEC*> readyQueue;
queue<PEC*> waitingQueue;
PEC* processors[4];


int main()
{
	genDataFile();


}

void scheduler()
{
	if (readyQueue.empty()){}
	else
	{
		



	}
}

