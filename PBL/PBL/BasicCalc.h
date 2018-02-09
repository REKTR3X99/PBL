#pragma once
#include <stdio.h>
#include <conio.h>


#define ELECTRON_MASS 9.109E-31
#define ELECTRON_ENERGY 1.6E-19


double Energy(double Velocity, double PlateDistance)
{
	return Velocity / PlateDistance;
}


