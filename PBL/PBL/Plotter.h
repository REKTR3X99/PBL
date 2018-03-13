#pragma once
#include <Windows.h>

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
}Args;

struct NewCords
{
	double *XCords_Gen;
	double *YCords_Gen;
}NCords;


//void Draw(double Points
DWORD CALLBACK WINAPI Draw(unsigned long long ElemCount)
{
	int XInterval = 50;
	slWindow(XRes, YRes, "Plot", 0);
	unsigned long long i = 0;
	slSetFontSize(35);
	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		//Drawing X and Y axes
		slSetForeColor(1, 0.929, 0.2,1);
		slLine(4, 30, 50, 30); //X-Axis 
		slLine(3, 30,  4, 70); //Y-Axis 

		//Displaying X and Y
		slSetFontSize(36);
		slText(4, 100, "Y");
		slText(50, 50, "X");

		//Drawing the plates 
		slSetForeColor(1, 0, 0, 1);
		slRectangleOutline(0, YRes, 2 *XRes + 2 , 50);
		slRectangleOutline(0, 0, 2 * XRes + 2, 50);

		//Drawing Field Lines
		//for (int i = 0; i <= 4; i++)
		//{
		//	slLine(XInterval, 50, YRes - 5, YRes - 50);
		//	XInterval += 50;
		//}
		//Drawing electron
		slSetForeColor(0.1, 1, 0.1, 1);
		slCircleFill(NCords.XCords_Gen[i], NCords.YCords_Gen[i], 2, 128);
		
		slRender();
		i++;
		
		Sleep(10);
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
			NCords.YCords_Gen[i] = YRes / 2;
			
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
		NCords.XCords_Gen[i] = Args.XComp[i] * XRes / Max_X;
		NCords.YCords_Gen[i] = ((Args.YComp[i] * (YRes-50)) / (Max_Y)) + 30; //adding 30 so that it starts above electron plate
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