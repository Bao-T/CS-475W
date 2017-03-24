#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <map>

int randBurst()
{
	return rand() % 5 + 1;
}

int randID()
{
	return rand() % 10000 + 1;
}

int randArriveTime()
{
	return rand() % 300 + 1;
}

void genDataFile()
{
	std::map<int, int> PID;
	srand(time(NULL));
	std::ofstream myfile;
	myfile.open("datafile.txt", std::ofstream::out | std::ofstream::trunc);
	if (myfile.is_open())
	{
		for (int k = 0; k < 20; ) {
			int id = randID();
			if (PID.find(id) == PID.end())
			{
				myfile << id << "," << randArriveTime();
				int bursts = rand() % 40 + 1;
				for (int i = 0; i < bursts; i++)
				{
					myfile << "," << randBurst();
				}
				myfile << "\n";
				k++;
			}
		}
	}
	else std::cout << "Unable to open file";
	return;
}
