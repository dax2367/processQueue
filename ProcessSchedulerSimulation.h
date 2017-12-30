// Program:		Process Que Simulation
// Author:		Holly Eaton
// Description:	Program that simulates a process scheduler using a simplified multilevel feedback queue.

#ifndef PROCESS_SCHEDULER_SIMULATION_H
#define PROCESS_SCHEDULER_SIMULATION_H

#include <queue>
#include "Process.h"

using namespace std;

class ProcessSchedulerSimulation
{
public:
	ProcessSchedulerSimulation();
	void runScheduler();

private:
	queue<Process> getInputFile();
	Process createProcessObject(int priority, int mReqRuntime);
	void printFinishedProcessInfo(Process thisProcess);
};

#endif
