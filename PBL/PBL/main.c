#include <stdio.h>
#include <conio.h>
#include "BasicCalc.h"
#include <Windows.h>


#pragma warning (disable :4996) //disabling warning for safe function declarations
void Caller(float, unsigned long int);

int main()
{
	double *PotentialDifference = (double *)malloc(sizeof(double)); //allocating memory for velocity variable
	double *PlateDistance = (double *)malloc(sizeof(double)); //allocating memory for PlateDistance
	unsigned long int *Time_Seconds = (unsigned long int *)malloc(sizeof(unsigned long int)); //allocating memory for Time
	float *StepSize = (float *)malloc(sizeof(float)); //assinging memory for Step Size
	//Displaying message to user

	/*
	Note : Potential Difference is calculated in Volts and the distance in meters
	*/
	printf("\nEnter the Potential Difference between the plates and the plate distance");
	scanf("%lf",PotentialDifference); // In volts 
	scanf("%lf",PlateDistance); // In meters

	Basic_Calculations(*PotentialDifference, *PlateDistance);//passing values of velocity and platedistance
	


	printf("\nEnter the time you want to simulate for");
	scanf("%ld", Time_Seconds);


	//Freeing Allocating memory
	free(PotentialDifference);
	free(PlateDistance);

	Velocity_Disp_Calc(10.0, Time_Seconds);


	printf("\nEnter the step size");
	scanf("%f", StepSize);

	Caller(*StepSize, Time_Seconds);

	free(StepSize);


	system("pause");

}

void Caller(float StepSize, unsigned long int Time_Seconds)
{
	int count = 0;
	while (count <= Time_Seconds)
	{
		ElectronMovement_Perpendicular(Velocity_Electron, count);
		Sleep(StepSize * 1000);
		count++;
	}
	
}