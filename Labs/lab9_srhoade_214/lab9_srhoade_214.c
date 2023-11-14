/* Stephen Rhoades G01369048
 * CS 262, Lab Section 214
 * Lab9: Structures and Arrays with Dynamic Memory
 */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 40


typedef struct date {
	int Month, Day, Year;
} date;

typedef struct employee{
	int ID;
	char FirstName[SIZE/2], LastName[SIZE/2];
	date DOB;
	double Salary;
} employee;

void printData(employee * data, int size) {
	int i;
	employee cur;
	char name[SIZE], dateStr[15];
	printf("*************************************************************\n");
	printf("\t%-8s %-20s %-10s %-15s\n", "ID", "Name", "DOB", "Salary");
	for (i = 0; i < size; i ++){
		cur = *(data+i);
		sprintf(name, "%s %s", cur.FirstName, cur.LastName);
		sprintf(dateStr, "%d/%d/%d", cur.DOB.Month, cur.DOB.Day, cur.DOB.Year);
		printf("\t%-8d %-20.20s %-10s %-15.2f\n", cur.ID, name , dateStr, cur.Salary);
	}
	printf("*************************************************************\n");
}

void printEmployee(employee data){
	printf("*************************************************************\n");
	printf("\tID: %d\n", data.ID);
	printf("\tFirst Name: %s\n", data.FirstName);
	printf("\tLast Name: %s\n", data.LastName);
	printf("\tDOB: %d/%d/%d\n", data.DOB.Month, data.DOB.Day, data.DOB.Year);
	printf("\tSalary: %.2f\n", data.Salary);
	printf("*************************************************************\n");

}

void search(char * inBuff, employee ** emps, int size){
	int i, ID;

	printf("\n**Search For Employee Data by ID**\n");

	printf("Enter employee's ID:");
        fgets(inBuff, SIZE, stdin);
        while(sscanf(inBuff, "%d", &ID) < 1){
                printf("Please enter an Integer value for employee's ID:");
                fgets(inBuff, SIZE, stdin);
        }

        for(i = 0; i < size; i++) {
                if (ID == (*(*emps + i)).ID) {
                       printEmployee((*(*emps + i))) ;
		       return;
                }
        }
	printf("ID Not Found\n");
	return;
}

int insert(char * inBuff, employee ** emps, int size){
	employee new;
	int i;
	
	printf("\n**Insert Data For New Employee**\n");

	printf("Enter employee's ID: ");
	fgets(inBuff, SIZE, stdin);
	while(sscanf(inBuff, "%d", &new.ID) < 1 || new.ID < 0){
		if (new.ID < 0)
			printf("ID value must be positive and less than 2147483647: ");
		else 
			printf("Please enter an Integer value for employee's ID: ");
		fgets(inBuff, SIZE, stdin);
	}
	
	for(i = 0; i < size; i++) {
		if (new.ID == (*(*emps + i)).ID) {
			printf("Error! ID is already in the database.\n");
			printf("Returning to menu.\n");
			return 0;
		}
	}

	printf("Enter employee's first and last name: ");
	fgets(inBuff, SIZE, stdin);
	while (sscanf(inBuff, "%s %s", new.FirstName, new.LastName) < 2) {
                printf("Please enter employee's name in format \"First Last\": ");
		fgets(inBuff, SIZE, stdin);
	}
	
	printf("Enter employee's date of birth in the form Month Day Year: ");
	fgets(inBuff, SIZE, stdin);
	while(sscanf(inBuff, "%d %d %d", &new.DOB.Month, &new.DOB.Day, &new.DOB.Year) < 3 ||
			 new.DOB.Month < 0 || new.DOB.Day < 0 || new.DOB.Year < -9999 ||
			 new.DOB.Month > 12 || new.DOB.Day > 31 || new.DOB.Year > 9999) {
		printf("Please enter valid employee's date of birth in format \"12 30 2020\": ");
                fgets(inBuff, SIZE, stdin);
	}

	printf("Enter employee's salary: ");
	fgets(inBuff, SIZE, stdin);
	while(sscanf(inBuff, "%lf", &new.Salary) < 1) {
		printf("Enter employee's salary in digit form: ");
		fgets(inBuff, SIZE, stdin);
	}
	
	*(*emps + size) = new;
	return 1;
}

