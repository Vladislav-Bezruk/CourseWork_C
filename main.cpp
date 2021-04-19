#include "include\graphics.h"
#include <stdio.h>
#include <conio.h>
#include "include\functions.h"

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
	initwindow(400, 300); 
	
	output(5);
	                     
	moveto(0, 0);         
	lineto(400, 300);       
	getch();
	cleardevice();
	getch();            
	            
	closegraph();   
	
	     
	return 0;
}
