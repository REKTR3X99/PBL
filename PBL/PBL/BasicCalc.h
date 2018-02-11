#pragma once
#include <stdio.h>
#include <conio.h>
#include <math.h> 
#include <Windows.h>



#define ELECTRON_MASS 9.109E-31
#define ELECTRON_ENERGY 1.6E-19



double Energy_Electron = 0.0f;
double Force_Electron;// = 0.0f;
double Acceleration_Electron = 0.0f;
double Velocity_Electron = 0.0f;
double Displacement_Electron = 0.0f; 
double DistanceTravelled_Electron = 0.0f;
int Time_Epoch = 0;


#pragma region Perpendicular Electric Field
double VerticalDisplacement_Y_ElectricField_Perpendicular;
double HorizontalDisplacement_X_ElectricField_Perpendicular;
double VerticalDisplacement_LeavingElectricField;
const double ElectronPlateWidth_L = 0.5f;
#pragma endregion


#pragma region Electron Prjected at an angle Electric Field
double HorizontalComponent_Y_ElectricField_Projection;
double VerticalCompoenet_Y_ElectricField_Projection;
double MaxVerticalDisplacement_Y_ElectricField_Projection;
double TimeTakenForMaxVerticalDisplacement_ElectricField_Projection;
double TimeOfFlightOfElectron_ElectricField_Projection;
double RangeOfElectron_ElectricField_Projection;
#pragma endregion

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

#pragma region Parallel Electric Field
	void Velocity_Disp_Calc(double InitialVelocity_Electron, unsigned long int Time_SecondsFromEpoch)
	{
		//Note : Add a time function to get the velocity over time
		Velocity_Electron = InitialVelocity_Electron + (Acceleration_Electron * Time_SecondsFromEpoch);
		Displacement_Electron = (InitialVelocity_Electron * Time_SecondsFromEpoch) + (0.5f*Acceleration_Electron * (Time_SecondsFromEpoch*Time_SecondsFromEpoch));

		printf("\n%g\n%g", Velocity_Electron, Displacement_Electron);
	}

#pragma endregion




	void TimeDependedCalcs(unsigned long int Time_SecondsFromEpoch)
	{
		DistanceTravelled_Electron = -1*(Force_Electron) / (2 * ELECTRON_MASS) * pow(Time_SecondsFromEpoch, 2);
	}


	
	void ElectronMovement_Perpendicular(double InitialVelocity_Electron,  int Time_Epoch)
	{
		
			HorizontalDisplacement_X_ElectricField_Perpendicular = InitialVelocity_Electron * Time_Epoch;
			VerticalDisplacement_Y_ElectricField_Perpendicular = -1 * (Force_Electron / 2 * ELECTRON_MASS) * Time_Epoch * Time_Epoch;
			VerticalDisplacement_LeavingElectricField = (ELECTRON_ENERGY / 2 * ELECTRON_MASS) * Energy_Electron * (ElectronPlateWidth_L / pow(InitialVelocity_Electron, 2));

			printf("\n\n");
			printf("\nHorizontal Disp : %g", HorizontalDisplacement_X_ElectricField_Perpendicular);
			printf("\nVertical Disp : %g", VerticalDisplacement_Y_ElectricField_Perpendicular);
			printf("\nVertical Displacement Leaving : %g", VerticalDisplacement_LeavingElectricField);
			printf("\nTime : %d", Time_Epoch);
	}

	void ElectronMovement_Projectile(double InitialVelocity_Electron, float ProjectionAngle_Electron,unsigned long int Time_Seconds)
	{
		HorizontalComponent_Y_ElectricField_Projection = (InitialVelocity_Electron * cos(ProjectionAngle_Electron)) * Time_Seconds;
		VerticalCompoenet_Y_ElectricField_Projection = (InitialVelocity_Electron * sin(ProjectionAngle_Electron)) * (0.5 * Acceleration_Electron * pow(Time_Seconds, 2));

		MaxVerticalDisplacement_Y_ElectricField_Projection = ((pow(InitialVelocity_Electron, 2)) * (pow(sin(ProjectionAngle_Electron), 2))) / 2 * Acceleration_Electron;
		TimeTakenForMaxVerticalDisplacement_ElectricField_Projection = (InitialVelocity_Electron * sin(ProjectionAngle_Electron)) / Acceleration_Electron;

		
		TimeOfFlightOfElectron_ElectricField_Projection = 2 * TimeTakenForMaxVerticalDisplacement_ElectricField_Projection;
		RangeOfElectron_ElectricField_Projection = (2 * sin(ProjectionAngle_Electron) * cos(ProjectionAngle_Electron) * pow(InitialVelocity_Electron, 2) ) / Acceleration_Electron;
	
		printf("\n\n");
		printf("\n%g\n%g", HorizontalComponent_Y_ElectricField_Projection, VerticalCompoenet_Y_ElectricField_Projection);
	
	}