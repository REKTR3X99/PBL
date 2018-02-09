#pragma once
#include <stdio.h>
#include <conio.h>


#define ELECTRON_MASS 9.109E-31
#define ELECTRON_ENERGY 1.6E-19


double Energy_Electron;
double Force_Electron;
double Acceleration_Electron;


void BasicCalculations(double Velocity, double PlateDistance)
{
	Energy_Electron = Velocity / PlateDistance;
	Force_Electron = -1 * ELECTRON_ENERGY * Energy_Electron;
	Acceleration_Electron = Force_Electron / ELECTRON_MASS;

}

