/* Stephen Rhoades G01369048
 * CS 262, Lab section 214
 * lab3: implimenting branching, loops, and functions. Control flow.
 *
 *
 */

#include <stdio.h>
#define SIZE 30

char askIn(), askChar(), menu();
int askNum(), valCheck(int N, char C);
void printLine(int N, char C), printRect(int N, char C), printSquare(int N, char C), printTri(int N, char C);


int valCheck(int N, char C){
	int clear = 1;
	if (N == 0 || C == 0) {
		printf("\nERROR! A necesary value has not been set.\n");
		clear = 0;
	}
	if (N == 0 )
		printf("Please set the size of the shape by typing 'n' or 'N'.\n");
	if (C == 0)
		printf("Please set the character used to draw the shape by typing 'c' or 'C'.\n");
	return clear;

}

void printLine(int N, char C) {
	int i;
	printf("This function prints a line size %d with the character '%c'.\n", N, C); 
	for ( i = 0; i < N; i++){
		printf("%c\n", C);
	}
}

void printRect(int N, char C) {
	int y, x;
	printf("This function prints a rectangle size %d with the character '%c'.\n", N, C);
	for (y = 0; y < N; y++) {
		for (x = 0; x < N+4; x++) {
			printf("%c", C);
		}
		printf("\n");
	}
}

void printSquare(int N, char C) {
	int y, x;
	printf("This function prints a square size %d with the character '%c'.\n", N, C);
	for(y = 0; y < N; y++){
		for (x = 0; x < N; x++) {
			printf("%c", C);
		}
		printf("\n");
	}
}

void printTri(int N, char C) {
	int y, x;
	printf("This function prints a trianlge size %d with the character '%c'.\n", N, C);
	for(y = 0; y < N; y++){
		for (x = 0; x < y +1; x++) {
			printf("%c", C);
		}
		printf("\n");
	}
}

char askIn() {
	char inBuff[SIZE];
	char in;
	printf("\nEnter a character from the menu: \n");
	fgets(inBuff, SIZE, stdin);
	sscanf(inBuff, "%c", &in);
	return in;
}

char askChar() {
	char inBuff[SIZE];
	char ans;
	printf("Enter a character to be used to make shapes: \n");
	fgets(inBuff, SIZE, stdin);
	sscanf(inBuff, "%c", &ans);
	return ans;
}

int askNum() {
	char inBuff[SIZE];
	int ans = 0;
	printf("Enter a number from 1-15 for the size of the shapes: \n");
	fgets(inBuff, SIZE, stdin);
	sscanf(inBuff, "%d", &ans);
	while (ans > 15 || ans < 1) {
		printf("Invalid Entry!\nPlease enter a number from 1-15: \n");
		fgets(inBuff, SIZE, stdin);
		sscanf(inBuff, "%d", &ans);
	}
	return ans;
}

char menu(){

	printf("\nMenu Choice\t\t\tInput Choices\n");
        printf("Enter/Change Character\t\t'C' or 'c'\n");
	printf("Enter/Change Number\t\t'N' or 'n'\n");
	printf("Draw Line\t\t\t'L' or'l'\n");
	printf("Draw Square\t\t\t'S' or 's'\n");
	printf("Draw Rectangle\t\t\t'R or 'r'\n");
	printf("Draw Triangle\t\t\t'T or 't'\n");
	printf("Quit Program\t\t\t'Q' or 'q'\n");
	return askIn();
}

int main(){
	char in, C;
	int N;
	in = menu();
	C = 0;
	N = 0;
	
	while ( !(in == 'q' || in == 'Q') ){
		
		switch(in) {
			case 'C' :
			case 'c' :
				C = askChar();
				break;
			case 'N' :
			case 'n' :
				N = askNum();
				break;
			case 'L' :
			case 'l' :
				if (valCheck(N, C)) {
					printLine(N, C);
				} else {
					in = menu();
					continue;
				}
				break;
			case 'S' :
			case 's' :
				if (valCheck(N,C)) {
					printSquare(N, C);
				} else {
					in = menu();
					continue;
				}
				break;
			case 'R' :
			case 'r' :
				if (valCheck(N,C)) {
					printRect(N, C);
				} else {
					in = menu();
					continue;
				}
				break;
			case 'T' :
			case 't' :
				if (valCheck(N,C)) {
					printTri(N, C);
				} else {
					in = menu();
					continue;
				}
				break;
			default:
				printf("Invalid Entry!\n");
				in = menu();
				continue;
		}
		in = askIn();
		

	}
	printf("thank you, have a nice day.\n");
	return 0;
}


