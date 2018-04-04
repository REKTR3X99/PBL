

//Currently in works,  need to develop a way for thread creation in Linux
#if (defined _WIN32 || defined _WIN64)

#include <Windows.h>
#include <process.h>
#include <conio.h>
#elif defined __linux__

#include <unistd.h>
#include <pthread.h>

#endif


#include <stdio.h>
#include <stdlib.h>

#include "BasicCalc.h"


#pragma warning (disable :4996) //disabling warning for safe function declarations
#pragma warning (disable :6031) //disabling return value ignored for scanf; specifically for x64 build

enum FieldTypes
{
	Parallel_Electric,
	Perpendicular_Electric,
	Projectile_Electric,
	Longitudinal_Magnetic,
	Transverse_Magnetic
};

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
	return status.ullAvailPhys;
}

int main(int argc,char* argv[])
{
	enum FieldType FieldType;
	
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

	if (*RequiredVariables->MemAllocFactor * sizeof(double) > GetAvailableMemory() * 0.90f)
	{
		printf("\nSorry but the value you entered exceeds over 80%% of the available memory.");
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
	Basic_Calculations();//passing values of velocity and platedistance

	Choice: //goto jumper label
	printf("\n1: Parallel ElectricField\n2: Perpendicular Electric Field\n3: Projectile Electric Field");
	scanf("%d", &choice);


	
	switch (choice)
	{
	case 1 :
		//FieldType = Parallel_Electric;
		ElectronMovement_Parallel(Parallel_Electric);
		break;
	case 2 : 
		//FieldType = Perpendicular_Electric;
		printf("\nEnter Plate Width");
		scanf("%f", RequiredVariables->PlateWidth);
		ElectronMovement_Perpendicular(*RequiredVariables->PlateWidth,Perpendicular_Electric);
		break;

	case 3 : 
		//FieldType = Projectile_Electric;
		printf("\nEnter Projection Angle");
		scanf("%f", RequiredVariables->ProjectionAngle);

		ElectronMovement_Projectile(*RequiredVariables->ProjectionAngle, Projectile_Electric);
		break;
	case 4:
		Electron_MAG_Longitudinal(Longitudinal_Magnetic);
		break;


	default : 
		printf("\nThe value entered doesn't match with any of the option, please try again");
		choice = 0;
		goto Choice; //Jump back to choice if the user inputs wrong values
		break;
	}


	
	system("pause");


	return EXIT_SUCCESS;
}
