#include <graphics.h> //потрібно для графічного інтерфейсу
#include <stdio.h> //потрібно для виводу та вводу інформації
#include <math.h> //математичні функції

#define INPUT           "files/input.txt" //файл з вхідними даними
#define OUTPUT          "files/output.txt" //файл з вихідними даними
#define PI              3.141592653 //число пі
#define HEIGHT          720 //висота вікна для побудови графіка
#define WIDTH           1280 //ширина вікна для побудови графіка
#define STR_LEN         99 //довжина рядка char
#define DATA_COUNT      3 //кількість вхідних даних
#define EROR_SQRT       "It is impossible to calculate the square root" //помилка, коли неможливо порахувати квадратний корінь
#define ERROR_NOFILE    "There are no input file" //помилка, коли неможилво відкрити файл з вхідними даними
#define ERROR_EMPTYFILE "Input file is empty" //помилка, коли файл з вхідними даними пустий
#define ERROR_INVDATA   "Invalid input data" //помилка, коли вхідні дані некоректні

struct DATA { //структура вхідних даних
	double T, dt, L0, C0;
	int k0, m, n;
};

struct DATA_RES { //структура вихідних даних (протабульована функція)
	int n, num;
	double *x, *y;
	char *xLabel, *yLabel, *xSystem, *ySystem;
};

double getMin(double arr[], int n); //прототип функції для знаходження найменшого значення в масиві (потрібно для побудови графіка)

double getMax(double arr[], int n); //прототип функції для знаходження максимального значення в масиві (потрібно для побудови графіка)

int convert(double c, double dc, double cMin); //прототип функції для перетворення розрахованих координат точки в координату на екрані (потрібно для побудови графіка)

bool isBetween(double x, double a, double b); //прототип функції для з'ясування того, чи число входить в деякий проміжок 

double calcC(double t, DATA data); //прототип фукції для обрахування C

double calcK(double t, DATA data); //прототип функції для обрахування K

double calcL(double t, double k, DATA data); //прототип функції для обрахування L

DATA readData(FILE *input); //прототип функції для отримання вхідних даних з файлу

double calcT(double L, double C); //прототип функції для обрахування результату (T)

void draw(DATA_RES result); //прототип функції, яка будує графік

double calcT(double t, DATA data); //прототип функції для обрахування результату (T) від часу

DATA_RES tabulate(DATA data, int num, char* xLabel, char* yLabel, char* xSystem, char* ySystem); //прототип функції, яка табулює функцію

void printResult(DATA_RES result, FILE *output); //прототип функції, яка друкує протабульовану функцію у файл і командний рядок

int main() {	

	DATA data[DATA_COUNT]; //створюємо масив структур для вхідних даних
	DATA_RES res[DATA_COUNT]; //створюємо масив структур для вихідних даних
	FILE *input, *output; //вхідний та вихідний файл
	int i;
	
	initwindow(WIDTH, HEIGHT); //ініціалізуємо графічне вікно

	input = fopen(INPUT, "r"); //відкриваємо вхідний файл в режимі читання
	output = fopen(OUTPUT, "w"); //відкриваємо вихідний файл в режимі запису
	
	if (input == 0) { //якщо вхідний файл не відкрився
		puts(ERROR_NOFILE); //виводимо помилку
		exit(1);
	}
	
	fseek(input, 0, SEEK_END);
    if (ftell(input) == 0) { //якщо вхідний файл пустий
        puts(ERROR_EMPTYFILE); //виводимо помилку
        exit(1);
    } 
    fseek(input, 0, SEEK_SET);
    
    for (i = 0; i < DATA_COUNT; i++) { 
    	data[i] = readData(input); //читаємо вхідні дані
	}
	
	for (i = 0; i < DATA_COUNT; i++) {
    	res[i] = tabulate(data[i], i + 1, "t", "Tk", "c.", "c."); //табулюємо функцію 
	}
	
	for (i = 0; i < DATA_COUNT; i++) {
		system("cls");
		
		draw(res[i]); //друкуємо графік
		
		printResult(res[i], output); //роздруковуємо результат
		
		getch();
	}
	
	fclose(input); //завершаємо роботу з вхідним файлом
	fclose(output); //завершаємо роботу з вихідним файлом
	
	return 0;
}

double getMin(double arr[], int n) { //функції для знаходження найменшого значення в масиві (потрібно для побудови графіка)
	int i, iMin = 0;
	
	for (i = 1; i < n; i++) {
		if (arr[iMin] > arr[i]) {
			iMin = i; //знаходимо індекс найменого значення в масиві
		}
	}
	
	return arr[iMin]; //повертаємо найменше значення в масиві
}

double getMax(double arr[], int n) { //функції для знаходження найбільшого значення в масиві (потрібно для побудови графіка)
	int i, iMax = 0;
	
	for (i = 1; i < n; i++) {
		if (arr[iMax] < arr[i]) {
			iMax = i; //знаходимо індекс найбільшого значення в масиві
		}
	}
	
	return arr[iMax]; //повертаємо найменше значення в масиві
}

