// Program:		Process Que Simulation
// Author:		Holly Eaton
// Description:	Program that simulates a process scheduler using a simplified multilevel feedback queue.



#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>

using namespace std;

class Process
{
public:
	Process();
	Process(int processPriority, int processReqRunTime);

	int mPID;
	int mInitialPriority;
	int mReqRuntime;
	int mCurrentPriority;
	int mTicksLeftOnThisProcess;
	int mStartTime;
	int mFinishTime;
	bool mIsFinished;
};

#endif