// Program:		Process Que Simulation
// Author:		Holly Eaton
// Description:	Program that simulates a process scheduler using a simplified multilevel feedback queue.

#include <iostream>
#include "ProcessSchedulerSimulation.h"

using namespace std;

void main()
{
	bool notDone = true;
	char choice;
	char closeWindow;

	while (notDone)
	{
		ProcessSchedulerSimulation queUpTheQ;
		queUpTheQ.runScheduler();
		cout << "\n\nWould you like to run another process? ";
		cin >> choice;
		if (choice == 'n' || choice == 'N')
			notDone = false;
		cin.get();
	}
	cout << endl << "Thanks for trying the process scheduler...";
	cin.get();
}