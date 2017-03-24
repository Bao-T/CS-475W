#pragma once
#include <iostream>
#include "PEC.h"
#include "PCB.h"




void RoundRobin(int TimeQuantum, &PEC, int currentProcess, int currentQueue)
{
	if (PEC.PCB.BurstT.top > TimeQuantum)
	{
		currentQueue--;
		process[currentProcess].FBqueue[currentQueue].push_back;
	}
	else if (BurstT.top < TimeQuantum)
	{
		add(BurstT.top).pop;
	}
	else if (BurstT.top = TimeQuantum)
	{
		PCB.add.ExecutionTime(TimeQuantum);
			BurstT.pop;
	}
}