int update(char * inBuff, employee ** emps, int size) {
	int ID, i, input;
	
	printf("\n**Update Employee Data**\n");

	printf("Enter employee's ID: ");
	fgets(inBuff, SIZE, stdin);
	while(sscanf(inBuff, "%d", &ID) < 1){
		printf("Please enter an Integer value for employee's ID: ");
		fgets(inBuff, SIZE, stdin);
	}

	for(i = 0; i < size; i++) {
		if (ID == (*(*emps + i)).ID) {
			printEmployee((*(*emps + i)));
			break;
		}
	}
	if (i == size) {
		printf("ID doesn't exist.\n");
		return 0;
	}
	printf("Which data do you want to update?\n");
	printf("\t1 - First Name\n");
	printf("\t2 - Last Name\n");
	printf("\t3 - DOB\n");
	printf("\t4 - Salary\n");
	printf("\t5 - Do not update\n");
	
	fgets(inBuff, SIZE, stdin);
        while(sscanf(inBuff, "%d", &input) < 1 || input > 5 || input < 1){
		printf("Option is not valid, try it again.\n");
		fgets(inBuff, SIZE, stdin);
	}
	switch (input) {
		case 1:
			printf("Enter replacement first name: ");
			fgets(inBuff, SIZE, stdin);
			while (sscanf(inBuff, "%s", (*(*emps + i)).FirstName) < 1) {
				printf("Please enter valid string for first name: ");
				fgets(inBuff, SIZE, stdin);
			}
			break;
		case 2:
			printf("Enter replacement last name: ");
			fgets(inBuff, SIZE, stdin);
			while (sscanf(inBuff, "%s", (*(*emps + i)).LastName) < 1) {
				printf("Please enter valid string for last name: ");
				fgets(inBuff, SIZE, stdin);
			}
			break;
		case 3:
			printf("Enter replacement date of birth: ");
                        fgets(inBuff, SIZE, stdin);
                        while (sscanf(inBuff, "%d %d %d", &(*(*emps + i)).DOB.Month, &(*(*emps + i)).DOB.Day, 
						&(*(*emps + i)).DOB.Year) < 3) {
                                printf("Please enter replacement date of birth in format \"12 30 2020\": ");
                                fgets(inBuff, SIZE, stdin);
                        }
			break;
		case 4:
			printf("Enter replacement salary: ");
                        fgets(inBuff, SIZE, stdin);
                        while (sscanf(inBuff, "%lf", &(*(*emps + i)).Salary) < 1) {
                                printf("Enter replacement salary in digit form: ");
                                fgets(inBuff, SIZE, stdin);
                        }
			break;
		case 5:
			return 1;
		default:
			printf("Error! input case out of bounds! (update())\n");
	}
	return 1;
}

int main() {
	char inBuff[SIZE];
	char input;
	int N = 3, size = 0;
	employee * employees;
	employees = malloc(sizeof(employee) * N);
	if (employees == NULL){
		printf("Error! Memory allocation failed for employees array.\n");
		return 1;
	}
	
	/*menu*/
	printf("Enter your Choice:\n");
	printf("'i' - Insert data\n");
	printf("'u' - Update data\n");
	printf("'s' - Search employee\n");
	printf("'p' - Print the database\n");
	printf("'q' - Quit\n");
	
	printf("\nmenu choice: ");
	fgets(inBuff, SIZE, stdin);
	sscanf(inBuff, "%c", &input);

	while(input != 'q' && input != 'Q') {
		switch(input){
			case 'i':
			case 'I':
				if(size == N) {
					N *= 2;
					employees = realloc(employees, sizeof(employee) * N);
					if (employees == NULL){
						printf("Error! Memory reallocation failed for employees array.\n");
						return 1;
					}
				}
				if (insert(inBuff, &employees, size)){
					size++;
				}
				break;
			case 'u':
                        case 'U':
				update(inBuff, &employees, size);
                                break;
			case 's':
                        case 'S':
                                search(inBuff, &employees, size);
				break;
			case 'p':
                        case 'P':
                                printData(employees, size);
				break;
			default:
				printf("%c is not a valid choice\nPlease re-enter the choice.\n", input);
				break;
		}

		printf("\nmenu choice: ");
		fgets(inBuff, SIZE, stdin);
        	sscanf(inBuff, "%c", &input);
	}
	free(employees);
	return 0;
}
