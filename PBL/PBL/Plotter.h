#pragma once
#include <malloc.h>

#include <Windows.h>

#include "BasicCalc.h"
//using different headers for x64 and x86
#if defined _WIN32 
#include "SIGIL\include\sl.h"
#elif defined _WIN64
#include "SIGIL\include\x64\sl.h"
#endif



#define XRES 800
#define YRES 600


struct Arguments
{
	double *XComp;
	double *YComp;
	double *MaxYCord;
	double MaxXCord;
}Args;

struct NewCords
{
	double *XCords_Gen;
	double *YCords_Gen;
}NCords;

DWORD CALLBACK WINAPI Draw_Parallel(unsigned long long ElemCount)
{
	slWindow(XRES, YRES, "Plot", 0);
	unsigned long long i = 0;
	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		slSetForeColor(0, 1, 0, 1);
		slCircleFill(NCords.XCords_Gen[i], YRES/2, 2.5, 128);
		i++;
		if (i == ElemCount)
		{
			i = 0;
			continue;
		}
		slRender();
	}

	slClose();

	return 0;
}

DWORD CALLBACK WINAPI Draw_Perpendicular(unsigned long long ElemCount)
{
	slWindow(XRES, YRES, "Plot", 0);
	int LineDrawCount_X = XRES;
	int LineDrawCount_Y = YRES;
	float alpha = 1;
	int i = 0;
	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		slSetForeColor(1, 1, 1, 1);
		slSetFontSize(100);
		slText(700, 300, "Magnetic Field");
		slSetForeColor(0, 0.3, 1, 1);
		//drawing direction of perpendicular magnetic lines
		slLine(100, YRES, 100, LineDrawCount_Y -= 1);
		slLine(200, YRES, 200, LineDrawCount_Y -= 1);
		slLine(300, YRES, 300, LineDrawCount_Y -= 1);
		slLine(400, YRES, 400, LineDrawCount_Y -= 1);
		slLine(500, YRES, 500, LineDrawCount_Y -= 1);
		slLine(600, YRES, 600, LineDrawCount_Y -= 1);
		slLine(700, YRES, 700, LineDrawCount_Y -= 1);

		   //slLine(0, 100, XRes, 100);
		slSetForeColor(0, 0.9, 0, 1);
		slCircleFill(NCords.XCords_Gen[i], NCords.YCords_Gen[i], 2, 128);
		i++;
		if (i == ElemCount)
		{
			i = 0;
			continue;
		}
		if (LineDrawCount_Y < 0)
		{
			LineDrawCount_Y = YRES;
			
		}
		//Sleep(20);
		slRender();
	}

	slClose();

	return 0;
}



//Drawing for Projectile
DWORD CALLBACK WINAPI Draw_Projectile(unsigned long long ElemCount)
{
	int XInterval = 50;
	slWindow(XRES, YRES, "Plot", 0);
	unsigned long long i = 0;
	slSetFontSize(35);
	//unsigned long long i = 0;
	unsigned long long int j = 0;
	for ( i = 0; i <= ElemCount; i++)
	{
		if (Args.YComp[i] > *Args.MaxYCord)
			break;
	}

	//Mirroring half of the parabola to save on performance
	for (j = i; j <= ElemCount; j--)
	{
		{
		Args.YComp[i] =  Args.YComp[j+1] + Args.MaxXCord;

		}
		++i;;
	}
	for (unsigned long long i = 0; i < ElemCount; i++)
	{
		//NCords.XCords_Gen[i] = Args.XComp[i] * XRes / 100;
		NCords.YCords_Gen[i] = ((Args.YComp[i] * (YRES - 50)) / (*Args.MaxYCord)) + 30;
	}
	

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		//Drawing X and Y axes
		slSetForeColor(1, 0.929, 0.2,1);
		slLine(4, 30, 50, 30); //X-Axis 
		slLine(3, 30,  4, 70); //Y-Axis 

		//Displaying X and Y
		slSetFontSize(100);
		slText(4, 100, "Y");
		slText(50, 50, "X");

		//Drawing the plates 
		slSetForeColor(1, 0, 0, 1);
		slRectangleOutline(0, YRES, 2 *XRES + 2 , 50);
		slRectangleOutline(0, 0, 2 * XRES + 2, 50);

		//Drawing Field Lines
		//for (int i = 0; i <= 4; i++)
		//{
		//	slLine(XInterval, 50, YRes - 5, YRes - 50);
		//	XInterval += 50;
		//}
		//Drawing electron
		slSetForeColor(0.1, 1, 0.1, 1);
		slCircleFill(NCords.XCords_Gen[i], NCords.YCords_Gen[i], 2.5, 128);
		
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

DWORD CALLBACK WINAPI Draw_Transverse()
{
	slWindow(XRES, YRES, "Plot", 0);
	int XPos_Start = XRES;
	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		slSetForeColor(0, 0.2, 0.8, 1);
		slLine(XRES, 150, XPos_Start, 150);
		slLine(XRES, 300, XPos_Start, 300);
		slLine(XRES, 450, XPos_Start, 450);
		XPos_Start-=5;

		if (XPos_Start == 0)
			XPos_Start = XRES;
		slRender();
	}

	slClose();
}

