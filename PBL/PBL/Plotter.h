#pragma once

#include "SIGIL\include\sl.h"
#include "BasicCalc.h"


//void Draw(double Points
DWORD CALLBACK Draw(double PointsX[],double PointsY[])
{
	slWindow(500, 500, "Plot", 0);
	int i = 0;

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE) || i< 50)
	{
		slLine(PointsX[i], PointsY[i], PointsX[i + 1], PointsY[i + 1]);
		//slPoint(PointsX[i], PointsY[i]);
		slRender();
	}
	slClose();


	return 0;
}


DWORD CALLBACK GenerateCoordinates(double RawCoordinatesX[], double RawCoordinatesY[])
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

