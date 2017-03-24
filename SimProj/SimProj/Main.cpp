#include <iostream>
#include "DataFileGen.h"
#include "PCB.h"
#include "PEC.h"
#include <vector>
#include <map>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using std::vector;
using std::cout;
using std::map;

vector<PEC> PECreferences;
priority_queue<PEC*> allProcesses;
vector<PEC*> completedProcesses;
map<int, PCB*> currentProcessTable;
vector<PEC*> readyQueue;
pair<PEC*, double> nextEvent;
double currentTime;
enum nE
{
	admitToReady, moveToReady, dispatch, processorEvent
};


int NumOfProcesses = 0;

struct Processor
{
public:
	vector<PEC*> processQueue[4];
	vector<pair<PEC*, double>> waitingQueue;
	int processesInQueue = 0;
	PEC* CurrProccess;
	double executionTime;
	double processorTime;
};

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
			cout << "\t"<< data[1]<< "\t"<< data[2] <<endl;
			NumOfProcesses++;
			///
			PECreferences.push_back(temp);


		}

	}

	for (auto p: PECreferences)
	{
		allProcesses.emplace(&p);
	}
}
void loadBalancing()
{
	for (auto rp: readyQueue)
	{
		int procIndx = 0;
		int pQSize = processor[0].processQueue[0].size()+ processor[0].processQueue[1].size()+ processor[0].processQueue[2].size()+ processor[0].processQueue[3].size() + processor[0].processQueue[4].size();
		for (int i = 1; i < 4; i++)
		{
			if (pQSize < processor[i].processQueue[0].size() + processor[i].processQueue[1].size() + processor[i].processQueue[2].size() + processor[i].processQueue[3].size() + processor[i].processQueue[4].size())
			{
				pQSize = processor[i].processQueue[0].size() + processor[i].processQueue[1].size() + processor[i].processQueue[2].size() + processor[i].processQueue[3].size() + processor[i].processQueue[4].size();
				procIndx = i;
			}
		}

		processor[procIndx].processQueue[0].push_back(rp);
	}

	for (auto p : processor)
	{
		if (p.processQueue[0].size() + p.processQueue[1].size() + p.processQueue[2].size() + p.processQueue[3].size() + p.processQueue[4].size() == 0)
		{
			int procIndx = 0;
			int overloadIndex = processor[0].processQueue[0].size() + processor[0].processQueue[1].size() + processor[0].processQueue[2].size() + processor[0].processQueue[3].size() + processor[0].processQueue[4].size();
			for (int i = 1; i < 4; i++)
			{
				if (overloadIndex > processor[i].processQueue[0].size() + processor[i].processQueue[1].size() + processor[i].processQueue[2].size() + processor[i].processQueue[3].size() + processor[i].processQueue[4].size())
				{
					overloadIndex = processor[i].processQueue[0].size() + processor[i].processQueue[1].size() + processor[i].processQueue[2].size() + processor[i].processQueue[3].size() + processor[i].processQueue[4].size();
					procIndx = i;
				}
			}
			int carryOverAmount = overloadIndex / 2;
			for (int k = 0; k < 5; k++)
			{
				for (int i = 0; i < processor[procIndx].processQueue[k].size() && carryOverAmount > 0;)
				{
					if (processor[procIndx].processQueue[k][i]->state != executing)
					{
						carryOverAmount--;
						p.processQueue[0].push_back(processor[procIndx].processQueue[k][i]);
						p.processesInQueue++;
						processor[procIndx].processQueue[k].erase(processor[procIndx].processQueue[k].begin() + i);
						processor[procIndx].processesInQueue--;

					}
					else
						i++;
				}
			}

			
		}
	}

}


