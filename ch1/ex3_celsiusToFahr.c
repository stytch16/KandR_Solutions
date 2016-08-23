#include <stdio.h>

#define MIN -50.0
#define MAX 50.0
#define STEP 10.0

int main(void)
{
	float cels, fahr;
	
	// Print heading
	printf("Celsius To Fahrenheit\n*****************\n");
	
	// Print table
	for (cels = MIN; cels <= MAX; cels += STEP) {
		fahr = (9.0 / 5.0) * cels + 32.0; 
		printf("%3.0f\t%5.1f\n", cels, fahr);	
	}
	return 0;
}
