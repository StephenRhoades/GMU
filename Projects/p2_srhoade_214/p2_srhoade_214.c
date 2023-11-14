/* Stephen Rhoades G01369048
 * CS 262, Lab section 214
 * Project 2: Blazcar's Roads
 *
 * This program is designed to read a file containing structured information about roads and 
 * their intesections and determine the rank when it comes to the longest possible road to 
 * downtown, ie intersection 0, each road could achieve when the intersections counts as that 
 * road. Each combination of road and their intersections is considered to see what each road's 
 * maximum rank could be. This is then printed into an output file called blazcar_c1.out.
 *
 * Necessary file format: n = number of roads, m = number of intersections, 0 0 ends the program
 * n m
 * name1 intersection length
 * ...
 * namen intersection length
 * intesection length
 * ...
 * intersection length
 * 0 0
 *
 * example:
 * 6 2
 * Bulma 0 513
 * Frieza 2 675
 * Yamcha 2 700
 * Vegeta 1 335
 * Piccolo 1 305
 * Goku 0 765
 * 0 353
 * 0 65
 * 0 0
 */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 50

/* This function populates and returns an array with every possible combination of route choices.
 * Included in the array is the altered length of an intersection if any combine separatly from a named road.
 * The number of possible permutations is calculated by multiplying the number of times each 
 *  value of m(the number of interstections) appears in the list. The array is then malloced data
 *  to fit n+m values in each permutation.
 * Each base distance value is copied over to the new array for each permutation, then the intersection 
 *  distances will be added to each road that connects with it in sequential combinations to cover each case.
 * */
int * iterate(int n, int m, int * c, int * d){
	int i, x, y, * fact, perms, *data, skip, div;

	fact = malloc(sizeof(int) *m);
	if(fact == NULL) {
		printf("Error! Memory allocation failed.\n");
		return NULL;
	}
	for (x = 0; x < m; x++ ){
		*(fact+x) = 0;
		for (y = 0; y < n+m; y++){
			if (*(c+y) == x+1){
				*(fact+x) += 1; 
			}
		}
		/* test printing 
		printf("fact[%d] = %d\n", x, *(fact+x));
		*/
	}
	perms = 1;
	for (x = 0; x < m; x++ ){
		perms *= *(fact+x);
	}
	/* test printing
	printf("#permutations = %d\n", perms);
	*/

	data = malloc(sizeof(int) *(n+m) *perms);
	if(data == NULL) {
		printf("Error! Memory allocation failed.\n");
		return NULL;
	}
	
	/* initializes each permutations values to their corresponding base value.*/
	for (x = 0; x < (n+m)* perms; x++){
		*(data+x) = *(d+(x%(n+m)));
	}		
	
	/* This will iterate each combination like a truth table but able to have more than 0 and 1 */
	for (i = 0; i < perms; i++ ){
		div = perms;
		for (x = 0; x < m; x++ ){
			skip = i % div;		/*modulus the skip constant by the previous divisor*/
			div /= *(fact + x);	/*divides the divisor by the number of occurences of 
						  the current intersection.*/

			for (y = 0; y < n+m; y++){
				if (*(c+y) == x+1){
					if( (skip/div) == 0){
						*(data+y+((n+m)*i)) += *(data+n+((n+m)*i)+x);
						break;
					} else {
						skip -= div;
					}
				}
			}
		}
	}
	
	/* test printing of data array
	for(x = 0; x < perms; x++ ){
		for (y = 0; y < n; y++){
			printf("%d ", *(data+y+((n+m)*x)));
		}
		printf("\n");
	}
	*/
	free(fact);
	return data;
}


/* This function loops through the data set of each iteration and compares the values of the given 
 * indexed road to the other roads in its permutation to determine the best rank possible for the 
 * given road and return it.
 * */
