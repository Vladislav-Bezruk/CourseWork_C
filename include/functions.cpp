#include <math.h>

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
