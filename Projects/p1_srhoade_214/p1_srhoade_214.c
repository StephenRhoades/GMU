/* Stephen Rhoades G01369048
 * CS 262, Lab section 214
 * Project 1: Math R@ce
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 36

 
/* This function takes in a character as input and returns 
 * either 1 if the character matches a menu option or 0 if not.
 */	
int is_valid_option(char input) {
	  /* simple logic returning true if any of the options match the input
	  */
	  if (input == '1' || input == '2' || input == '3' || input == '4' || input == '5'){
	  	return 1;
	  }
	  return 0;
}
	
	
/*This function prints out the current race status indicated by the int parameter.
 * The '@' symbol indicates how far along the track you are with spaces indcated by an '_',
 * and the finish line is represented by '%';
 */	
void race_status(int progress){
	  int i;
	  printf("Race counter: %d/10\n", progress);
	  for (i = 0; i < progress; i++) { /*prints out an '_' and tab for each correct answer */
	  	printf("_\t");
	  }
	
	  printf("@\t");			/*indicates the current place*/
	  
	  for(i = progress + 1; i < 10; i++) { /*prints out any '_' remainig to the limit of 9 total*/
	  	printf("_\t");
	  }
	
	  if (progress < 10) 		/*unless the race is finished end the line with e the '%'*/
	  	printf("%c", '%');
	
	  printf("\n\n");
}	

	
/* This is the addition function which receives the character array of the given username to
 *  print at the conclusion.
 * It prints the header and initial race progress and prompts the user to start before looping
 *  the main function 10 times before printing the results.
 * In each loop the funtion generates two random numbers [0-100] that add to [0-100] making sure
 *  they don't match the previous values (if they exist).
 * Then the user is asked what the two values' sum is and to select option 'a', 'b', or 'c' where
 *  one value is the correct answer and the others are unique random values [0-100].
 * It then updates the user's progress if answered correctly before printing the race progess.
 * After the loop ends the function will congratuale the user if each question was answered correctly
 *  or listing how many more correct answers were needed if not.
 * The function is then terminated upon the user inputing a newline.
 */	
void addition(char * name) {
	int i, val1, val2, past1, past2, opt, wrong1, wrong2;
	int progress = 0;
	char inBuff[SIZE + 1];
	char ans1, ans2, in;
	
	printf("\n");
	printf("*******************************\n");
	printf("*    Math R@ce - Addition     *\n");
	printf("*******************************\n");
	printf("\n");
	
	race_status(progress);
	printf("<Start>");
	fgets(inBuff, SIZE, stdin);
	
	past1 = -1;
	past2 = -1;
	for (i = 0; i < 10; i++){
		do {
			val1 = rand() % 101;
			val2 = rand() % 101;
		} while (val1 + val2 > 100|| (past1 == val1 && past2 == val2) || (past1 == val2 && past2 == val1));
		past1 = val1;
		past2 = val2;
		
	
		printf("\nOperation %d:\n%d + %d\n", i+1, val1, val2);
		opt = rand() % 3;
		do {
			wrong1 = rand()%101;
		} while (wrong1 == val1 + val2);
		
		do {
	                 wrong2 = rand()%101;
		} while (wrong2 == val1 + val2 || wrong2 == wrong1);
	
		switch (opt) {
			case 0:
				ans1 = 'a';
				ans2 = 'A';
				printf("a %d\n", val1 + val2);
				printf("b %d\n", wrong1);
				printf("c %d\n", wrong2);
				break;
			case 1:
	                        ans1 = 'b';
				ans2 = 'B';
				printf("a %d\n", wrong1);
	                        printf("b %d\n", val1 + val2);
				printf("c %d\n", wrong2);
				break;
			case 2:
			        ans1 = 'c';
			        ans2 = 'C';
				printf("a %d\n", wrong1);
			        printf("b %d\n", wrong2);
				printf("c %d\n", val1 + val2);
				break;
			default:
				printf("ERROR! rand num out of bounds");
				break;
		}
		
		printf("\n");
		do {
			printf("Answer: ");
			fgets(inBuff, SIZE, stdin);
			sscanf(inBuff, "%c", &in);
		} while (in != 'a' && in != 'A' && in != 'b' && in != 'B' && in != 'c' && in != 'C');
	
		if (ans1 == in || ans2 == in) {
			printf("Correct!\n\n");
			progress++;
		} else {
			printf("Incorrect\n\n");
		}
		race_status(progress);
	}
	
	if (progress == 10){
		printf("Congratulations %s! You reached the finish line.\n", name);
	} else {
		printf("You did not finish the race %s,\n", name);
		printf("You were missing %d steps to reach the finish line.\n\n", 10 - progress);
	}
	
	printf("Press <return> to go back to the menu:"); 
	fgets(inBuff, SIZE, stdin);
}	
	

