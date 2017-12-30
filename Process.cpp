// Program:		Process Que Simulation
// Author:		Holly Eaton
// Description:	Program that simulates a process scheduler using a simplified multilevel feedback queue.

#include <iostream>
#include "Process.h"

using namespace std;
//===================================================================================================================================
//Function Name: Process
//
//Description: Default constructor
//===================================================================================================================================
Process::Process()
{
	mPID = -1;
	mCurrentPriority = 0;
	mInitialPriority = 0;
	mReqRuntime = 0;
	mTicksLeftOnThisProcess = 0;
	mStartTime = 0;
	mFinishTime = 0;
	mIsFinished = false;
}

//===================================================================================================================================
//Function Name: Process
//
//Description: Overloaded default constructor
//===================================================================================================================================
Process::Process(int processPriority, int processReqRunTime)
{
	mCurrentPriority = processPriority;
	mInitialPriority = processPriority;
	mReqRuntime = processReqRunTime;
	mTicksLeftOnThisProcess = processReqRunTime;
	mIsFinished = false;
}