#include <math.h>
#include "structures.cpp"
#include <stdio.h>

double getMin(double arr[], int n) {
	int i, iMin = 0;
	
	for (i = 1; i < n; i++) {
		if (arr[iMin] > arr[i]) {
			iMin = i;
		}
	}
	
	return arr[iMin];	
}

double getMax(double arr[], int n) {
	int i, iMax = 0;
	
	for (i = 1; i < n; i++) {
		if (arr[iMax] < arr[i]) {
			iMax = i;
		}
	}
	
	return arr[iMax];	
}

int convert(double c, double dc, double cMin) {
	return round((c - cMin) / dc);	
}

bool isBetween(double x, double a, double b) {
	if (x >= a && x <= b) {
		return true;
	}
	return false;
}

double calcC(double t, DATA data) {
	if (isBetween(t, 0, data.T / 3)) {
		return data.C0 * (1 - exp(-1 * data.n * t));
	}
	if (isBetween(t, data.T / 3, data.T)) {
		return data.C0 * (1 - exp(-1 * data.n * data.T / 3));
	}	
}

double calcK(double t, DATA data) {
	if (isBetween(t, 0, data.T / 4)) {
		return data.k0 * (1 + exp(-1 * data.m * t));
	}
	if (isBetween(t, data.T / 4, data.T)) {
		return data.k0 * (1 + exp(-1 * data.m * data.T / 4));
	}		
}

double calcL(double t, double k, DATA data) {
	if (isBetween(t, 0, data.T / 2)) {
		return data.L0 * (1 - exp(-1 * k * t));
	}
	if (isBetween(t, data.T / 2, data.T)) {
		return data.L0 * (1 - exp(-1 * k * data.T / 2));
	}
}

DATA readData(FILE *input) {
	DATA data;
	
	fscanf(input, "%lf%lf%lf%d%lf%d%d", 
	       &data.T, &data.dt, &data.L0, &data.k0,
		   &data.C0, &data.m, &data.n);
		   
	return data;
}
