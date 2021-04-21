#include <stdlib.h>
#include "functions.h"
#include "graphics.h"
#include <math.h>

void draw(double x[], double y[], int n, char* xLabel, char* yLabel) {
	double xMin = getMin(x, n);
	double xMax = getMax(x, n);
	
	double yMin = getMin(y, n);
	double yMax = getMax(y, n);
	
	int w = getmaxx();
	int h = getmaxy();
	
	double dx = (xMax - xMin) / w;
	double dy = (yMax - yMin) / h;
	
	int i;
	
	cleardevice();
	
	for (i = 0; i < n - 1; i++) {
		line(convert(x[i], dx, xMin), h - convert(y[i], dy, yMin), convert(x[i + 1], dx, xMin), h - convert(y[i + 1], dy, yMin));
	}
	
	outtextxy(0, 0, yLabel);
	outtextxy(w - 10 * strlen(xLabel), h - 20, xLabel);
}
