#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#define INPUT           "files/input.txt"
#define OUTPUT          "files/output.txt"
#define PI              3.141592653
#define HEIGHT          720
#define WIDTH           1280
#define STR_LEN         99
#define DATA_COUNT      3
#define EROR_SQRT       "It is impossible to calculate the square root"
#define ERROR_NOFILE    "There are no input file"
#define ERROR_EMPTYFILE "Input file is empty"
#define ERROR_INVDATA   "Invalid input data"

struct DATA {
	double T;
	double dt;
	double L0;
	int k0;
	double C0;
	int m;
	int n;
};

struct DATA_RES {
	int n, num;
	double *x, *y;
	char *xLabel, *yLabel, *xSystem, *ySystem;
};

double getMin(double arr[], int n);

double getMax(double arr[], int n);

int convert(double c, double dc, double cMin);

bool isBetween(double x, double a, double b);

double calcC(double t, DATA data);

double calcK(double t, DATA data);

double calcL(double t, double k, DATA data);

DATA readData(FILE *input);

double calcT(double L, double C);

void draw(DATA_RES result);

double calcT(double t, DATA data);

DATA_RES tabulate(DATA data, int num, char* xLabel, char* yLabel, char* xSystem, char* ySystem);

void printResult(DATA_RES result, FILE *output);

int main() {	

	DATA data[DATA_COUNT];
	DATA_RES res[DATA_COUNT];
	FILE *input, *output;
	int i;
	
	initwindow(WIDTH, HEIGHT);

	input = fopen(INPUT, "r");
	output = fopen(OUTPUT, "w");
	
	if (input == 0) {
		puts(ERROR_NOFILE);
		exit(1);
	}
	
	fseek(input, 0, SEEK_END);
    if (ftell(input) == 0) { 
        puts(ERROR_EMPTYFILE);  
        exit(1);
    } 
    fseek(input, 0, SEEK_SET);
	
	for (i = 0; i < DATA_COUNT; i++) {
		system("cls");
		
		data[i] = readData(input);
			
		res[i] = tabulate(data[i], i + 1, "t", "Tk", "c.", "c.");
		
		draw(res[i]);
		
		printResult(res[i], output);
		
		getch();
	}
	
	fclose(input);
	fclose(output);
	
	return 0;
}

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
	int flag;
	
	flag = fscanf(input, "%lf%lf%lf%d%lf%d%d", 
	       &data.T, &data.dt, &data.L0, &data.k0,
		   &data.C0, &data.m, &data.n);
		   
	if (flag != 7 || data.T <= 0 || data.dt <= 0 || data.L0 <= 0|| 
		data.k0 <= 0 || data.C0 <= 0 || data.m <= 0 || data.n <= 0) {
		puts(ERROR_INVDATA);
		exit(1);
	}
		   
	return data;
}

void draw(DATA_RES result) {
	char xLabelG[STR_LEN];
	char yLabelG[STR_LEN];
	
	double xMin = getMin(result.x, result.n);
	double xMax = getMax(result.x, result.n);
	
	double yMin = getMin(result.y, result.n);
	double yMax = getMax(result.y, result.n);
	
	int w = getmaxx();
	int h = getmaxy();
	
	double dx = (xMax - xMin) / w;
	double dy = (yMax - yMin) / (h - 10);
	
	char label[STR_LEN] = "Result ";
	char strNum[3] = {result.num + '0', ':', '\0'};
	char labelBkp[STR_LEN];
	
	int i;
	
	setbkcolor(WHITE);
	
	setlinestyle(SOLID_LINE, 0, 5);
	
	cleardevice();
	
	setcolor(RED);
	
	for (i = 0; i < result.n - 1; i++) {
		line(convert(result.x[i], dx, xMin), 
		h - convert(result.y[i], dy, yMin), 
		convert(result.x[i + 1], dx, xMin), 
		h - convert(result.y[i + 1], dy, yMin));
	}
	
	setcolor(BLUE);
	
	strcat(label, strNum);
	
	outtextxy(w / 2 - 10 * strlen(label), 0, label);
	
	strcpy(xLabelG, result.xLabel);
	strcpy(yLabelG, result.yLabel);
	
	strcat(yLabelG, ", ");
	strcat(yLabelG, result.ySystem);
	
	strcat(xLabelG, ", ");
	strcat(xLabelG, result.xSystem);
	
	outtextxy(0, 0, yLabelG);
	outtextxy(w - 10 * strlen(xLabelG), h - 20, xLabelG);
	
	setcolor(GREEN);
	
	snprintf(labelBkp, STR_LEN, "%lg", result.y[0]);
	
	outtextxy(0, h - 20, labelBkp);
	
	snprintf(labelBkp, STR_LEN, "%lg", result.y[result.n - 1]);
	
	outtextxy(0, 20, labelBkp);
	
	snprintf(labelBkp, STR_LEN, "%lg", (result.y[0] + result.y[result.n - 1]) / 2);
	
	outtextxy(0, h / 2, labelBkp);
	
	snprintf(labelBkp, STR_LEN, "%lg", result.x[0]);
	
	outtextxy(20, h - 30, labelBkp);
	
	snprintf(labelBkp, STR_LEN, "%lg", result.x[result.n - 1]);
	
	outtextxy(w - 30, h - 30, labelBkp);
	
	snprintf(labelBkp, STR_LEN, "%lg", (result.x[0] + result.x[result.n - 1]) / 2);
	
	outtextxy(w / 2, h - 30, labelBkp);
}

double calcT(double t, DATA data) {
	return calcT(calcL(t, calcK(t, data), data), calcC(t, data));
}

double calcT(double L, double C) {
	if (L * C >= 0) {
		return 2 * PI * sqrt(L * C);
	} else {
		puts(EROR_SQRT);
		exit(1);
	}
}

DATA_RES tabulate(DATA data, int num, char* xLabel, char* yLabel, char* xSystem, char* ySystem) {
	DATA_RES result;
	int i = 0;
	double t = 0;

	result.n = (data.T / data.dt) + 1;
	result.num = num;
	result.xLabel = xLabel;
	result.yLabel = yLabel;
	result.xSystem = xSystem;
	result.ySystem = ySystem;
	
	result.x = (double*)calloc(result.n, sizeof(double)); 
	result.y = (double*)calloc(result.n, sizeof(double)); 
		
	do {
		result.x[i] = t;
		result.y[i] = calcT(t, data);
		
		t += data.dt;
		i++;
	} while (t <= data.T);
	
	result.x[result.n - 1] = data.T;
	result.y[result.n - 1] = calcT(data.T, data);
	
	return result;
}

void printResult(DATA_RES result, FILE *output) {
	int i;
	printf("Result %d:\n", result.num);
	fprintf(output, "Result %d:\n", result.num);
	
	for (i = 0; i < result.n; i++) {
		printf("%s = %.3lf %s\t %s = %lg %s\n", result.xLabel, result.x[i],
		                                         result.xSystem, result.yLabel,
											     result.y[i], result.ySystem);
											   
		fprintf(output, "%s = %.3lf %s\t %s = %lg %s\n", result.xLabel, result.x[i],
		                                                  result.xSystem, result.yLabel,
											              result.y[i], result.ySystem);
	}	
}