/* This is the addition function which receives the character array of the given username to
 *  print at the conclusion.
 * It prints the header and initial race progress and prompts the user to start before looping
 *  the main function 10 times before printing the results.
 * In each loop the funtion generates two random numbers [0-100] that subtract to [0-100] making sure
 *  they don't match the previous values (if they exist).
 * Then the user is asked what the two values' difference is and to select option 'a', 'b', or 'c' where
 *  one value is the correct answer and the others are unique random values [0-100].
 * It then updates the user's progress if answered correctly before printing the race progess.
 * After the loop ends the function will congratuale the user if each question was answered correctly
 *  or listing how many more correct answers were needed if not.
 * The function is then terminated upon the user inputing a newline.
 */
void subtraction(char * name) {
	int i, val1, val2, past1, past2, opt, wrong1, wrong2;
        int progress = 0;
        char inBuff[SIZE];
        char ans1, ans2, in;

        printf("\n");
        printf("*******************************\n");
        printf("*   Math R@ce - Subtraction   *\n");
        printf("*******************************\n");
        printf("\n");

	race_status(progress);
	printf("<Start>");
	fgets(inBuff, SIZE, stdin);
	
	past1 = -1;
	past2 = -1;
	for (i = 0; i < 10; i++){
		
		do {
	        	val1 = rand() % 101;
                        val2 = rand() % 101;
                } while (val1 - val2 < 0 || (past1 == val1 && past2 == val2));
                past1 = val1;
		past2 = val2;

		printf("\nOperation %d:\n%d - %d\n", i+1, val1, val2);
		opt = rand() % 3;
		
		do {
                        wrong1 = rand()%101;
                } while (wrong1 == val1 - val2);
		
		do {
			wrong2 = rand()%101;
                } while (wrong2 == val1 - val2 || wrong2 == wrong1);
		
		switch (opt) {
                        case 0:
                                ans1 = 'a';
                                ans2 = 'A';
                                printf("a %d\n", val1 - val2);
                                printf("b %d\n", wrong1);
                                printf("c %d\n", wrong2);
                                break;
                        case 1:
                                ans1 = 'b';
                                ans2 = 'B';
                                printf("a %d\n", wrong1);
                                printf("b %d\n", val1 - val2);
                                printf("c %d\n", wrong2);
                                break;
                        case 2:
                                ans1 = 'c';
                                ans2 = 'C';
                                printf("a %d\n", wrong1);
                                printf("b %d\n", wrong2);
                                printf("c %d\n", val1 - val2);
                                break;
			default:
                                printf("ERROR! rand num out of bounds");
                                break;
                }
		printf("\n");
                do {
                        printf("Answer: ");
                        fgets(inBuff, SIZE, stdin);
                        sscanf(inBuff, "%c", &in);
                } while (in != 'a' && in != 'A' && in != 'b' && in != 'B' && in != 'c' && in != 'C');

                if (ans1 == in || ans2 == in) {
                        printf("Correct!\n\n");
                        progress++;
                } else {
                        printf("Incorrect\n\n");
                }
                race_status(progress);
        }

        if (progress == 10){
                printf("Congratulations %s! You reached the finish line.\n", name);
        } else {
                printf("You did not finish the race %s,\n", name);
                printf("You were missing %d steps to reach the finish line.\n\n", 10 - progress);
        }
        printf("Press <return> to go back to the menu:");
        fgets(inBuff, SIZE, stdin);
}


/* This is the addition function which receives the character array of the given username to
 *  print at the conclusion.
 * It prints the header and initial race progress and prompts the user to start before looping
 *  the main function 10 times before printing the results.
 * In each loop the funtion generates two random numbers [0-100] that mutilpy to [0-100] making sure
 *  they don't match the previous values (if they exist).
 * Then the user is asked what the two values' product is and to select option 'a', 'b', or 'c' where
 *  one value is the correct answer and the others are unique random values [0-100].
 * It then updates the user's progress if answered correctly before printing the race progess.
 * After the loop ends the function will congratuale the user if each question was answered correctly
 *  or listing how many more correct answers were needed if not.
 * The function is then terminated upon the user inputing a newline.
 */
