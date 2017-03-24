#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "PCB.h"

using namespace std;
enum State {waiting, ready, executing};
class PEC {

private:
	int PID;
	PCB processControlBlock;
public:
	State state;

	vector<int> dataRegion;
	vector<string> textregion;



	PEC::PEC(int id, double arrivalTime, vector<double> bursts)
	{
		PID = id;
		vector <double> t = bursts;
		processControlBlock = *new PCB(arrivalTime,t);
	}



	int returnPID() const
	{
		return PID;
	}

	PCB getPCB() const
	{
		return processControlBlock;
	}

	bool operator<( const PEC& rhs) const
	{
		return getPCB().getArrivalTime() > rhs.getPCB().getArrivalTime();
	}

};


