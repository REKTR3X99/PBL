#pragma once

#include "SIGIL\include\sl.h"
#include "BasicCalc.h"


//void Draw(double Points
DWORD CALLBACK Draw(double PointsX[],double PointsY[])
{
	slWindow(800, 600, "Plot", 0);
	int i = 0;

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		slLine(PointsX[i], PointsY[i], PointsX[i+1], PointsY[i+1]);
		//slPoint(PointsX[i], PointsX[i+1]);
		slRender();
	}
	slClose();


	return 0;
}


DWORD CALLBACK WINAPI GenerateCoordinates(LPVOID *RawCoordinatesX[], LPVOID *RawCoordinatesY[])
{
	

	int factor = sizeof(RawCoordinatesX) / sizeof(RawCoordinatesX[0]);
	printf("\n Factor :%d", factor);

	double *NewXCordinate = (double *)calloc(factor, sizeof(double));
	double *NewYCordinate = (double *)calloc(factor, sizeof(double));

	for (unsigned long long i = 0; i <= factor; i++)
	{
		NewXCordinate[i] = RawCoordinatesX[i + 1] - RawCoordinatesX[i];
		NewYCordinate[i] = RawCoordinatesY[i + 1] - RawCoordinatesY[i];
	}

	Draw(NewXCordinate, NewYCordinate);

	
	return 0;
}

