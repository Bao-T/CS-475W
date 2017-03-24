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
priority_queue<PEC*,vector<PEC*>,Comp> PECList;
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

int main()
{
	genDataFile();
	loadDataFile();
	//while(!PECList.empty())
	//{
	//	cout << PECList.top()->getPCB().arrivalTime << endl;
	//	PECList.pop();
	//}


}