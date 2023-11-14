/* Stephen Rhoades G01369048
 * CS 262, Lab Section 214
 * Lab7: File I/O and Formatting
 */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 60

int main(int argc, char *argv[]){
	int linesToRead, Gnum, semester, credits;
	float grade;
	char buff[SIZE];
	char * input, * output, *name, *course;
	FILE * frptr, * fwptr;
	if (argc <= 2) {
		printf("Not enough arguments for main to run. Please try again with at least two arguments.\n");
		return 1;
	}
	
	input = argv[1];
	output = argv[2];
	
	/* printf("input: %s, output: %s\n", input, output); */
	
	frptr = fopen(input, "r");
	if (frptr == NULL) {
		printf("ERROR! the input file could not be opened\n");
		return 1;
	}
	
	fwptr = fopen(output, "w");
	if (fwptr == NULL) {
		printf("ERROR! the output file could not be opened\n");
		return 1;
	}
	
	name = malloc(20);
	course = malloc(20);

	fgets(buff, SIZE, (FILE*)frptr);

	for (linesToRead = atoi(buff); linesToRead > 0; linesToRead--){

		fgets(buff, SIZE, (FILE*)frptr);

		sscanf(buff, "%d %[^,] %s %d %s %d %f", &Gnum, name, course, &semester, course, &credits, &grade );
		fprintf(fwptr,"%-25s %-10d %-8.2f %-10s %-3d %3d\n",name, Gnum, grade, course, credits, semester);
	}

	free(name);
	free(course);
	fclose(frptr);
	fclose(fwptr);
	return 0;
}

