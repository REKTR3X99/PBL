#include <stdio.h>
#include <conio.h>
#include "BasicCalc.h"

#pragma warning (disable :4996) //disabling warning for safe function declarations

int main()
{
	double *PotentialDifference = (double *)malloc(sizeof(double)); //allocating memory for velocity variable
	double *PlateDistance = (double *)malloc(sizeof(double)); //allocating memory for PlateDistance
	unsigned long int *Time_Seconds = (unsigned long int *)malloc(sizeof(unsigned long int)); //allocating memory for Time
	//Displaying message to user

	/*
	Note : Potential Difference is calculated in Volts and the distance in meters
	*/
	printf("\nEnter the Potential Difference between the plates and the plate distance");
	scanf("%lf",PotentialDifference); // In volts 
	scanf("%lf",PlateDistance); // In meters

	Basic_Calculations(*PotentialDifference, *PlateDistance);//passing values of velocity and platedistance
	


	printf("\nEnter the time you want to simulate for");
	scanf("%lf", Time_Seconds);


	//Freeing Allocating memory
	free(PotentialDifference);
	free(PlateDistance);

	Velocity_Disp_Calc(10.0f, Time_Seconds);

	system("pause");

}