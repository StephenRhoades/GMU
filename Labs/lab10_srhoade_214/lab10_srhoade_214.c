/* Stephen Rhoades G01369048
 * CS 262, Lab Section 214
 * Lab10: Friends Birthday List
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 50

typedef struct Data{
	char * name;
	int dob, mob, yob;
	struct Data * next;
} Data;

Data * make_node(char * name, int dob, int mob, int yob){
	Data * newDate = malloc(sizeof(Data));
	newDate->next = NULL;
	newDate->name = malloc(SIZE);
	newDate->name = strncpy(newDate->name,name, SIZE);
	newDate->dob = dob;
	newDate->mob = mob;
	newDate->yob = yob;
	return newDate;
}

int insertNode(Data * dummy, Data data) {
	Data * current = dummy->next;
        Data * prev = dummy;
	Data * newNode;
	while(current != NULL){
		if (!strcmp(current->name, data.name)){
			printf("Name already present!\n");
			return 0;
		}
		current = current->next;
	}
	current = dummy->next;
	while(current != NULL && (current->mob < data.mob || 
			(current->mob == data.mob && ( current->dob < data.dob || 
			(current->dob == data.dob && (current->yob < data.yob || 
			(current->yob == data.yob && strcmp(current->name, data.name) < 0) ))))) ){
		prev = current;
		current = current->next;
	}
	newNode = make_node(data.name, data.dob, data.mob, data.yob);
	newNode->next = prev->next;
	prev->next = newNode;
	return 1;
}

int insert(Data * dummy, char * inBuff) {
	Data new;
	int x = 0;
	new.name = malloc(SIZE);
	printf("*** Insert data ***\n");
	printf("Name: ");
	fgets(inBuff, SIZE, stdin);
	while(sscanf(inBuff, "%[^\n]", new.name) < 1){
		printf("Invalid input!\nName: ");
		fgets(inBuff, SIZE, stdin);
	}
	printf("Month of birth: ");
	fgets(inBuff, SIZE, stdin);
	while(sscanf(inBuff, "%d", &new.mob) < 1 || new.mob > 12 || new.mob < 1){
		printf("Invalid input! please enter in a digit from [1-12]\nMonth of birth: ");
		fgets(inBuff, SIZE, stdin);
	}
	printf("Day of birth: ");
	fgets(inBuff, SIZE, stdin);
	while(sscanf(inBuff, "%d", &new.dob) < 1 || new.dob > 31 || new.dob < 1){
		printf("Invalid input! please enter in a digit from [1-31]\nDay of birth: ");
		fgets(inBuff, SIZE, stdin);
	}
	printf("Year of birth: ");
	fgets(inBuff, SIZE, stdin);
	while(sscanf(inBuff, "%d", &new.yob) < 1){
		printf("Invalid input!\nYear of Birth: ");
		fgets(inBuff, SIZE, stdin);
	}
	x = insertNode(dummy, new);
	free(new.name);
	return x;
}

Data * deleteNode(Data * dummy, Data data) {
	Data *current = dummy->next;
	Data * prev = dummy;
	Data * deleted = NULL;
	while(current != NULL){
		if(current->mob == data.mob && current->dob == data.dob &&
			current->yob == data.yob && !strcmp(current->name, data.name)) {
			prev->next = current->next;
			deleted = &data;
			free(current->name);
			free(current);
			break;
		}
		prev = current;
		current = current->next;
	}
	return deleted;
}

Data * delete(Data * dummy, char *inBuff) {
	Data data;
        Data * deleted = NULL;
        data.name = malloc(SIZE);

        printf("*** Delete data ***\n");
        printf("Name: ");
        fgets(inBuff, SIZE, stdin);
        while(sscanf(inBuff, "%[^\n]", data.name) < 1){
                printf("Invalid input!\nName: ");
                fgets(inBuff, SIZE, stdin);
        }
        printf("Month of birth: ");
        fgets(inBuff, SIZE, stdin);
        while(sscanf(inBuff, "%d", &data.mob) < 1 || data.mob > 12 || data.mob < 1){
                printf("Invalid input! please enter in a digit from [1-12]\nMonth of birth: ");
                fgets(inBuff, SIZE, stdin);
        }
        printf("Day of birth: ");
        fgets(inBuff, SIZE, stdin);
        while(sscanf(inBuff, "%d", &data.dob) < 1 || data.dob > 31 || data.dob < 1){
                printf("Invalid input! please enter in a digit from [1-31]\nDay of birth: ");
                fgets(inBuff, SIZE, stdin);
        }
        printf("Year of birth: ");
        fgets(inBuff, SIZE, stdin);
        while(sscanf(inBuff, "%d", &data.yob) < 1){
                printf("Invalid input!\nYear of Birth: ");
                fgets(inBuff, SIZE, stdin);
        }
	deleted = deleteNode(dummy, data);
	
        free(data.name);
        return deleted;
}

void printList(Data * dummy){
	Data * current = dummy->next;
	printf("************ List content ************\n");
	while(current != NULL){
		printf("%02d/%02d/%d %s\n", current->mob, current->dob, current->yob, current->name);
		current = current->next;
	}
}

void free_all(Data * dummy){
	Data * temp = NULL;
	while(dummy != NULL){
		temp = dummy->next;
		free(dummy->name);
		free(dummy);
		dummy = temp;
	}
	printf("Memory free Successfully!\n");
}

void print_menu(int listLength){
	printf("\n************ Friends birthday list ************\n");
	printf("Friends in the list: %d\n", listLength);
	printf("   (1)\tInsert data\n");
	printf("   (2)\tDelete data\n");
	printf("   (3)\tPrint list\n");
	printf("   (4)\tQuit\n");
	printf("*****************************************\n");
	printf("Enter your choice: ");
}

int main() {
	int listLength = 0, input = 0;
	char inBuff[SIZE];
	Data * dummy = make_node("HEAD", -1, -1, -1); 

	while (input != 4){
		print_menu(listLength);
		fgets(inBuff, SIZE, stdin);
		sscanf(inBuff, "%d", &input);
		printf("\n");
		switch(input) {
			case 1:
				if(insert(dummy, inBuff)) {
					listLength++;
				}
				break;
			case 2:
				if(delete(dummy, inBuff) == NULL){
					printf("\n################ Data Does not exist ###############\n");
				} else {
					listLength--;
				}
				break;
			case 3:
				printList(dummy);
				break;
			case 4:
				break;
			default:
				printf("Input does not match a menu option please input a digit [1-4]\n");
		}
	
	}	

	free_all(dummy);
	return 1;
}

