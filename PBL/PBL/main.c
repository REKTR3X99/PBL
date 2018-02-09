#include <stdio.h>
#include <conio.h>
#include "BasicCalc.h"

#pragma warning (disable :4996)

int main()
{
	double *Velocity = (double *)malloc(sizeof(double)); //allocating memory for velocity variable
	double *PlateDistance = (double *)malloc(sizeof(double)); //allocating memory for PlateDistance

	//Displaying message to user
	printf("\nEnter the Velocity of the electron and the plate distance");
	scanf("%lf",Velocity);
	scanf("%lf",PlateDistance);

	//passing values of velocity and platedistance
	BasicCalculations(*Velocity, *PlateDistance);
	
	//Freeing Allocating memory
	free(Velocity);
	free(PlateDistance);


	system("pause");

}