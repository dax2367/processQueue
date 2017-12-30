// Program:		Process Que Simulation
// Author:		Holly Eaton
// Description:	Program that simulates a process scheduler using a simplified multilevel feedback queue.

#ifndef PRIORITY_Q_H
#define PRIORITY_Q_H

#include <queue>
#include "Process.h"

using namespace std;

const int HIGHEST_PRIORITY = 9;
const int TICK = 10;
const int NEW_PROCESS_TICK = 15;

class PriorityQ
{
public:
	PriorityQ();
	Process deQue();
	void enQue(Process thisProcess);
	bool areQuesEmpty();

private:
	queue<Process> arrayOfPriorityQs[HIGHEST_PRIORITY+1];
};

#endif