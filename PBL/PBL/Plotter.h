#pragma once

#define XRes 800
#define YRes 600

#include <malloc.h>
#include <Windows.h>

#include "BasicCalc.h"
//using different headers for x64 and x86
#if defined _WIN32 
#include "SIGIL\include\sl.h"
#elif defined _WIN64
#include "SIGIL\include\x64\sl.h"
#endif

struct Arguments
{
	double *XComp;
	double *YComp;
}Args, *PArgs;


struct NewCords
{
	double *XCords_Gen;
	double *YCords_Gen;
}NCords;


//void Draw(double Points
DWORD CALLBACK WINAPI Draw(unsigned long long ElemCount)
{
	slWindow(XRes, YRes, "Plot", 0);
	unsigned long long i = 0;
	slSetFontSize(35);
	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		
		slSetForeColor(0.1, 1, 0.1, 1);
		slLine(NCords.XCords_Gen[i],NCords.YCords_Gen[i],NCords.XCords_Gen[i+1],NCords.YCords_Gen[i+1]);
		//slText(NCords.XCords_Gen[i], NCords.YCords_Gen[i], ".");
		slRender();
		i++;
		
		//	slScale(NCords.XCords_Gen[i], NCords.YCords_Gen[i]);
		Sleep(16);
		if (i == ElemCount)
		{
			slSetForeColor(0, 0, 0, 0);
			i = 0;
		}
		
	}
	slClose();


	return 0;
}


void GenerateCoordinates(unsigned long long ElemCount)
{
	double Max_X = Args.XComp[0];
	double Max_Y= 0;
	

	//Scaling down the values to fit into the resolution of the window
	
	if (Args.YComp == 0)
	{
		NCords.XCords_Gen = (double *)calloc(ElemCount, sizeof(double)); 
		NCords.YCords_Gen = (double *)calloc(ElemCount, sizeof(double));
		for (unsigned long long i = 0; i <= ElemCount; i++)
		{
			Max_X = (Max_X < Args.XComp[i]) ? Args.XComp[i] : Max_X;
			
		}
	}
	else
	{
		NCords.XCords_Gen = (double *)calloc(ElemCount, sizeof(double));
		NCords.YCords_Gen = (double *)calloc(ElemCount, sizeof(double));
		for (unsigned long long i = 0; i <= ElemCount; i++)
		{
			Max_X = (Max_X < Args.XComp[i]) ? Args.XComp[i] : Max_X;
			Max_Y = (Max_Y < Args.YComp[i]) ? Args.YComp[i] : Max_Y;
		}
	}

	for (unsigned long long i = 0; i < ElemCount; i++)
	{
		NCords.XCords_Gen[i] = (Args.XComp[i] * XRes )/ Max_X;
		NCords.YCords_Gen[i] = (Args.YComp[i] * YRes )/ Max_Y;
		printf("\nX = %lf\t Y = %lf", NCords.XCords_Gen[i], NCords.YCords_Gen[i]);
	}
	
	DWORD ThreadID;
	HANDLE DrawHandle = CreateThread(NULL, 0, Draw, ElemCount, 0, &ThreadID);
}

void PlotAssigner(double *XRawCords, double *YRawCords)
{
	
	unsigned long long Elems = _msize(XRawCords) / sizeof(XRawCords[0]);

	Args.XComp = XRawCords;
	Args.YComp = YRawCords;

	//free(XRawCords);
	//free(YRawCords);

	GenerateCoordinates(Elems);
	system("pause");
	
}