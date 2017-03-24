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
	bool operator()( const PEC* a, const PEC* b){
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

priority_queue<PEC*,vector<PEC*>,Comp> PECList;
vector<PEC*> PECComplete;
//map<int, PCB*> currentProcessTable;
vector<PEC*> PECReadyQueue;
//pair<PEC*, double> nextEvent;
double currentTime;
Processor processor[4];


void loadDataFile()
{
	ifstream input("datafile.txt");
	while (input)
	{
		while (input)
		{
			string s;
			if (!getline(input, s)) break;
			istringstream ss(s);
			vector<double> data;

			while (ss)
			{
				string s;
				if (!getline(ss, s, ',')) break;
				data.push_back(std::stod(s));
			}
			PEC temp(data[0], data[1], data);
			//cout << "\t" << data[1] << "\t" << data[2] << endl;
			//NumOfProcesses++;
			PECreferences.push_back(temp);
			

		}

	}

	for (int i = 0; i < PECreferences.size();i++)
	{
		PECList.push(&PECreferences[i]);
	}
	
}
void loadBalancing()
{
	for (auto rp : PECReadyQueue)
	{
		int procIndx = 0;
		int pQSize = processor[0].FBQueue[0].size() + processor[0].FBQueue[1].size() + processor[0].FBQueue[2].size() + processor[0].FBQueue[3].size() + processor[0].FBQueue[4].size();
		for (int i = 1; i < 4; i++)
		{
			if (pQSize > processor[i].FBQueue[0].size() + processor[i].FBQueue[1].size() + processor[i].FBQueue[2].size() + processor[i].FBQueue[3].size() + processor[i].FBQueue[4].size())
			{
				pQSize = processor[i].FBQueue[0].size() + processor[i].FBQueue[1].size() + processor[i].FBQueue[2].size() + processor[i].FBQueue[3].size() + processor[i].FBQueue[4].size();
				procIndx = i;
			}
		}
		rp->inProcessor = procIndx;
		rp->inFBQueue = 0;
		rp->state = ready;
		processor[procIndx].FBQueue[0].push_back(rp);
	}

	//for (auto p : processor)
	//{
	//	if (p.FBQueue[0].size() + p.FBQueue[1].size() + p.FBQueue[2].size() + p.FBQueue[3].size() + p.FBQueue[4].size() == 0)
	//	{
	//		int procIndx = 0;
	//		int overloadIndex = processor[0].FBQueue[0].size() + processor[0].FBQueue[1].size() + processor[0].FBQueue[2].size() + processor[0].FBQueue[3].size() + processor[0].FBQueue[4].size();
	//		for (int i = 1; i < 4; i++)
	//		{
	//			if (overloadIndex > processor[i].FBQueue[0].size() + processor[i].FBQueue[1].size() + processor[i].FBQueue[2].size() + processor[i].FBQueue[3].size() + processor[i].FBQueue[4].size())
	//			{
	//				overloadIndex = processor[i].FBQueue[0].size() + processor[i].FBQueue[1].size() + processor[i].FBQueue[2].size() + processor[i].FBQueue[3].size() + processor[i].FBQueue[4].size();
	//				procIndx = i;
	//			}
	//		}
	//		int carryOverAmount = overloadIndex / 2;
	//		for (int k = 0; k < 5; k++)
	//		{
	//			for (int i = 0; i < processor[procIndx].FBQueue[k].size() && carryOverAmount > 0;)
	//			{
	//				if (processor[procIndx].FBQueue[k][i]->state != executing)
	//				{
	//					carryOverAmount--;
	//					p.FBQueue[0].push_back(processor[procIndx].FBQueue[k][i]);
	//					p.processesInQueue++;
	//					processor[procIndx].FBQueue[k].erase(processor[procIndx].FBQueue[k].begin() + i);
	//					processor[procIndx].processesInQueue--;

	//				}
	//				else
	//					i++;
	//			}
	//		}


	//	}
	//}

}

void Scheduler()
{
	priority_queue<PEC*, vector<PEC*>, CompBurst> nextEvent;
	int processorNumber = 0;
	for (auto p:processor)
	{
		if (p.CurrProccess != NULL)
		{
			nextEvent.push(p.CurrProccess); // current processes in Processors
		}
		for (auto wq: p.waitingQueue)
		{
			nextEvent.push(wq); // All in waiting queue
		}
	}
	nextEvent.push(PECList.top());
	
	PEC* nextE = nextEvent.top();
	if (nextE->state == waiting)
	{
		nextE->increaseWaitTimeTotal(nextE->getPCB().BurstList.front()); // increase wait time
		processor[nextE->inProcessor].FBQueue[0].push_back(nextE); // put back into FBqueue
		nextE->state = ready; //set to ready
		nextE->inFBQueue = 0;
		//remove from waiting queue
		processor[nextE->inProcessor].waitingQueue.erase(remove(processor[nextE->inProcessor].waitingQueue.begin(), processor[nextE->inProcessor].waitingQueue.end(), nextE), processor[nextE->inProcessor].waitingQueue.end());
	}
	else if (nextE->state == none)
	{
		nextE->state = ready; // set to ready
		PECReadyQueue.push_back(nextE); // put to PEC ready queue for load balancing
		PECList.pop(); // remove from PEC list
	}
	else if (nextE->state == executing) //FBqueue Algorithms
	{
		//FCFS
		nextE->state = waiting;
		for (auto fbQ:processor[nextE->inProcessor].FBQueue)
		{
			for (auto proc:fbQ)
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
}
int main()
{
	genDataFile();
	loadDataFile();
	//while(!PECList.empty())
	//{
	//	cout << PECList.top()->getPCB().arrivalTime << endl;
	//	PECReadyQueue.push_back(PECList.top());
	//	PECList.pop();
	//}
	

	cout << " ";

	Scheduler();
	loadBalancing();
	Scheduler();
}