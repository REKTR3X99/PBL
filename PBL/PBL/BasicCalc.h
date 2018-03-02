#pragma once
#include <stdio.h>
#include <conio.h>
#include <math.h> 
#include <Windows.h>
#include "Plotter.h"



#define ELECTRON_MASS 9.109E-31
#define ELECTRON_ENERGY 1.6E-19

double Energy_Electron = 0.0f; 
double Force_Electron = 0.0f;
double Acceleration_Electron = 0.0f;


struct ElectricField {
	struct Parallel
	{
		double Horizontal_X_Component;
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

	struct Component
	{
		double *Xcomponent;
		double *Ycomponent;
	} RequiredVaraibles;
};

struct Miscelaneous
{
	float count;
	unsigned int MemAllocFactor;
	unsigned int index;
}Misc;


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



	void ElectronMovement_Parallel(float Time_SecondsFromEpoch,float StepSize)
	{
		struct ElectricField EField;

		Misc.count = 1;
		Misc.index = 0;
		Misc.MemAllocFactor = round(Time_SecondsFromEpoch / StepSize);
		
		
		EField.RequiredVaraibles.Xcomponent = (double *)calloc(Misc.MemAllocFactor, sizeof(double));
		

		while (Misc.count <= Time_SecondsFromEpoch)
		{
			EField.Parallel.Horizontal_X_Component = fabs(Force_Electron) / (2 * ELECTRON_MASS) * pow(Misc.count, 2);
			*EField.RequiredVaraibles.Xcomponent = EField.Parallel.Horizontal_X_Component;
			printf("\nX = %g", EField.Parallel.Horizontal_X_Component);
			Misc.count += StepSize;
		}

		
	}


	
	void ElectronMovement_Perpendicular(double InitialVelocity_Electron,  float Time_Epoch,float StepSize,float PlateWidth)
	{		
		struct ElectricField EField;
		

		Misc.count = 0;
		Misc.index = 0;
		Misc.MemAllocFactor = Time_Epoch / StepSize;

		EField.RequiredVaraibles.Xcomponent = (double *)calloc(Misc.MemAllocFactor, sizeof(double));
		EField.RequiredVaraibles.Ycomponent = (double *)calloc(Misc.MemAllocFactor, sizeof(double));

		while (Misc.count <= Time_Epoch)
		{
			EField.Perpendicular.HorizontalDisplacement_X = InitialVelocity_Electron * Misc.count;
			EField.Perpendicular.VerticalDisplacement_Y = -1 * (Force_Electron / 2 * ELECTRON_MASS) * pow(Misc.count,2);
			EField.Perpendicular.VerticalDisplacement_Leaving = (ELECTRON_ENERGY / 2 * ELECTRON_MASS) * Energy_Electron * (PlateWidth / pow(InitialVelocity_Electron, 2));
			
			
			EField.RequiredVaraibles.Xcomponent[Misc.index] = EField.Perpendicular.HorizontalDisplacement_X;
			EField.RequiredVaraibles.Ycomponent[Misc.index] = EField.Perpendicular.VerticalDisplacement_Y;
			Misc.index++;
			Misc.count += StepSize;
		
		}
		
	}

	void ElectronMovement_Projectile(double InitialVelocity_Electron, float ProjectionAngle_Electron,float Time_Seconds,float StepSize)
	{
		struct ElectricField EField;

		Misc.count = 0;
		Misc.index = 0;
		Misc.MemAllocFactor = Time_Seconds / StepSize;
		
		EField.RequiredVaraibles.Xcomponent = (double *)calloc(Misc.MemAllocFactor, sizeof(double));
		EField.RequiredVaraibles.Ycomponent = (double *)calloc(Misc.MemAllocFactor, sizeof(double));
		
		double *Vx0 = (double *)malloc(sizeof(double));
		double *Vy0 = (double *)malloc(sizeof(double));
		

		*Vx0 = InitialVelocity_Electron * sin(ProjectionAngle_Electron);
		*Vy0 = InitialVelocity_Electron * cos(ProjectionAngle_Electron) * Time_Seconds;

		while (Misc.count <= Time_Seconds)
		{
			EField.Projection.HorizontalComponent_X = *Vx0 * Misc.count;
			EField.Projection.VerticalComponent_Y = *Vy0 + (0.5 * Acceleration_Electron * pow(Misc.count, 2));


			EField.RequiredVaraibles.Xcomponent[Misc.index] = EField.Projection.HorizontalComponent_X;
			EField.RequiredVaraibles.Ycomponent[Misc.index] = EField.Projection.VerticalComponent_Y;
			Misc.index++;
			Misc.count += StepSize;
		}

		

		//HANDLE PlotterThread = CreateThread(NULL, 0, GenerateCoordinates, XComponentArray, YComponentArray, NULL, NULL);
		free(Vx0);
		free(Vy0);

		printf("\n\n");
		//printf("\nHorizontal Componenet : %g\nVertical Component :  %g\nTime Since Epoch : %g", HorizontalComponent_X_ElectrincField_Projection, VerticalCompoenet_Y_ElectricField_Projection, Time_Seconds);

		//MaxVerticalDisplacement_Y_ElectricField_Projection = ((pow(InitialVelocity_Electron, 2)) * (pow(sin(ProjectionAngle_Electron), 2))) / 2 * Acceleration_Electron;
		//TimeTakenForMaxVerticalDisplacement_ElectricField_Projection = (InitialVelocity_Electron * sin(ProjectionAngle_Electron)) / Acceleration_Electron;
		//
		//
		//TimeOfFlightOfElectron_ElectricField_Projection = 2 * TimeTakenForMaxVerticalDisplacement_ElectricField_Projection;
		//RangeOfElectron_ElectricField_Projection = (2 * sin(ProjectionAngle_Electron) * cos(ProjectionAngle_Electron) * pow(InitialVelocity_Electron, 2) ) / Acceleration_Electron;
	
	}