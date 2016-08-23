#include <stdio.h>

#define MIN -50.0
#define MAX 50.0
#define STEP 10.0

#define REVERSE 1

int main(void)
{
	float cels, fahr;
	int sign;
	sign = 1.0;
	// Print heading
	printf("Celsius To Fahrenheit\n*****************\n");
	
	if (REVERSE) {
		sign = -1.0;
	}
	// Print table
	for (cels = MIN; cels <= MAX ; cels += STEP) {
		fahr = sign * (9.0 / 5.0) * cels + 32.0; 
		printf("%3.0f\t%5.1f\n", sign * cels, fahr);	
	}
	return 0;
}
