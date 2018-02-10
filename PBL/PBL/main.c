#include <stdio.h>
#include <conio.h>
#include "BasicCalc.h"
#include <Windows.h>
 


#pragma warning (disable :4996) //disabling warning for safe function declarations
void Perpendicular_ElectricField(float, unsigned long int);

int main()
{
	double *PotentialDifference = (double *)malloc(sizeof(double)); //allocating memory for velocity variable
	double *PlateDistance = (double *)malloc(sizeof(double)); //allocating memory for PlateDistance
	unsigned long int *Time_Seconds = (unsigned long int *)malloc(sizeof(unsigned long int)); //allocating memory for Time
	float *StepSize = (float *)malloc(sizeof(float)); //assinging memory for Step Size
	double *InitialVelocity = (double *)malloc(sizeof(double));
	//Displaying message to user

	/*
	Note 1: Units : 
	Potential Difference : Volts 
	Plate Distance : Meters 
	Initial Velocity : Meters/second
	Time : Seconds 
	

	Note 2 : Step Size is the update interval between the calculations.
	*/
	printf("\nEnter the Potential Difference between the plates");
	scanf("%lf",PotentialDifference); // In volts 

	printf("\nEnter the distance between the plate distance");
	scanf("%lf",PlateDistance); // In meters
	
	printf("\nEnter the Initial Velocity of the electron");
	scanf("%lf", InitialVelocity);

	printf("\nEnter the time you want to simulate for");
	scanf("%ld", Time_Seconds);

	printf("\nEnter the step size");
	scanf("%f", StepSize);

	//Function calls for basic math
	Basic_Calculations(*PotentialDifference, *PlateDistance);//passing values of velocity and platedistance
	Velocity_Disp_Calc(*InitialVelocity, *Time_Seconds);


	//Freeing Allocating memory
	free(PotentialDifference);
	free(PlateDistance);
	free(InitialVelocity);

	

	Perpendicular_ElectricField(*StepSize, *Time_Seconds);

	free(StepSize);

	
	system("pause");

}

void Perpendicular_ElectricField(float StepSize, unsigned long int Time_Seconds)
{
	unsigned int count = 0;
	
	while (count <= Time_Seconds)
	{
		ElectronMovement_Perpendicular(Velocity_Electron, count);
		Sleep(StepSize * 1000);
		count++;
	}
	
}