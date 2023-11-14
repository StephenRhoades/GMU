/* Stephen Rhoades G01369048
 * CS 262, Lab section 214
 * lab5: The Title of the Movie of My Life
 */

#include <stdio.h>
#include <string.h>
#define SIZE 20
#define WSIZE 50

void get_adjective(char letter, char adjective[]) {
	if (letter >= 'A' && letter <= 'E') {
		strcat(adjective, "The awesome");
	} 
	else if (letter >= 'F' && letter <= 'J') {
		strcat(adjective, "The funny");
	}
	else if (letter >= 'K' && letter <= 'O') {
		strcat(adjective, "The dangerous");
	}
	else if (letter >= 'P' && letter <= 'T') {
		strcat(adjective, "The lovely");
	}
	else if (letter >= 'U' && letter <= 'Z') {
		strcat(adjective, "The electrifying");
	}
	else {
		printf("ERROR! input character mismatch!\n");
	}
}

void get_subject(char month[], char subject[]) {
	if (strcmp(month, "JAN") == 0 || strcmp(month, "FEB") == 0 ||
		strcmp(month, "MAR") == 0) {
                strcat(subject, "biography");
        }
        else if (strcmp(month, "APR") == 0 || strcmp(month, "MAY") == 0 ||
                strcmp(month, "JUN") == 0) {
		strcat(subject, "revenge");
        }
	else if (strcmp(month, "JUL") == 0 || strcmp(month, "AUG") == 0 ||
                strcmp(month, "SEP") == 0) {
        	strcat(subject, "battle");
	}
	else if (strcmp(month, "OCT") == 0 || strcmp(month, "NOV") == 0 ||
                strcmp(month, "DEC") == 0) { 
		strcat(subject, "fairy tale");
	}
	else {
                printf("ERROR! input month mismatch!\n");
        }	
}

void get_complement(int digit, char complement[]) {
	if (digit == 0 || digit == 1) {
                strcat(complement, "of a movie star");
        }
        else if (digit == 2 || digit == 3) {
                strcat(complement, "of a hero");
        }
        else if (digit == 4 || digit == 5) {
                strcat(complement, "of a jedi");
        }
        else if (digit == 6 || digit == 7) {
                strcat(complement, "of an ogre");
        }
        else if (digit == 8 || digit == 9) {
                strcat(complement, "of a dreamer");
        }
        else {
                printf("ERROR! input digit out of bounds!\n");
        }
}

int main() {
	char inBuff[WSIZE];
	char adjective[SIZE] = "";
        char subject[SIZE] = "";
	char complement[SIZE] = "";
	char month[SIZE] = "";
	char movieTitle[WSIZE] = "";
	char letter, finished;
	int digit, i;
	
	printf("*** Welcome to the Title Movie creator program ***\n");
	finished = 'N';

	while (finished != 'y' && finished != 'Y') {
		adjective[0] = 0;
		subject[0] = 0;
		complement[0] = 0;
		movieTitle[0] = 0;
		
		printf("\tEnter the first letter of your last name [A-Z] ");
		fgets(inBuff, WSIZE, stdin);
		sscanf(inBuff, "%c", &letter);
		
		while (letter < 'A'|| letter > 'z' || (letter > 'Z' && letter < 'a')) {
			printf("\tERROR! Invalid Input!\n\tEnter the first letter of your last name [A-Z] ");
	                fgets(inBuff, WSIZE, stdin);
			sscanf(inBuff, "%c", &letter);
		}
		if (letter > 'Z') 
			letter -= 32;
	
		printf("\tEnter your birth month [JAN|FEB|...|DEC] ");
		fgets(inBuff, WSIZE, stdin);
		sscanf(inBuff, "%[^\n]", month);
		
		for (i = 0; i < strlen(month); i++){
			if (month[i] >= 'a' && month[i] <= 'z')
				month[i] -= 32;
		}
		while (!(strcmp("JAN", month) == 0|| strcmp("FEB", month) == 0 ||
			strcmp("MAR", month) == 0 || strcmp("APR", month) == 0 ||
			strcmp("MAY", month) == 0 || strcmp("JUN", month) == 0 ||
			strcmp("JUL", month) == 0 || strcmp("AUG", month) == 0 ||
			strcmp("SEP", month) == 0 || strcmp("OCT", month) == 0 ||
			strcmp("NOV", month) == 0 || strcmp("DEC", month) == 0 )) {
			
			printf("\tERROR! Invalid input!\n\tEnter your birth month [Jan|FEB|...|DEC] ");
			fgets(inBuff, WSIZE, stdin);
			sscanf(inBuff, "%[^\n]", month);
		
			for (i = 0; i < strlen(month); i++){
				if (month[i] >= 'a' && month[i] <= 'z')
					month[i] -= 32;
			}
		}
	
		printf("\tEnter the last digit of your cellphone [0-9] ");
		fgets(inBuff, SIZE, stdin);
		sscanf(inBuff, "%d", &digit);
		
		while (digit > 9 || digit < 0) {
			printf("\tERROR! Invalid input!\n\tEnter the last digit of your cellphone [0-9] ");
			fgets(inBuff, SIZE, stdin);
			sscanf(inBuff, "%d", &digit);
	
		}
		get_adjective(letter, adjective);
		get_subject(month, subject);
		get_complement(digit, complement);
		
		strcat(movieTitle, adjective);
		strcat(movieTitle, " ");
		strcat(movieTitle, subject);
		strcat(movieTitle, " ");
		strcat(movieTitle, complement);
		
		printf("\nThe Movie Title for your life is:\n\t%s\n\n",movieTitle);
		
		printf("Do you want to quit [Y|y]? ");
		fgets(inBuff, WSIZE, stdin);
		sscanf(inBuff, "%c", &finished);

	}
	return 0;
}
