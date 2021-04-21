#include "include\graphics.h"
#include <stdio.h>
#include <conio.h>
#include "include\functions.h"
#include "include\graph.h"
#include <math.h>

#define HEIGHT 600
#define WIDTH 800

struct DATA {
	double T;
	double dt;
	double L0;
	int k0;
	double C0;
	int m;
	int n;
};

int main() {
	initwindow(WIDTH, HEIGHT);
	 
	/*                    
	moveto(0, 0);         
	lineto(400, 300);       
	getch();
	cleardevice();
	getch();            
	            
	closegraph(); 
	*/
	int n = 10000;
	
	double x[n] , y[n];
	
	for (int i = 0; i < n; i++) {
		x[i] = 0.01 * (i - n / 2);
		float xn = x[i];
		
		y[i] = sin(xn);
	}
	
	draw(x, y, n, "T, секунди", "F, сила");
	
	getch();
	
	return 0;
}
