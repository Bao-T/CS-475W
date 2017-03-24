//#include <iostream>
//#include "DataFileGen.h"
//#include "PCB.h"
//#include "PEC.h"
//#include <vector>
//#include <map>
//#include <queue>
//#include <fstream>
//#include <string>
//#include <sstream>
//using std::vector;
//using std::cout;
//using std::map;
//
//
//priority_queue<PEC> allProcesses;
//vector<PEC*> completedProcesses;
//map<int, PCB*> currentProcessTable;
//queue<PEC*> readyQueue;
//vector<pair<PEC*,double>> waitingQueue;
//vector<PEC*> processorQueue[4];
//pair<PEC*,double> processorCE[4];
//double currentTime;
//
//
//void loadDataFile()
//{
//	ifstream input("datafile.txt");
//	while (input)
//	{
//		while (input)
//		{
//			string s;
//			if (!getline(input, s)) break;
//			istringstream ss(s);
//			vector<double> data;
//
//			while (ss)
//			{
//				string s;
//				if (!getline(ss, s, ',')) break;
//				data.push_back(std::stod(s));
//			}
//			PEC temp(data[0], data[1], data);
//			allProcesses.emplace(temp);
//
//
//		}
//
//	}
//}
//
//void loadBalancing() // call for all time updates (at the end of every FBqueue check
//{
//	for (auto p: processorCE)
//	{
//		/*
//		if current time >= allprocesses.next.arrival time
//		{
//			put allprocesses.next into a queue for an available processor that has the smallest queue
//			delete allprocesses.next from allproccesses
//			
//		}
//		if this processor's queue is empty, take a processes from the largest processor queue or take half of those PEC
//
//
//		*/
//		
//	}
//	
//}
// 
//void fBQueue() //(put in main with a while look)
//{
//	/*
//for all processors;
//	if a processor is available (ie, currentTime >= time a processes in processor takes to complete/time it would take for it to go into ready queue)
//		find a queue that is not empty. start from 1 and go to 5
//		for PEC is not finsihed after q1 executes, move to queue --
//			for all PEC not executed, age++
//				if age = 5, queue ++
//			time wait for processes += I/O burst time or time wait += time of last process leaving processor - time processs came into ready queue
//		
//			if executed, current time = time arrived to execute 
//
//		if process = finished
//			total time = times in processor + time wating + time in I/O burst
//		
//		if everything is empty, current time = arrival time of first process in allProcesses (case for starting up the simulation
//	check waiting queue, push to ready queue when time quantum reached
//	load balancing check will be here
//
//
//	*/
//
//
//}
//void temp()
//{
//	pair<PEC, double> smallest = make_pair(allProcesses.top(), allProcesses.top().getPCB().getArrivalTime());
//	readyQueue.push(&smallest.first);
//
//	while (true)
//	{
//		
//		for (auto p : processorCE)
//		{
//			if (smallest.second >= p.first->getPCB().getTime() + processorCE->second)
//			{
//				smallest = make_pair(p, p.first->getPCB().getTime() + processorCE->second);
//			}
//		}
//		for (auto p: waitingQueue)
//		{
//			if(smallest.second >= p.first->getPCB().getTime() + p.second)
//			{
//				smallest = make_pair(p, p.first->getPCB().getTime() + p.second);
//			}
//		}
//		if (smallest.second >= allProcesses.top().getPCB().getArrivalTime())
//		{
//			smallest = make_pair(allProcesses.top(), allProcesses.top().getPCB().getArrivalTime());
//		}
//
//	}
//
//
//}
//
///*
//find the next smallest time interval (arriving process, CPU burst time end, I/O burst time end)
//smallest time 
//arriving process
//	smallest time = arrival time
//CPU burst time end (of all cores) (find a process for each core using FBqueue)
//	smallest time = (arrival Time + executionTime + waitTime + CPU burst time (current))
//I/O burst time end
//	smallest time = (arrival Time + executionTime + waitTime + I/O burst time (current))
//
//set time to smallest one of the three
//current time = STI
//
//arriving process
//	push to ready queue
//	load balancing
//	push to CPU queue
//CPU
//	add burst time to execution time
//	add burst time to all processes in the processor's queue's waitTime except for the process being executed (only processes on the same core)
//	put in waiting queue
//I/O burst
//	add I/O burst time to current process' waitTime
//	put in ready queue.
//
//
//
//
//*/
//
//
//int main1()
//{
//	genDataFile();
//	loadDataFile();
//
//	//while (!allProcesses.empty())
//	//{
//	//	cout << allProcesses.top().getPCB().getArrivalTime() << " "; 
//	//	allProcesses.pop();
//	//}
//
//
//
//}