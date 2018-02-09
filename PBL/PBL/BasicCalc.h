#pragma once
#include <stdio.h>
#include <conio.h>
#include <math.h>


#define ELECTRON_MASS 9.109E-31
#define ELECTRON_ENERGY 1.6E-19



double Energy_Electron;
double Force_Electron;
double Acceleration_Electron;
double Velocity_Electron;
double Displacement_Electron; 


	void Basic_Calculations(double PotentialDifference, double PlateDistance)
	{
		Energy_Electron = PotentialDifference / PlateDistance; //Energy of the electron
		Force_Electron = -1 * ELECTRON_ENERGY * Energy_Electron; //Force of the electorn on plate B ( The plate form which the electron enters into the field)
		Acceleration_Electron = Force_Electron / ELECTRON_MASS; //Acceleration of the electron

	}

	void Velocity_Disp_Calc(double InitialVelocity_Electron, long int Time_SecondsFromEpoch)
	{
		//Note : Add a time function to get the velocity over time
		Velocity_Electron = InitialVelocity_Electron + (Acceleration_Electron * Time_SecondsFromEpoch);
		Displacement_Electron = (InitialVelocity_Electron * Time_SecondsFromEpoch) + (0.5f*Acceleration_Electron * powf(Time_SecondsFromEpoch, 2));

	}


