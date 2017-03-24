

#include <queue>
using namespace std;
struct PCB
{
	double arrivalTime;
	queue<double, deque<double>> BurstList;
	double endTime;
	double executionTotalTime = 0;
	double waitTotalTime = 0;
	
};
enum State
{
	waiting, ready, executing, none
};

class PEC
{
private:
	PCB pcb;
	double PID;
public:
	State state = none;
	PEC::PEC(int id, double arr, vector<double> bursts)
	{
		PID = id;
		pcb.arrivalTime = arr;
		std::queue<double, std::deque<double>> q(std::deque<double>(bursts.begin() + 2, bursts.end()));
		pcb.BurstList = q;
	}

	PCB getPCB() const
	{
		return pcb;
	}
	void increaseExecutionTimeTotal(double length)
	{
		pcb.executionTotalTime += length;
	}
	void increaseWaitTimeTotal(double length)
	{
		pcb.waitTotalTime += length;
	}


};