void Scheduler()
{
	
	nE next;
	if (!allProcesses.empty())
	{
		currentTime = allProcesses.top()->getPCB().getArrivalTime();
		if (currentTime >= allProcesses.top()->getPCB().getArrivalTime())
		{
			currentTime = allProcesses.top()->getPCB().getArrivalTime();
			next = admitToReady;
		}
	}
	else
	{
		for(auto proc: processor)
		{
			if (proc.processQueue[0].empty());
				//currentTime = proc.processQueue[0].front()->getPCB().;
		}
	}



	

	PEC* processToChange;
	int processorToChange;
	pair<PEC*, double> waitingQueueToChange;
	
	int processorCount = 0;
	for (auto p: processor)
	{
		if (p.CurrProccess != NULL)
		{
			for (int i = 0; i < 5; i ++)
			{
				for (int k = 0; k < p.processQueue[i].size(); k++)
				{
					if (k == 0)
						p.processorTime = 10;
					else if (k == 1)
						p.processorTime = 30;
					else if (k == 2)
						p.processorTime = 50;
					else if (k >= 3)
						p.processorTime = p.executionTime;





					if (p.CurrProccess != NULL && currentTime >= p.CurrProccess->getPCB().getTime() + p.processorTime)
					{
						currentTime = p.CurrProccess->getPCB().getTime() + p.processorTime;
						processToChange = p.CurrProccess;
						processorToChange = processorCount;
						next = processorEvent;

					}
					
				}
			}
		}
		processorCount++;
	}
	
	processorCount = 0;
	/*
	for (auto p : processor)
	{
		for (auto w : p.waitingQueue)
		{
			if (currentTime >= w.second)
			{
				currentTime = w.second;
				next = moveToReady;
				processorToChange = processorCount;
				processToChange = w.first;
				waitingQueueToChange = w;
			}
		}
		processorCount++;
	}

	*/
	if (next == admitToReady)
	{
		PEC* temp = allProcesses.top();
		
	    readyQueue.push_back(temp);
		allProcesses.pop();
	}

	/*
	if (next == moveToReady)
	{
		processToChange->getPCB().addWaitingTime(processToChange->getPCB().BurstT.front());
		processToChange->getPCB().BurstT.pop();
		if (processToChange->getPCB().BurstT.empty())
		{
			completedProcesses.push_back(processToChange);
			processor[processorToChange].waitingQueue.erase(std::remove(processor[processorToChange].waitingQueue.begin(), processor[processorToChange].waitingQueue.end(), waitingQueueToChange), processor[processorToChange].waitingQueue.end());
		}
		else
		{
			processor[processorToChange].processQueue[0].push_back(processToChange);
			processor[processorToChange].waitingQueue.erase(std::remove(processor[processorToChange].waitingQueue.begin(), processor[processorToChange].waitingQueue.end(), waitingQueueToChange), processor[processorToChange].waitingQueue.end());
		}
	}




	if(next == processorEvent) //FBQUEUE
	{
		//Queue 4 FCFS
		for (auto q4 : processor[processorToChange].processQueue[2])
		{
			processor[processorToChange].processorTime = 50;
			if (q4 == processToChange)
			{
				for (auto i : processor[processorToChange].processQueue)
				{
					for (auto j : i)
					{
						if (j != processToChange)
						{
							
								j->getPCB().addWaitingTime( processor[processorToChange].executionTime);
						}
					}
				}
				
				if (q4->getPCB().BurstT.empty())
				{
					completedProcesses.push_back(q4);
				}
				else
				{

					processor[processorToChange].waitingQueue.push_back(make_pair(q4, q4->getPCB().BurstT.front()));
					q4->getPCB().BurstT.pop();
				}



				processor[processorToChange].processQueue[0].erase(std::remove(processor[processorToChange].processQueue[0].begin(), processor[processorToChange].processQueue[0].end(), q4), processor[processorToChange].processQueue[0].end());


			}
		}










		//Queue 3 
		for (auto q3 : processor[processorToChange].processQueue[2])
		{
			processor[processorToChange].processorTime = 50;
			if (q3 == processToChange)
			{
				for (auto i : processor[processorToChange].processQueue)
				{
					for (auto j : i)
					{
						if (j != processToChange)
						{
							if (processor[processorToChange].processorTime <processor[processorToChange].executionTime)
								j->getPCB().addWaitingTime(processor[processorToChange].processorTime);
							else
								j->getPCB().addWaitingTime(processor[processorToChange].processorTime - processor[processorToChange].executionTime);
						}
					}
				}
				if (processor[processorToChange].processorTime <processor[processorToChange].executionTime) //if needs extra time
				{
					q3->getPCB().BurstT.front() -= processor[processorToChange].processorTime;
					processor[processorToChange].executionTime -= processor[processorToChange].processorTime;
					processor[processorToChange].processQueue[3].push_back(q3);
					

				}
				if (q3->getPCB().BurstT.empty())
				{
					completedProcesses.push_back(q3);
				}
				else
				{

					processor[processorToChange].waitingQueue.push_back(make_pair(q3, q3->getPCB().BurstT.front()));
					q3->getPCB().BurstT.pop();
				}



				processor[processorToChange].processQueue[0].erase(std::remove(processor[processorToChange].processQueue[0].begin(), processor[processorToChange].processQueue[0].end(), q3), processor[processorToChange].processQueue[0].end());


			}
			}
		//Queue 2
		for (auto q2 : processor[processorToChange].processQueue[1])
		{
			processor[processorToChange].processorTime = 30;
			if (q2 == processToChange)
			{
				for (auto i : processor[processorToChange].processQueue)
				{
					for (auto j : i)
					{
						if (j != processToChange)
						{
							if (processor[processorToChange].processorTime <processor[processorToChange].executionTime)
								j->getPCB().addWaitingTime(processor[processorToChange].processorTime);
							else
								j->getPCB().addWaitingTime(processor[processorToChange].processorTime - processor[processorToChange].executionTime);
						}
					}
				}
				if (processor[processorToChange].processorTime <processor[processorToChange].executionTime) //if needs extra time
				{
					q2->getPCB().BurstT.front() -= processor[processorToChange].processorTime;
					processor[processorToChange].executionTime -= processor[processorToChange].processorTime;
					processor[processorToChange].processQueue[2].push_back(q2);
					

				}
				if (q2->getPCB().BurstT.empty())
				{
					completedProcesses.push_back(q2);
				}
				else
				{

					processor[processorToChange].waitingQueue.push_back(make_pair(q2, q2->getPCB().BurstT.front()));
					q2->getPCB().BurstT.pop();
				}



				processor[processorToChange].processQueue[0].erase(std::remove(processor[processorToChange].processQueue[0].begin(), processor[processorToChange].processQueue[0].end(), q2), processor[processorToChange].processQueue[0].end());


			}
			}
		//Queue 1
		for(auto q1 : processor[processorToChange].processQueue[0])
		{
			processor[processorToChange].processorTime = 10;
			if (q1 == processToChange)
			{
				for (auto i: processor[processorToChange].processQueue)
				{
					for(auto j: i)
					{
						if (j != processToChange)
						{
							if (processor[processorToChange].processorTime <processor[processorToChange].executionTime)
								j->getPCB().addWaitingTime(processor[processorToChange].processorTime);
							else
								j->getPCB().addWaitingTime(processor[processorToChange].processorTime - processor[processorToChange].executionTime);
						}
					}
				}
				if (processor[processorToChange].processorTime <processor[processorToChange].executionTime) //if needs extra time
				{
					q1->getPCB().BurstT.front() -= processor[processorToChange].processorTime;
					processor[processorToChange].executionTime -= processor[processorToChange].processorTime;
					processor[processorToChange].processQueue[1].push_back(q1);
					

				}

				if (q1->getPCB().BurstT.empty())
				{
					completedProcesses.push_back(q1);
				}
				else
				{

					processor[processorToChange].waitingQueue.push_back(make_pair(q1, q1->getPCB().BurstT.front()));
					q1->getPCB().BurstT.pop();
				}



					processor[processorToChange].processQueue[0].erase(std::remove(processor[processorToChange].processQueue[0].begin(), processor[processorToChange].processQueue[0].end(), q1), processor[processorToChange].processQueue[0].end());


			}
		}




		for (int i = 0; i < processor[processorToChange].processQueue->size(); i ++)
		{
			if (processor[processorToChange].processQueue[i][0] != NULL && i < 3)
			{
				processor[processorToChange].CurrProccess = processor[processorToChange].processQueue[i][0];
				processor[processorToChange].executionTime = processor[processorToChange].processQueue[i][0]->getPCB().BurstT.front();
				processor[processorToChange].processQueue[i][0]->getPCB().BurstT.pop();
				break;
			}
			//else if (processor[processorToChange].processQueue[i][0] != NULL && i = 2)
		
			else if (processor[processorToChange].processQueue[i][0] != NULL && i == 3)
			{
				processor[processorToChange].CurrProccess = processor[processorToChange].processQueue[i][0];
				processor[processorToChange].executionTime = processor[processorToChange].processQueue[i][0]->getPCB().BurstT.front();
				processor[processorToChange].processQueue[i][0]->getPCB().BurstT.pop();
			}
		}

		
	}
	*/
}


int main()
{
	genDataFile();
	loadDataFile();
	//currentTime = allProcesses.top().getPCB().getArrivalTime();

	for (int i = NumOfProcesses; i > 0; i --)//while(completedProcesses.size() < NumOfProcesses)
	{
		loadBalancing();
		Scheduler();
		
	}

	while (!allProcesses.empty())
	{
		PEC* pec = allProcesses.top();
		cout << "PID: " << pec->returnPID()<<"\t Execution Time: " << pec->getPCB().getExecutionTime() << "\t Wait Time: " << pec->getPCB().getWaitTime() << endl;
		allProcesses.pop();
	}


}


