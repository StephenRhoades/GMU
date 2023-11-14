/* Stephen Rhoades G01369048
 * CS 262, Lab Section 214
 * Lab11: Bitwise Operators
 */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 50
#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d" 
#define BYTETOBINARY(byte) \
	(byte & 0x80 ? 1 : 0), \
	(byte & 0x40 ? 1 : 0), \
	(byte & 0x20 ? 1 : 0), \
	(byte & 0x10 ? 1 : 0), \
	(byte & 0x08 ? 1 : 0), \
	(byte & 0x04 ? 1 : 0), \
	(byte & 0x02 ? 1 : 0), \
	(byte & 0x01 ? 1 : 0)
#define PRINTBIN(x) printf(BYTETOBINARYPATTERN, BYTETOBINARY(x));


void setlsbs(unsigned char *p, unsigned char b0){
	int i,x, sub;
	unsigned char temp = 0;
	for (i = 0; i < 8; i ++){
		sub = 1;
		for (x = 0; x < i; x ++ ){
			sub *= 2;
		}	
		temp = b0 & sub;
		if (temp == 0){
			p[i] = p[i] & 0xFE;
		} else {
			p[i] = p[i] | 0x01;
		}
	}
}

unsigned char getlsbs(unsigned char *p){
	int i = 0;
	unsigned char lsb, b0 = 0;
	for (i = 0; i < 8; i ++){
		lsb = *(p+i) & 1;
		lsb = lsb << i;
		b0 = b0 | lsb;
	}

	return b0;
}

int main(int argc,char *argv[]){
	unsigned char *p; 
	unsigned char byte0;
	int i = 0, seed = 0;
	p = malloc(8);
	
	if (argc <= 1) {
		printf("Need a command line argument!\n");
		return 0;
	}
	if (sscanf(argv[1], "%d", &seed) < 1) {
		printf("Please enter an integer value for the command line argument!\n");
		return 0;
	}
	srand((unsigned)seed);

	for (i = 0; i < 8; i++ ){
		*(p+i) = rand()%256;
	}
	byte0 = rand()%256;
	
	printf("p values:\n");
	for (i = 0; i < 8; i++){
		printf("decimal: %d, binary: ", *(p+i));
		PRINTBIN(*(p+i)); printf("\n");
	}
	printf("\n");

	printf("byte0 value:\n");
	printf("decimal: %d, binary: ", byte0);
	PRINTBIN(byte0); printf("\n\n");
	
	setlsbs(p, byte0);
	printf("modified p values:\n");
        for (i = 0; i < 8; i++){
		printf("decimal: %d, binary: ", *(p+i));
		PRINTBIN(*(p+i)); printf("\n");
	}
	printf("\n");
	
	byte0 = getlsbs(p);
	
	printf("returned byte0 value:\n");
	printf("decimal: %d, binary: ", byte0);
	PRINTBIN(byte0); printf("\n");

	free(p);
	return 1;
}
