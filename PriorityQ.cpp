// Program:		Process Que Simulation
// Author:		Holly Eaton
// Description:	Program that simulates a process scheduler using a simplified multilevel feedback queue.

#include <queue>
#include "Process.h"
#include "PriorityQ.h"
#include "ProcessSchedulerSimulation.h"

PriorityQ::PriorityQ()
{

}

//===================================================================================================================================
//Function Name: deQue
//
//Description: takes the next Process object from the queue with the most priority
//
//Return: the process object being dequed
//===================================================================================================================================
Process PriorityQ::deQue()
{
	Process temp;
	int i=0;
	do
	{
		if (!arrayOfPriorityQs[i].empty())
		{
			temp = arrayOfPriorityQs[i].front();
			arrayOfPriorityQs[i].pop();
			return temp;
		}
		i++;
	}
	while (i<=HIGHEST_PRIORITY);

	return temp;
}

//===================================================================================================================================
//Function Name: enQue
//
//Description: puts a process object in the queue at the appropriate array index
//
//Arguments: (I) thisProcess - the process object being enqueued
//===================================================================================================================================
void PriorityQ::enQue(Process thisProcess)
{
	arrayOfPriorityQs[thisProcess.mCurrentPriority].push(thisProcess);
}

//===================================================================================================================================
//Function Name: areQuesEmpty
//
//Description: Checks to see if there are any objects in the array of queues
//
//Return: True - there are objects still in the array of queues
//			False - there are no objects in the array of queues
//===================================================================================================================================
bool PriorityQ::areQuesEmpty()
{
	int counter=0;
	for (int i=0; i<=HIGHEST_PRIORITY; i++)
	{
		if (arrayOfPriorityQs[i].size() > 0)
			counter++;
	}
	if (counter > 0)
		return false;
	return true;
}