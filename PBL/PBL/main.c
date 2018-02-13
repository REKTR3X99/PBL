#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "BasicCalc.h"
#include <Windows.h>



#pragma warning (disable :4996) //disabling warning for safe function declarations
void Perpendicular_ElectricField(float, float);
void Projectile_ElectricField(float, float);



int main(void)
{


	double *PotentialDifference = (double *)malloc(sizeof(double)); //allocating memory for velocity variable
	double *PlateDistance = (double *)malloc(sizeof(double)); //allocating memory for PlateDistance
	float *Time_Seconds = (float *)malloc(sizeof(float)); //allocating memory for Time
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
	scanf("%f", Time_Seconds);

	printf("\nEnter the step size");
	scanf("%f", StepSize);

	//Function calls for basic math
	Basic_Calculations(*PotentialDifference, *PlateDistance);//passing values of velocity and platedistance
	Velocity_Disp_Calc(*InitialVelocity, *Time_Seconds);


	//Freeing Allocating memory
	free(PotentialDifference);
	free(PlateDistance);
	//free(InitialVelocity);

	

	//Perpendicular_ElectricField(*StepSize, *Time_Seconds,*InitialVelocity);
	Projectile_ElectricField(*StepSize, *Time_Seconds,*InitialVelocity);

	free(StepSize);

	
	system("pause");

}

void Perpendicular_ElectricField(float StepSize, float Time_Seconds,double InitialVelocity)
{
	float count = 0;
	
	while (count <= Time_Seconds)
	{
		ElectronMovement_Perpendicular(Velocity_Electron, count);
		//Sleep(StepSize * 1000); //for real-time simulation
		count+=StepSize;
	}
	
}

void Projectile_ElectricField(float StepSize, float Time_Seconds, double InitialVelocity)
{
	float count = 1;
	float ProjectionAngle_Electron;
	printf("\nEnter the projection angle");
	scanf("%f", &ProjectionAngle_Electron);


	while (count <= Time_Seconds)
	{
		ElectronMovement_Projectile(InitialVelocity, ProjectionAngle_Electron, count);
		//Sleep(StepSize * 1000); //for realtime simulation
		count += StepSize;
	}
}