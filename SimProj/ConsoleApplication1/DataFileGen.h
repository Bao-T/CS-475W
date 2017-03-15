#include <iostream>
#include <fstream>
#include <time.h>

int randBurst()
{
	return rand() % 1000 + 1;
}

int randID()
{
	return rand() % 10000 + 1;
}

int randArriveTime()
{
	return rand() % 1000000 + 1;
}

void genDataFile()
{
	srand(time(NULL));
	std::ofstream myfile;
	myfile.open("datafile.txt", std::ofstream::out | std::ofstream::trunc);
	if (myfile.is_open())
	{
		for (int k = 0; k < 300; k++) {
			myfile << randID() << "," << randArriveTime();
			int bursts = rand() % 40 + 1;
			for (int i = 0; i < bursts; i++)
			{
				myfile << "," << randBurst() ;
			}
			myfile << "\n";
		}
	}
	else std::cout << "Unable to open file";
	return;
}
