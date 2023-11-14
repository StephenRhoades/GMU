/* Stephen Rhoades G01369048
 * CS 262, Lab section 214
 * lab4: Discrete Analog Clock
 */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 60

/* This function is used to first check if the provided angle matches any angle that is formed from the 
 * particular clock moving at fixed intervals of 6 degrees.
 * At the same time the function will record each time that produceses a positive result inside the
 * integer array pointed to.
 * Lastly, the function keeps track of the number of positive results to both progress array indexing 
 * and record the size of the array.
 */
int angleExists(int A, int * arr, int * arrSize){
	int exists = 0;					/* 'boolean' truth value. */
	int m, h, mAng, hAng;
	int i = 0;
	for (h = 0; h < 24; h++){			/* iterates every hour*/
		for (m = 0; m < 60; m++){		/* iterates every minute*/
			mAng = 6 * m;
			hAng = (30 * h + 6 * (m/12))%360;
			if (A == abs(mAng - hAng) || A == 360 - abs(mAng - hAng)) {	/*compares the angle of the minute and hour hand*/
				exists = 1;		/* record truth value to return*/
				arr[i] = m + h * 60;
				i++;
				/*printf("%d\n", *arrSize);
				*printf("mins: %d, hours: %d\n", m, h);*/
			}
		}
	}
	*arrSize = i;		/* assigns the size of the array to the provided address*/
	return exists;

}

/*This function converts the integer value of minutes into two variables, one of minutes and the other hours,
 *then it prints out the two vaiables with a 24-hour military time format.
 */
void printTime(int min) {
	int hour = min / 60;
	min = min % 60;
	printf("%02d%02d\n", hour, min);	
}

int main() {
	int angle = -1;
	char inBuff[SIZE];
	int array[SIZE];
	int arrSize = 0;
	int val,i;
	do {
		printf("Please enter a whole angle value from 0 to 180.\n"); 
		fgets(inBuff, SIZE, stdin);
		sscanf(inBuff, "%d", &angle);	

	} while (angle < 0 || angle > 180 );	/*will continue prompting the user until appropriate input is provided*/
	
	
	if (angleExists(angle, array, &arrSize)) { /*this is where all the math happens when calling the function*/
		printf("There are %d different times where the two clock hands form a minimum angle of %d degrees.\n", arrSize, angle);
		printf("Those times are at:\n");
		for (i = 0; i < arrSize; i++) {	/*iterates each stored value in the array and calls the print function with said value*/ 
			/*printf("TEST! %d\n", val);*/
			val = array[i];
			printTime(val);
			
		}
	} else {
		printf("There is no time where the clock hands form a %d degree angle.\n", angle);
	}

	return 0;
}
