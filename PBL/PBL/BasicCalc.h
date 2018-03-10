#pragma once
#pragma warning (disable : 6011)


#if defined _WIN32 || defined _WIN64

#include <Windows.h>
#include <process.h>
#include <conio.h>
#elif  defined __linux__
#include <unistd.h>
#endif


#include <stdio.h>
#include <math.h> 

#include "Plotter.h"

#pragma warning (disable : 4700)

#define ELECTRON_MASS 9.109E-31
#define ELECTRON_ENERGY 1.6E-19

double Energy_Electron = 0.0f; 
double Force_Electron = 0.0f;
double Acceleration_Electron = 0.0f;


struct ElectricField {
	struct Parallel
	{
		double X_Component;
	}Parallel;

	struct Perpendicular {

		double VerticalDisplacement_Y;
		double HorizontalDisplacement_X;
		double VerticalDisplacement_Leaving;
		const double ElectronPlateWidth_L;
	}Perpendicular;

	struct Projection {
		double HorizontalComponent_X;
		double VerticalComponent_Y;
		double MaxVerticalDisplacement;
		double TimeTakenForMaxVerticalDisplacement;
		double TimeOfFlightOfElectron;
		double RangeOfElectron;
	}Projection;

	struct Arrays
	{
		double *Xcomponent;
		double *Ycomponent;
	} CompArray;

	 struct RVar
	{
		 double PotentialDifference;
		 double InitialVelocity;
		 double PlateDistance;
		 float TimeEpoch;
		 float StepSize;
	}Var;

}EField, *EField_P;

struct Miscelaneous
{
	float count;
	unsigned long int MemAllocFactor;
	unsigned long int index;
}Misc;

void Assigner(double *PotentialDifference_P, double *InitialVelocity_P, double *PlateDistance_P, float *Time_Seconds_P, float *Step_Size_P, unsigned long int *MemAllocFactor_P)
{
	EField.Var.PotentialDifference = *PotentialDifference_P;
	EField.Var.InitialVelocity = *InitialVelocity_P;
	EField.Var.PlateDistance = *PlateDistance_P;
	EField.Var.TimeEpoch = *Time_Seconds_P;
	EField.Var.StepSize = *Step_Size_P;
	Misc.MemAllocFactor = *MemAllocFactor_P;


	//Freeing Memory after assinging it
	free(PotentialDifference_P);
	free(InitialVelocity_P);
	free(PlateDistance_P);
	free(Time_Seconds_P);
	free(Step_Size_P);
	free(MemAllocFactor_P);
}

#pragma region Basic Calculations
	void Basic_Calculations(double PotentialDifference, double PlateDistance)
	{
		Energy_Electron = PotentialDifference / PlateDistance; //Energy of the electron
		Force_Electron = -1 * ELECTRON_ENERGY * Energy_Electron; //Force of the electorn on plate B ( The plate form which the electron enters into the field)
		Acceleration_Electron = fabs(Force_Electron) / ELECTRON_MASS; //Acceleration of the electron: negating by -1 to get a positive result for acceleration

		printf("\n%g", Energy_Electron);
		printf("\n%g", Force_Electron);
		printf("\n%g", Acceleration_Electron);

	}
#pragma endregion



	void ElectronMovement_Parallel()
	{
		float count = Misc.count = 0;
		int Index = Misc.index = 0;
		float Time = EField.Var.TimeEpoch;
		float StepSize = EField.Var.StepSize;
		unsigned int mem = Misc.MemAllocFactor;

		
		EField.CompArray.Xcomponent = (double *)calloc(mem, sizeof(double));
		//printf("\nsize : %ld", (int)sizeof(EField.CompArray.Xcomponent));
		

		while (count <= Time)
		{
			EField.Parallel.X_Component = fabs(Force_Electron) / (2 * ELECTRON_MASS) * pow(count, 2);
			
			EField.CompArray.Xcomponent[Index] = EField.Parallel.X_Component;
			//printf("\nX Main Loop : %g", EField.Parallel.X_Component);
			count += StepSize;
			Index++;
		}

		//for (unsigned int i = 0; i <= Misc.MemAllocFactor-1; i++)
		//{
		//	printf("\nX = %g", EField.CompArray.Xcomponent[i]);
		//}	

		PlotAssigner(EField.CompArray.Xcomponent, EField.CompArray.Ycomponent);// Calls assigning thread
	}
	void ElectronMovement_Perpendicular(float PlateWidth)
	{		
		//struct ElectricField *EField = (struct ElectricField *)malloc(sizeof(struct ElectricField));
		

		Misc.count = 0;
		Misc.index = 0;


		EField.CompArray.Xcomponent = (double *)calloc(Misc.MemAllocFactor, sizeof(double));
		EField.CompArray.Ycomponent = (double *)calloc(Misc.MemAllocFactor, sizeof(double));

		while (Misc.count <= EField.Var.TimeEpoch)
		{
			EField.Perpendicular.HorizontalDisplacement_X = EField.Var.InitialVelocity * Misc.count;
			EField.Perpendicular.VerticalDisplacement_Y = -1 * (Force_Electron / 2 * ELECTRON_MASS) * pow(Misc.count,2);
			EField.Perpendicular.VerticalDisplacement_Leaving = (ELECTRON_ENERGY / 2 * ELECTRON_MASS) * Energy_Electron * (PlateWidth / pow(EField.Var.InitialVelocity, 2));
			
			
			EField.CompArray.Xcomponent[Misc.index] = EField.Perpendicular.HorizontalDisplacement_X;
			EField.CompArray.Ycomponent[Misc.index] = EField.Perpendicular.VerticalDisplacement_Y;
			Misc.index++;
			Misc.count += EField.Var.StepSize;
			
			printf("\nRunning");
		}
		PlotAssigner(EField.CompArray.Xcomponent, EField.CompArray.Ycomponent);
	}

	void ElectronMovement_Projectile(float ProjectionAngle_Electron)
	{
		//struct ElectricField *EField = (struct ElectricField *)malloc(sizeof(struct ElectricField));
		
		
		Misc.count = 0;
		Misc.index = 0;
		

		EField.CompArray.Xcomponent = (double *)calloc(Misc.MemAllocFactor, sizeof(double));
		EField.CompArray.Ycomponent = (double *)calloc(Misc.MemAllocFactor, sizeof(double));

		double *Vx0 = (double *)malloc(sizeof(double));
		double *Vy0 = (double *)malloc(sizeof(double));


		*Vx0 = EField.Var.InitialVelocity * cos(ProjectionAngle_Electron);
		*Vy0 = EField.Var.InitialVelocity * sin(ProjectionAngle_Electron) * EField.Var.TimeEpoch;

		while (Misc.count <= EField.Var.TimeEpoch)
		{
			
			EField.Projection.HorizontalComponent_X = *Vx0 * Misc.count;
			EField.Projection.VerticalComponent_Y = *Vy0 + (0.5 * Acceleration_Electron * pow(Misc.count, 2));


			EField.CompArray.Xcomponent[Misc.index] = EField.Projection.HorizontalComponent_X;
			EField.CompArray.Ycomponent[Misc.index] = EField.Projection.VerticalComponent_Y;
			Misc.index++;
			Misc.count += EField.Var.StepSize;

			printf("\nX0 = %g\t Y0 = %g",*Vx0,*Vy0);
		}
		
		free(Vx0);
		free(Vy0);
		
		printf("\n\n");
		PlotAssigner(EField.CompArray.Xcomponent, EField.CompArray.Ycomponent);
		
	
	}

