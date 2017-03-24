#pragma once
#include <iostream> 
#include <vector> 
#include <map>
#include <deque>
#include <queue>

class PCB {
private:
	int priority;
	long int programCounter;
	double timeLimit;


	double endTime;
	double throughput; // reseaarch
	double arrivalTime;
	double executionTime = 0;
	double waitTime = 0;



public:

	std::map <double, double> burstTimeMap;
	std::queue<double, std::deque<double>> BurstT;
	

	PCB::PCB(double a1, std::vector<double> bursts) {
		std::queue<double, std::deque<double>> q(std::deque<double>(bursts.begin()+2,bursts.end()));

		while (!bursts.empty())
		{
			std::cout << "@" << bursts.front() << std::endl;
			BurstT.push(bursts.front());
			bursts.pop_back();
		}
		BurstT = q;
		arrivalTime = a1;
	}
	PCB::PCB(){}



	void setTimeLimit(double t1) { timeLimit = t1; }// bao was here

	double getExecutionTime() const { return executionTime; }
	double getWaitTime() const { return  waitTime; }
	void addExecutionTime(double x)
	{
		executionTime += x;
	}

	void addWaitingTime(double x)
	{
		waitTime += x;
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
	double getTime()
	{
		return arrivalTime + executionTime + waitTime;
	}
	const double getArrivalTime() const
	{
		return arrivalTime;
	}
};
