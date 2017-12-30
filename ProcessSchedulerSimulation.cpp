// Program:		Process Que Simulation
// Author:		Holly Eaton
// Description:	Program that simulates a process scheduler using a simplified multilevel feedback queue.

#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include "Process.h"
#include "PriorityQ.h"
#include "ProcessSchedulerSimulation.h"

using namespace std;

//===================================================================================================================================
//Function Name: ProcessSchedulerSimulation
//
//Description: Default constructor
//===================================================================================================================================
ProcessSchedulerSimulation::ProcessSchedulerSimulation()
{

}

//===================================================================================================================================
//Function Name: getInputFile
//
//Description: Prompts the user for a file to be processed. Verifies the file and the data in the file.
//				Puts the data in a queue of process objects.
//
//Return: the queue of process objects
//===================================================================================================================================
queue<Process> ProcessSchedulerSimulation::getInputFile()
{
	ifstream inputFile;
	string inputFileName;
	int priority;
	int mReqRuntime;
	queue<Process> temp;

	cout << "\nWelcome to the Process Scheduler\n\nPlease Enter one of the following four valid file names:\n\n(data.txt, data1.txt, data2.txt or data3.txt)\n>";
	getline(cin, inputFileName);

	inputFile.open(inputFileName);
	while (!inputFile || inputFile.peek() == EOF)
	{
		cout << "\nThe file name you entered is incorrect or the file contains no valid data.\n";
		cout << "Please try again\n\nEnter a valid file name:\n>";
		getline(cin, inputFileName);
		inputFile.open(inputFileName);
	}

	cout << endl << endl;

	//load file to be processed
	bool stillGoodData = true;
	while (stillGoodData && inputFile.peek() != EOF && inputFile >> priority && inputFile.peek() != EOF && inputFile >> mReqRuntime)
	{
		if (priority >= 0 && priority <= HIGHEST_PRIORITY && mReqRuntime >= 0)
			temp.push(createProcessObject(priority, mReqRuntime));
		else
		{
			cout << "The input file contains values which are invalid.\nPlease check the values in the file and try again.\n";
			stillGoodData = false;
		}
	}
	inputFile.close();
	return temp;
}
//===================================================================================================================================
//Function Name: createProcessObject
//
//Description: Makes a process object
//
//Arguments:(I) priority - the initial priority of this process object
//			(I) mReqRuntime - the required Required Runtime of this process object
//
//Return: the created process object
//===================================================================================================================================
Process ProcessSchedulerSimulation::createProcessObject(int priority, int mReqRuntime)
{
	Process thisProcess(priority, mReqRuntime);
	return thisProcess;
}

//===================================================================================================================================
//Function Name: runScheduler
//
//Description: Checks to see if a new process needs to be added to the array of queues, adds a new process (if exists)
//				Checks to see if current process is finished or needs to be returned to the array of queues at it's new priority
//				Checks to see if a process in the array of queues needs to be given processor time, deques the process (if exists)
//				Determines when the next scheduled event is to occur and advances to that tick
//
//===================================================================================================================================
void ProcessSchedulerSimulation::runScheduler()
{
	int timeOfNextEvent = 0;
	int newProcessArrivesTime = 0;
	int nextProcessTime = 0;
	int id = 0;
	queue<Process> futureProcessQueue = getInputFile();
	PriorityQ processesToBeRun;
	Process processCpuIsRunning;
	int processesYetToRun = futureProcessQueue.size();

	while (!futureProcessQueue.empty() || !processesToBeRun.areQuesEmpty() || processesYetToRun > 0)
	{
		//see if it is time to add a new process
		if (timeOfNextEvent == newProcessArrivesTime)
		{
			if (!futureProcessQueue.empty())
			{
				futureProcessQueue.front().mStartTime = newProcessArrivesTime;
				futureProcessQueue.front().mPID = id++;
				processesToBeRun.enQue(futureProcessQueue.front());
				futureProcessQueue.pop();
			}
			newProcessArrivesTime += NEW_PROCESS_TICK;
		}

		//see if it is time to start a new process
		if (timeOfNextEvent == nextProcessTime)
		{
			if (processCpuIsRunning.mPID != -1) //first time
			{
				if (processCpuIsRunning.mTicksLeftOnThisProcess <= TICK)
				{
					processCpuIsRunning.mTicksLeftOnThisProcess = 0;
					processCpuIsRunning.mIsFinished = true;
				}
				else
				{
					processCpuIsRunning.mTicksLeftOnThisProcess -= TICK;
					if (processCpuIsRunning.mCurrentPriority < HIGHEST_PRIORITY)
						processCpuIsRunning.mCurrentPriority++;
				}

				//see if the current process is finished or if it needs to be put back in the queue
				if (processCpuIsRunning.mIsFinished)
				{
					processCpuIsRunning.mFinishTime = nextProcessTime;
					processesYetToRun--;
					printFinishedProcessInfo(processCpuIsRunning);
					processCpuIsRunning.mPID = -1;
				}
				else
				{
					processesToBeRun.enQue(processCpuIsRunning);
					processCpuIsRunning.mPID = -1;
				}
			}
			//get the next process to be run (if any)
			if (!processesToBeRun.areQuesEmpty())
			{
				processCpuIsRunning = processesToBeRun.deQue();

				if (processCpuIsRunning.mTicksLeftOnThisProcess <= TICK)
					nextProcessTime += processCpuIsRunning.mTicksLeftOnThisProcess;
				else nextProcessTime += TICK;
			}
			else
				nextProcessTime = newProcessArrivesTime;
		}

		if (newProcessArrivesTime <= nextProcessTime)
			timeOfNextEvent = newProcessArrivesTime;
		else
			timeOfNextEvent = nextProcessTime;
	}//closes while loop
}

//===================================================================================================================================
//Function Name: printFinishedProcessInfo
//
//Description: Displays information about the completed process object to the console window
//
//Arguments: (I) thisProcess - the finished process
//			
//===================================================================================================================================
void ProcessSchedulerSimulation::printFinishedProcessInfo(Process thisProcess)
{
	cout << "\n\nProcess Finished\nPID : " << thisProcess.mPID << 
		"\nInitial Piority : " << thisProcess.mInitialPriority << 
		"\nTotal Run Time Required For Process : " << thisProcess.mReqRuntime << 
		"\nFinal Priority : " << thisProcess.mCurrentPriority << 
		"\nStart Time : " << thisProcess.mStartTime <<
		"\nEnd Time : " << thisProcess.mFinishTime <<
		"\nTotal Time Used to Complete Process : " << thisProcess.mFinishTime - thisProcess.mStartTime;
}