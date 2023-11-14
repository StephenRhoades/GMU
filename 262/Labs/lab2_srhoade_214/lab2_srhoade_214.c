/* 
 * Stephen Rhoades G01369048
 * CS 262, Lab section lab214
 * lab2: This program aims to calculate the BSA of an individual
 *  based on user input in response to prompts. 
 */

#include <stdio.h>
#include <math.h> 
#define SIZE 30 
#define V1 0.007184
#define V2 0.425
#define V3 0.725

int main()
{
	char inBuff[SIZE]; /*character array(String)*/
	float weight, height; /* weight(kg), height(cm)*/
	double bsa; /*BSA (m^2)*/

	printf("\tInput height(cm): "); /*prints the contents*/
	fgets(inBuff, SIZE,stdin); /*gets a string from stdin and saves at inBuff array */
	sscanf(inBuff, "%f",&height); /*copys a string from inBuff and parses a string as float value */

	printf("\tInput weight(kg): ");
	fgets(inBuff, SIZE,stdin);
	sscanf(inBuff, "%f",&weight);
	
	bsa = V1 * pow(weight, V2) * pow(height, V3);
	printf("\tThe height is: %.1f cms\n\tThe weight is: %.1f kgs\n\tBSA: %.4f meter square\n",height,weight, bsa);
	return 0;
}
