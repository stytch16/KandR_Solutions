#include <stdio.h>

#define MIN -50
#define MAX 50
#define STEP 10

void printCelsToFahrTable(int min, int max, int step);
float computeCelsToFahr(float cels);

int main(void)
{
	
	// Print heading
	printf("Celsius To Fahrenheit\n*****************\n");
	
	// Print table
	printCelsToFahrTable(MIN, MAX, STEP);	
	return 0;
}

void printCelsToFahrTable(int min, int max, int step)
{
	float cels;
	for (cels = min; cels <= max; cels += step) {
		printf("%3.0f\t%5.1f\n", cels, computeCelsToFahr(cels));	
	}
}

float computeCelsToFahr(float cels)
{
	return (9.0 / 5.0) * cels + 32.0;
}

			
