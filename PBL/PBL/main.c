#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <process.h>

#include "SIGIL\include\sl.h"
#include "BasicCalc.h"


#pragma warning (disable :4996) //disabling warning for safe function declarations
#pragma warning (disable :6031) //disabling return value ignored for scanf; specifically for x64 build

struct Variables
{
	double *PotentialDifference;
	double *PlateDistance;
	double *InitialVelocity;
	float  *Time_Seconds;
	float  *StepSize;
	float  *ProjectionAngle;
	float  *PlateWidth;
	unsigned int *MemAllocFactor;
};


//To get total amount of available physical memory on system
unsigned long long GetAvailableMemory()
{
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	//printf("\nLength : %ld", status.ullTotalPhys);
	return status.ullTotalPhys;
}




int main(int argc,char* argv[])
{
	
	struct Variables *RequiredVariables		   = (struct Variables *)malloc(sizeof(struct Variables));

	RequiredVariables->PotentialDifference     = (double *)malloc(sizeof(double));
	RequiredVariables->PlateDistance		   = (double *)malloc(sizeof(double));
	RequiredVariables->InitialVelocity		   = (double *)malloc(sizeof(double));
	RequiredVariables->Time_Seconds			   = (float  *)malloc(sizeof(float ));
	RequiredVariables->StepSize				   = (float  *)malloc(sizeof(float ));
	RequiredVariables->ProjectionAngle		   = (float  *)malloc(sizeof(int   ));
	RequiredVariables->PlateWidth			   = (float  *)malloc(sizeof(float ));
	RequiredVariables->MemAllocFactor = (unsigned int *)malloc(sizeof(unsigned int));
	int choice;

#pragma region Input Section
	/*
	Note 1: All the units should be in their standard units
	

	Note 2 : Step Size is the update interval between the calculations.
	*/

	printf("\nEnter the values in their standard units");


	printf("\nEnter the Potential Difference between the plates");
	scanf("%lf",RequiredVariables->PotentialDifference); // In volts 

	printf("\nEnter the distance between the plate distance");
	scanf("%lf",RequiredVariables->PlateDistance); // In meters
	
	printf("\nEnter the Initial Velocity of the electron");
	scanf("%lf", RequiredVariables->InitialVelocity);

	printf("\nEnter the time you want to simulate for");
	scanf("%f",RequiredVariables->Time_Seconds);

	printf("\nEnter the step size");
	scanf("%f", RequiredVariables->StepSize); // stupid issue of not seeing that it was using **float has been resolved
#pragma endregion



	//Checking if the the memory to be allocated is greater than the available memory 
	//if yes -> program exits
	*RequiredVariables->MemAllocFactor = *RequiredVariables->Time_Seconds / *RequiredVariables->StepSize;

	if (*RequiredVariables->MemAllocFactor * sizeof(double) > GetAvailableMemory() * 0.7)
	{
		printf("\nSorry but the value you entered exceeds over 70%% of the available memory.");
		printf("\nThe program will now exit");		  
		return -1;
	}

	//Assigner caller
	Assigner(RequiredVariables->PotentialDifference,
		RequiredVariables->InitialVelocity,
		RequiredVariables->PlateDistance,
		RequiredVariables->Time_Seconds,
		RequiredVariables->StepSize,
		RequiredVariables->MemAllocFactor);

	//Function calls for basic math
	Basic_Calculations(*RequiredVariables->PotentialDifference, *RequiredVariables->PlateDistance);//passing values of velocity and platedistance


	printf("\n1: Parallel ElectricField\n2: Perpendicular Electric Field\n3: Projectile Electric Field");
	scanf("%d", &choice);


	switch (choice)
	{
	case 1 :
		ElectronMovement_Parallel();
		break;
	case 2 : 
		printf("\nEnter Plate Width");
		scanf("%f", RequiredVariables->PlateWidth);
		ElectronMovement_Perpendicular(*RequiredVariables->PlateWidth);
		break;

	case 3 : 
		printf("\nEnter Projection Angle");
		scanf("%f", RequiredVariables->ProjectionAngle);

		ElectronMovement_Projectile(*RequiredVariables->ProjectionAngle);
		break;

	default : 
		return  EXIT_FAILURE;
		break;
	}



	
	
	
	
	
	
	
	system("pause");
}
