#include "include\graphics.h"
#include <stdio.h>
#include <conio.h>
#include "include\functions.h"
#include "include\graph.h"
#include <math.h>
#include "include\structures.cpp"

#define INPUT      "files/input.txt"
#define OUTPUT     "files/output.txt"
#define PI         3.141592653
#define HEIGHT     600
#define WIDTH      800
#define DATA_COUNT 3

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
	int n = 21;
	
	double x[n] = {0, 30, 60, 90, 120, 150, 180, 210, 240, 270, 300, 330, 360, 390, 420, 450, 480, 510, 540, 570, 600};
	double y[n] = {0.000000, 0.000004, 0.000008, 0.000013, 0.000018, 0.000023, 0.000027, 0.000031, 0.000035, 0.000039, 0.000042, 0.000046, 0.000049, 0.000052, 0.000056, 0.000059, 0.000059, 0.000058, 0.000058, 0.000057, 0.000057};
	
	
	draw(x, y, n, "T, c", "I, À");
	
	getch();
	
	DATA data[DATA_COUNT];
	
	FILE *input;
	
	input = fopen(INPUT, "r");
	
	for (int i = 0; i < DATA_COUNT; i++) {
		data[i] = readData(input);
		printf("%lf %lf %lf %d %lg %d %d\n", data[i].T, data[i].dt, data[i].L0, data[i].k0, data[i].C0, data[i].m, data[i].n);
	}
	
	return 0;
}
