//#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <process.h>

#include "SIGIL\include\sl.h"
#include "BasicCalc.h"



void Parallel_ElectricField(float, float);
void Projectile_ElectricField(float, float, double, float);
void Perpendicular_ElectricField(float, float, double);

#pragma warning (disable :4996) //disabling warning for safe function declarations


struct Variables
{
	double *PotentialDifference;
	double *PlateDistance;
	double *InitialVelocity;
	float  *Time_Seconds;
	float  *StepSize;
	float  *ProjectionAngle;
} RefVar;

typedef struct ArgumentList
{
	int WindowWidth; 
	int WindowHeight;
	char Title;
	int FullScreen; 
} *PMyData, MyData;

int main(int argc,char* argv[])
{
	DWORD ThreadID;
	PMyData ArgumentList;
	ArgumentList = (PMyData)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MyData)); // Allocating Data for argument List;

	ArgumentList->WindowWidth = 500;
	ArgumentList->WindowHeight = 500;
	ArgumentList->Title = 'P';
	ArgumentList->FullScreen = 0;
	
	
	
	
	//HANDLE thread_Handle = CreateThread(
	//	NULL,  //Will use Default Security Attributes;
	//	0,		//Use Default Stack Size
	//	slWindow,	//SlWindow to reneder the GUI
	//	ArgumentList,//Passing Argument list as a structure
	//	0,	//default creation flags
	//	&ThreadID	//Thread ID for identifying
	//);
	
	
	struct Variables *RequiredVariables		 = (struct Variables *)malloc(sizeof(struct Variables));

	//struct Variables RequiredVariables;
	RequiredVariables->PotentialDifference     = (double *)malloc(sizeof(double));
	RequiredVariables->PlateDistance		   = (double *)malloc(sizeof(double));
	RequiredVariables->InitialVelocity		   = (double *)malloc(sizeof(double));
	RequiredVariables->Time_Seconds			   = (float  *)malloc(sizeof(float ));
	RequiredVariables->StepSize				   = (float  *)malloc(sizeof(float ));
	RequiredVariables->ProjectionAngle =		 (float  *)malloc(sizeof(int   ));
	
	int choice;

#pragma region Input Section
	/*
	Note 1: All the units should be in their standard units
	

	Note 2 : Step Size is the update interval between the calculations.
	*/

	printf("\nEnter the values in their standard units");


	printf("\nEnter the Potential Difference between the plates");
	scanf("%lf", RequiredVariables->PotentialDifference); // In volts 

	printf("\nEnter the distance between the plate distance");
	scanf("%lf",RequiredVariables->PlateDistance); // In meters
	
	printf("\nEnter the Initial Velocity of the electron");
	scanf("%lf", RequiredVariables->InitialVelocity);

	printf("\nEnter the time you want to simulate for");
	scanf("%f",RequiredVariables->Time_Seconds);

	printf("\nEnter the step size");
	scanf("%f", RequiredVariables->StepSize); // stupid issue of not seeing that it was using **float has been resolved
#pragma endregion


	//Function calls for basic math
	Basic_Calculations(*RequiredVariables->PotentialDifference, *RequiredVariables->PlateDistance);//passing values of velocity and platedistance
	


	printf("\n1: Parallel ElectricField\n2: Perpendicular Electric Field\n3: Projectile Electric Field");
	scanf("%d", &choice);


	switch (choice)
	{
	case 1 :
		Parallel_ElectricField(*RequiredVariables->StepSize, *RequiredVariables->Time_Seconds);
		break;
	case 2 : 
		Perpendicular_ElectricField(*RequiredVariables->StepSize, *RequiredVariables->Time_Seconds,*RequiredVariables->InitialVelocity);
		break;

	case 3 : 
		printf("\nEnter Projection Angle");
		scanf("%f", RequiredVariables->ProjectionAngle);
		Projectile_ElectricField(*RequiredVariables->StepSize,*RequiredVariables->Time_Seconds, *RequiredVariables->InitialVelocity,*RequiredVariables->ProjectionAngle);
		break;

	default : 
		return  EXIT_FAILURE;
		break;
	}



	//Freeing Allocating memory
	free(RequiredVariables->StepSize); 
	free(RequiredVariables->InitialVelocity);
	free(RequiredVariables->PotentialDifference);
	free(RequiredVariables->PlateDistance);
	free(RequiredVariables);
	system("pause");
	//exit(0);
	

}

void Parallel_ElectricField(float StepSize, float Time_Seconds)
{

	ElectronMovement_Parallel(Time_Seconds, StepSize);
}

void Projectile_ElectricField(float StepSize, float Time_Seconds, double InitialVelocity,float ProjectionAngle)
{
	ElectronMovement_Projectile(InitialVelocity, ProjectionAngle, Time_Seconds, StepSize);
}

void Perpendicular_ElectricField(float StepSize, float Time_Seconds, double InitialVelocity)
{

	ElectronMovement_Perpendicular(InitialVelocity, Time_Seconds, StepSize);

}