DWORD CALLBACK WINAPI Draw_Longitudinal()
{
	slWindow(XRES,YREs,"Plot", 0);
	
	while(!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		slSetForeColor(0,0.2,0.8,1);
		slCircleOutLine(XRES/2, YRES/2, 5,  128);
		slRender();
	}

	slClose();
}

void GenerateCoordinates(unsigned long long ElemCount)
{
	double Max_X = Args.XComp[0];
	double Max_Y= 0;
	unsigned long long i;
	
	//Scaling down the values to fit into the resolution of the window
	
	if (Args.YComp == 0)
	{
		NCords.XCords_Gen = (double *)calloc(ElemCount, sizeof(double)); 
		NCords.YCords_Gen = (double *)calloc(ElemCount, sizeof(double));

		for (i = 0; i < ElemCount; i++)
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
		if (Args.YComp == 0)
		{
			NCords.XCords_Gen[i] = Args.XComp[i] * XRES / Max_X;
			NCords.XCords_Gen[i] = YRES / 2;
			printf("\nX = %lf\t Y = %lf", NCords.XCords_Gen[i], NCords.YCords_Gen[i]);
		}
		else
		{
			NCords.XCords_Gen[i] = Args.XComp[i] * XRES / Max_X;
			NCords.YCords_Gen[i] = ((Args.YComp[i] * (YRES - 50)) / (Max_Y)) + 30; //adding 30 so that it starts above electron plate
			printf("\nX = %lf\t Y = %lf", NCords.XCords_Gen[i], NCords.YCords_Gen[i]);
		}
	}
	
}

void PlotAssigner(double *XRawCords, double *YRawCords, double *MaxYCordRaw, int Identifier,...) //parameter pack operator
{
	unsigned long long Elems;
	
	if (Identifier != 3 && Identifier != 4)
	{
		Elems = _msize(XRawCords) / sizeof(XRawCords[0]);
	}

	DWORD ThreadID;
	HANDLE DrawHandle;
	va_list ListArgs;
	va_start(ListArgs, Identifier);
	
	Args.MaxXCord = va_arg(ListArgs, double);
	va_end(ListArgs);
	
	Args.XComp = XRawCords;
	Args.YComp = YRawCords;
	Args.MaxYCord = MaxYCordRaw;

	if(Identifier!=3 && Identifier!=4)
		GenerateCoordinates(Elems);

	switch (Identifier)
	{
	case 0 :
		DrawHandle = CreateThread(NULL, 0, Draw_Parallel, Elems, 0, &ThreadID);
		break;

	case 1:
		DrawHandle = CreateThread(NULL, 0, Draw_Perpendicular, Elems, 0, &ThreadID);
		break;

	case 2:
		DrawHandle = CreateThread(NULL, 0, Draw_Projectile, Elems, 0, &ThreadID);
		break;

	case 3:
		DrawHandle = CreateThread(NULL, 0, Draw_Transverse, NULL, 0, &ThreadID);
		break;

	case 4:
	DrawHandle = CreateThread(NULL, 0, Draw_Longitudinal, NULL, 0, 0, &ThreadID);
		break;
		
	}
	
	system("pause");
	
}