#include "structures.h"

double getMin(double arr[], int n);

double getMax(double arr[], int n);

int convert(double c, double dc, double cMin);

bool isBetween(double x, double a, double b);

double calcC(double t, DATA data);

double calcK(double t, DATA data);

double calcL(double t, double k, DATA data);

DATA readData(FILE *input);