int highestRank(int index, int n, int m, int * c, int * data){
	int i, x, rank, best, *fact, perms;
	best = n;
	fact = malloc(sizeof(int) *m);
	if(fact == NULL) {
		printf("Error! Memory allocation failed.\n");
		return -1;
	}
	
	for (x = 0; x < m; x++ ){
		*(fact+x) = 0;
		for (i = 0; i < n+m; i++){
			if (*(c+i) == x+1){
				*(fact+x) += 1;
			}
		}
	}
	perms = 1;
	for (x = 0; x < m; x++ ){
		perms *= *(fact+x);
	}
	free(fact);
	
	/*loops through the array incrementing rank every time a value is larger than the indexed value.*/
	for(i = 0; i < perms; i++) {
		rank = 1;
		for( x = 0; x < n; x++) {
			if (*(data+index+((n+m)*i)) < *(data+x+((n+m)*i))){
				rank ++;
			}
		}
		if(rank < best){
			best = rank;
		}
	}
	return best;
}

/* The main function takes in a command line argument to indicate a file name to open. 
 * Then it creates an output file called blazcar_c1.out to write to.
 * The primary loop iterates while the parameters of the file do not equal 0 0.
 * 	The while loop reads through each line of the document indicated by the parameters n and m
 * 	and stores the information in arrays names, c(closest intersection), and d(distance to c).
 * 	Then the function iterate() is called to populate the int * data with each possible combination
 * 	of road naming and their approprate length.
 * 	Then for each named road the highestRank() function is called and the determined value is printed 
 * 	to blazcar_c1.out after the relevant road name.
 * If none of the mallocs or file opening causes an error and the loop is escaped then the program will 
 * print "Output file: blazcar_c1.out created successfully." and the files are closed.
 * */
int main(int argc, char *argv[] ) {
	char * input, line[SIZE], *names;
	FILE * frptr, * out; /* The file reading pointer and the file writing pointer. */
	int i, n, m, *c, *d, *data, instance;

	if (argc < 2) {
		printf("Error! You must	specify	input filename: ./p2 <input_filename>.\n");
		return 1;
	}
	
	input = argv[1];
	
	/* tries to open the file provided as a command line argument, 
	 * printing an error and exiting on failure.*/
	frptr = fopen(input, "r");
	if (frptr == NULL){
		printf("Error! The %s file can't be opened.\n", input);
		return 1;
	}
	
	out = fopen("blazcar_c1.out", "w");
        if (out == NULL){
                printf("Error! Could not open output file.\n");
                fclose(frptr);
		return 1;
        }

	fgets(line, SIZE, frptr);
	sscanf(line, "%d %d", &n, &m);
	instance = 0;

	while (n != 0 || m != 0 ) {
		instance++;
		fprintf(out, "Instance %d:\n", instance);
		c = malloc(sizeof(int) * (n+m));
		d = malloc(sizeof(int) * (n+m));
		names = malloc(SIZE * n);

		if(c == NULL){
			printf("Error! memory allocation failed!\n");
			fclose(out);
			fclose(frptr);
			return 1;
		}
		if(d == NULL){
			printf("Error! memory allocation failed!\n");
			fclose(out);
			fclose(frptr);
			free(c);
			return 1;
		}
		if(names == NULL){
			printf("Error! memory allocation failed!\n");
			fclose(out);
			fclose(frptr);
			free(c);
			free(d);
			return 1;
		}

		
		/* Loops through the start of the file to retrieve each road's primary data*/
		for (i = 0; i < n; i++) {
			fgets(line, SIZE, frptr);
			sscanf(line, "%s %d %d", names+(i*SIZE), c+i , d+i);
		}
		
		/* Loops through the remaining elements of the file to retrieve each intersetction's data*/
	        for (i = 0; i < m; i++) {
	                fgets(line, SIZE, frptr);
	                sscanf(line, "%d %d", c+i+n , d+i+n);
	        }
		
	
		data = iterate(n, m, c, d);
		
		/* The start of iterations to check each roads max rank */	
		for (i = 0; i < n; i++){
			fprintf(out, "%s ", names+(i*SIZE));
			fprintf(out, "%d\n", highestRank(i, n, m, c, data));
		}
	
		fgets(line, SIZE, frptr);
		sscanf(line, "%d %d", &n, &m);	/*scans for either the next iterations parameters 
						  or the end of the document*/
		free(c);
		free(d);
		free(data);
		free(names);
	}

	printf("Output file: blazcar_c1.out created successfully.\n");
	fclose(out);
	fclose(frptr);
	return 0;
}
