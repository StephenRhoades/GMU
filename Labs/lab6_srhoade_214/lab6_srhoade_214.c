/* Stephen Rhoades G01369048
 * CS 262, Lab section 214
 * lab6: Random Numbers and Dynamic Memory 
 */

#include <stdio.h>
#include <stdlib.h>

void shuffleArray(int *numArray, int arrayLength){
	int i, j, temp;
	for (i = arrayLength-1; i > 0; i-- ){
		j = rand() % (i + 1);
		temp = numArray[i];
		numArray[i] = numArray[j];
		numArray[j] = temp;
	}
}

int compare(const void *a, const void *b){
	return (*(int*)a - *(int*)b);
}

void getMemory(int **numArray, int n){
	if (n > 500 || n < 2) {
		printf("Error! array size out of bounds [2-500]\n");	
		exit(-1);
	}
	*numArray = malloc(sizeof(int) * n);
	if (*numArray == NULL) {
		printf("Error allocating memory!\n");
		exit(-1);
	}
}

void initArray(int *numArray, int arrayLength){
	int i;
	for (i = 0; i < arrayLength; i++){
		*(numArray+i) = i;
	}
}

void printArray(int *numArray, int arrayLength){
	int i;
	for (i = 0; i < arrayLength; i++){
	        printf("%d ", *(numArray + i));
	}
        printf("\n");
}

int main(int argc, char *argv[] ) {
	int s, n, i;
	int *numArray = 0;
	
	if (argc <= 2) {
		printf("Not enough arguments for main to run. Please try again with at least two arguments.\n");
		return 0;
	}
	
	sscanf(argv[1], "%d", &s);
	sscanf(argv[2], "%d", &n);
	srand((unsigned)s);

	getMemory(&numArray, n);
	
	
	printf("This program will initilize an array %d digits long from 0 to %d.\n", n, n-1);
	printf("The array will be printed, randomly shuffled then printed, and sorted then printed one final time in that order.\n");
	printf("This entire process will repeat 10 times with a new line separating each iteration.\n");
	
	for (i = 0; i < 10; i++){

		initArray(numArray, n);
		printArray(numArray, n);
	
		shuffleArray(numArray, n);
		printArray(numArray, n);
	
		qsort(numArray, n, sizeof(int), compare);
		printArray(numArray, n);
		printf("\n");
	}
		
	free(numArray);
	return 1;
}