void multiplication(char * name) {
	int i, val1, val2, past1, past2, opt, wrong1, wrong2;
        int progress = 0;
	char inBuff[SIZE];
	char ans1, ans2, in;

        printf("\n");
	printf("*******************************\n");
        printf("*  Math R@ce - Multiplication *\n");
        printf("*******************************\n");
        printf("\n");

	race_status(progress);
	printf("<Start>");
	fgets(inBuff, SIZE, stdin);

	past1 = -1;
	past2 = -1;
	for (i = 0; i < 10; i++){
        	do {
                        val1 = rand() % 101;
                        val2 = rand() % 101;
                } while (val1 * val2 > 100|| (past1 == val1 && past2 == val2) || (past1 == val2 && past2 == val1));
		past1 = val1;
		past2 = val2;

                printf("\nOperation %d:\n%d * %d\n", i+1, val1, val2);
                opt = rand() % 3;
		
		do {
                        wrong1 = rand()%101;
                } while (wrong1 == val1 * val2);
		
                do {
                         wrong2 = rand()%101;
                } while (wrong2 == val1 * val2 || wrong2 == wrong1);
		
                switch (opt) {
                        case 0:
                                ans1 = 'a';
                                ans2 = 'A';
                                printf("a %d\n", val1 * val2);
                                printf("b %d\n", wrong1);
                                printf("c %d\n", wrong2);
                                break;
                        case 1:
                                ans1 = 'b';
                                ans2 = 'B';
                                printf("a %d\n", wrong1);
                                printf("b %d\n", val1 * val2);
                                printf("c %d\n", wrong2);
                                break;
                        case 2:
                                ans1 = 'c';
                                ans2 = 'C';
                                printf("a %d\n", wrong1);
                                printf("b %d\n", wrong2);
                                printf("c %d\n", val1 * val2);
                                break;
                        default:
                                printf("ERROR! rand num out of bounds");
                                break;
                }
		printf("\n");
                do {
                        printf("Answer: ");
                        fgets(inBuff, SIZE, stdin);
                        sscanf(inBuff, "%c", &in);
                } while (in != 'a' && in != 'A' && in != 'b' && in != 'B' && in != 'c' && in != 'C');

                if (ans1 == in || ans2 == in) {
                        printf("Correct!\n\n");
                        progress++;
                } else {
                        printf("Incorrect\n\n");
                }
                race_status(progress);
        }

        if (progress == 10){
                printf("Congratulations %s! You reached the finish line.\n", name);
        } else {
                printf("You did not finish the race %s,\n", name);
                printf("You were missing %d steps to reach the finish line.\n\n", 10 - progress);
        }
        printf("Press <return> to go back to the menu:");
        fgets(inBuff, SIZE, stdin);
}


/* This is the division function which receives the character array of the given username to
 *  print at the conclusion.
 * It prints the header and initial race progress and prompts the user to start before looping
 *  the main function 10 times before printing the results.
 * In each loop the funtion generates two random numbers [0-100] that divide to [0-100] making sure
 *  they don't match the previous values (if they exist) and the denominator is not 0.
 * Then the user is asked what the two values' quotient is and to select option 'a', 'b', or 'c' where
 *  one value is the correct answer and the others are unique random values [0-100].
 * It then updates the user's progress if answered correctly before printing the race progess.
 * After the loop ends the function will congratuale the user if each question was answered correctly
 *  or listing how many more correct answers were needed if not.
 * The function is then terminated upon the user inputing a newline.
 */