int convert(double c, double dc, double cMin) { //функція для перетворення розрахованих координат точки в координату на екрані (потрібно для побудови графіка)
	return round((c - cMin) / dc);	
}

bool isBetween(double x, double a, double b) { //функція для з'ясування того, чи число входить в деякий проміжок 
	if (x >= a && x <= b) {
		return true;
	}
	return false;
}

double calcC(double t, DATA data) { //функція для обрахування C
	if (isBetween(t, 0, data.T / 3)) {
		return data.C0 * (1 - exp(-1 * data.n * t));
	}
	if (isBetween(t, data.T / 3, data.T)) {
		return data.C0 * (1 - exp(-1 * data.n * data.T / 3));
	}	
}

double calcK(double t, DATA data) { //функція для обрахування K
	if (isBetween(t, 0, data.T / 4)) {
		return data.k0 * (1 + exp(-1 * data.m * t));
	}
	if (isBetween(t, data.T / 4, data.T)) {
		return data.k0 * (1 + exp(-1 * data.m * data.T / 4));
	}		
}

double calcL(double t, double k, DATA data) { //функція для обрахування L
	if (isBetween(t, 0, data.T / 2)) {
		return data.L0 * (1 - exp(-1 * k * t));
	}
	if (isBetween(t, data.T / 2, data.T)) {
		return data.L0 * (1 - exp(-1 * k * data.T / 2));
	}
}

DATA readData(FILE *input) { //функція для отримання вхідних даних з файлу
	DATA data;
	int flag;
	
	flag = fscanf(input, "%lf%lf%lf%d%lf%d%d", //читаємо вхідні дані
	       &data.T, &data.dt, &data.L0, &data.k0,
		   &data.C0, &data.m, &data.n);
		   
	if (flag != 7 || data.T <= 0 || data.dt <= 0 || data.L0 <= 0|| //перевіряємо коректність вхідних даних
		data.k0 <= 0 || data.C0 <= 0 || data.m <= 0 || data.n <= 0) {
		puts(ERROR_INVDATA); //друкуємо помилку
		exit(1);
	}
		   
	return data; //повертаємо прочитану структуру
}

void draw(DATA_RES result) { //функція для побудови графіку
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
		line(convert(result.x[i], dx, xMin), //будуємо графік
		h - convert(result.y[i], dy, yMin), 
		convert(result.x[i + 1], dx, xMin), 
		h - convert(result.y[i + 1], dy, yMin));
	}
	
	setcolor(BLUE);
	
	//воводимо всі надписи на графіку
	
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

double calcT(double t, DATA data) { //функція для обрахунку T від часу
	return calcT(calcL(t, calcK(t, data), data), calcC(t, data));
}

double calcT(double L, double C) { //функція для обрахунку T від L та C 
	if (L * C >= 0) {
		return 2 * PI * sqrt(L * C);
	} else {
		puts(EROR_SQRT);
		exit(1);
	}
}

DATA_RES tabulate(DATA data, int num, char* xLabel, char* yLabel, char* xSystem, char* ySystem) { //функція для табулювання функції
	DATA_RES result;
	int i = 0;
	double t = 0;

	result.n = (data.T / data.dt) + 1; //кількість обрахованих значень фукції
	result.num = num;
	result.xLabel = xLabel;
	result.yLabel = yLabel;
	result.xSystem = xSystem;
	result.ySystem = ySystem;
	
	result.x = (double*)calloc(result.n, sizeof(double)); //виділяємо пам'ять для масиву x 
	result.y = (double*)calloc(result.n, sizeof(double)); //виділяємо пам'ять для масиву y
		
	do { //табулюємо функцію
		result.x[i] = t;
		result.y[i] = calcT(t, data);
		
		t += data.dt;
		i++;
	} while (t <= data.T);
	
	result.x[result.n - 1] = data.T;
	result.y[result.n - 1] = calcT(data.T, data);
	
	return result;
}

void printResult(DATA_RES result, FILE *output) { //функція для друкування результату у файл і командний рядок
	int i;
	
	//друкуємо заголовки
	
	printf("Result %d:\n", result.num);
	fprintf(output, "Result %d:\n", result.num);
	
	//друкуємо результати
	
	for (i = 0; i < result.n; i++) {
		printf("%s = %.3lf %s\t %s = %lg %s\n", result.xLabel, result.x[i],
		                                         result.xSystem, result.yLabel,
											     result.y[i], result.ySystem);
											   
		fprintf(output, "%s = %.3lf %s\t %s = %lg %s\n", result.xLabel, result.x[i],
		                                                  result.xSystem, result.yLabel,
											              result.y[i], result.ySystem);
	}	
}