void division(char * name) {
	int i, val1, val2, past1, past2, opt, wrong1, wrong2;
        int progress = 0;
	char inBuff[SIZE];
	char ans1, ans2, in;

        printf("\n");
	printf("*******************************\n");
        printf("*     Math R@ce - Division    *\n");
        printf("*******************************\n");
        printf("\n");

	race_status(progress);
	printf("<Start>");
	fgets(inBuff, SIZE, stdin);

	past1 = -1;
	past2 = -1;
	for (i = 0; i < 10; i++){
		do {
                        val1 = rand() % 101;
                        val2 = rand() % 100 + 1;
                } while (val1 % val2 > 0|| (past1 == val1 && past2 == val2));
		past1 = val1;
		past2 = val2;
		
                printf("\nOperation %d:\n%d / %d\n", i+1, val1, val2);
                opt = rand() % 3;
                do {
                        wrong1 = rand()%101;
                } while (wrong1 == val1 / val2);
		
                do {
                         wrong2 = rand()%101;
                } while (wrong2 == val1 / val2 || wrong2 == wrong1);
		
                switch (opt) {
                        case 0:
                                ans1 = 'a';
                                ans2 = 'A';
                                printf("a %d\n", val1 / val2);
                                printf("b %d\n", wrong1);
                                printf("c %d\n", wrong2);
                                break;
                        case 1:
                                ans1 = 'b';
                                ans2 = 'B';
                                printf("a %d\n", wrong1);
                                printf("b %d\n", val1 / val2);
                                printf("c %d\n", wrong2);
                                break;
                        case 2:
                                ans1 = 'c';
                                ans2 = 'C';
                                printf("a %d\n", wrong1);
                                printf("b %d\n", wrong2);
                                printf("c %d\n", val1 / val2);
                                break;
                        default:
                                printf("ERROR! rand num out of bounds");
                                break;
                }
		
		printf("\n");
                do {
                        printf("Answer: ");
                        fgets(inBuff, SIZE, stdin);
                        sscanf(inBuff, "%c", &in);
                } while (in != 'a' && in != 'A' && in != 'b' && in != 'B' && in != 'c' && in != 'C');

                if (ans1 == in || ans2 == in) {
                        printf("Correct!\n\n");
                        progress++;
                } else {
                        printf("Incorrect\n\n");
                }
                race_status(progress);
        }

        if (progress == 10){
                printf("Congratulations %s! You reached the finish line.\n", name);
        } else {
                printf("You did not finish the race %s,\n", name);
                printf("You were missing %d steps to reach the finish line.\n\n", 10 - progress);
        }
        printf("Press <return> to go back to the menu:");
        fgets(inBuff, SIZE, stdin);
}


/* This function prints out the menu of options for the user to choose from 1-5.
 * It then read the terminal for a valid input before returning the appropriate character.
 * If an invalid input is given it will print an error message and prompt the user until a valid 
 * input is provided.
 * This function also sets the random seed based on the machine clock each time it is called.
 */ 
char menu(){
	char input;
	char inBuff[SIZE];
	time_t t;
	srand((unsigned) time(&t));

	printf("\n");
        printf("1.\tAddition\n");
	printf("2.\tSubtraction\n");
	printf("3.\tMultiplication\n");
	printf("4.\tDivision\n");
        printf("5.\tQuit\n");
        printf("\nSelect an option: ");
        fgets(inBuff, SIZE, stdin);
        sscanf(inBuff, "%c", &input);
        while(!is_valid_option(input)){
        	printf("\nOption %c is not valid!\n", input);
        	printf("\nSelect an option: ");
        	fgets(inBuff, SIZE, stdin);
        	sscanf(inBuff, "%c", &input);
        }
	
	return input;

}


/* The main function starts by printing out the header of Math R@ce and asking for the user's name.(max 35 char)
 * It then initializes the menu, storing the returned value in an input vairable.
 * Then a while loop is maintained until the input matches the quit ooptino of the menu.
 * in the while loop a switch case calls the function that matches the input defaulting to an
 *  error message to catch any potential bugs in the code before calling the menu for a new input value.
 * Main finally prints a parting message to the user by name before returning.
 */ 
int main() {
	char inBuff[SIZE];	
	char name[SIZE];
	char input;
	printf("*******************************\n");
	printf("*     Welcome to Math R@ce    *\n");
	printf("*******************************\n");
	printf("\nPlayer's name:");
	
	fgets(inBuff, SIZE, stdin);
	sscanf(inBuff, "%[^\n]",name );
	
	input = menu();
	
	while(input != '5'){
		switch (input) {
			case '1': 
				addition(name);
				break;
			case '2':
				subtraction(name);
				break;
			case '3':
				multiplication(name);
				break;
			case '4':
				division(name);
				break;
			default:
				printf("ERROR! invalid input has been accepted!\n");
		}
		input = menu();	
	}
	
	printf("You are done %s,\nGood bye.\n",name);
	return 0;
}
