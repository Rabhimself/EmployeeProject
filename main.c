#include "header.h"

/*
	1) Add employee <EMAIL, ID VALIDATION>
	2) Display employee details
	3) Update employee
	4) Delete employee
	5) Display all employees by department
	6) Employee Report
*/


struct login
{
	char name[7];
	char pass[7];
	struct login *next;
};

main()
{	
	struct login *loginHead;
	struct employee *empHead;
	
	
	builder();
	loginHead = (struct login*)malloc(sizeof(struct login));
	loginHead = loginReader(&loginHead);
	doLogin(loginHead);

	//load employee file here

	empHead = loadEmployees();
	displayMenu(empHead);

}

//getPass uses getch() from the conio.h library, which gets a character without echoing
//if return was not pressed, it will instead echo an asterisk.
//function returns a 0 if the password passed in matches the password entered
int getPass(char pw[])
{
	char c;
	char pass[7];
	int i = 0;

	printf("Password: ");
	do 
	{
		
		c = _getch();
	  
		if(c != '\n') 
		{
			putchar('*');
			pass[i++] = c;
		}

	} while(i < 6 );
	pass[6] = '\0';
	return strcmp(pw,pass);
}
//linked list of logins will check against an entered PW
void doLogin(struct login *head)
{

	char password[7];
	
	char login[7];

	do
	{
		printf("Login: ");
		gets_s(login,6);
		strcpy_s(password, 7,searchLoginList(head, login));//searches the login list for the username entered and returns the password for that user
	}while(password == NULL);
	//check against linked list names

	//check against chosen struct password
	while(getPass(password) != 0)
	{
		printf("Incorrect password, try again.\n");
		system("pause");
		system("cls");
	}

}
struct login *loginReader(struct login **head)
{
	struct login *firstNode;
	struct login *tempNode;
	struct login *newNode;

	FILE *ptr_myFile;
	
	fopen_s(&ptr_myFile,"users.dat","r+b");

	if (ptr_myFile == NULL)
	{
		printf("Unable to open file!");
	}
	tempNode = (struct login*)malloc(sizeof(struct login));
	firstNode = (struct login*)malloc(sizeof(struct login));
	fread(firstNode,sizeof(struct login),1,ptr_myFile);
	*head = firstNode;

	while ( fread(tempNode,sizeof(struct login),1,ptr_myFile) != NULL) 
	{
		newNode = (struct login*)malloc(sizeof(struct login));
		*newNode = *tempNode;
		newNode->next = *head;
		*head = newNode;
	}

	fclose(ptr_myFile);
	return *head;

}
//just used to populate users.dat//
void builder()
{	
	FILE *ptr_myfile;
	
	struct login bill = {"bill","qwerty", NULL};
	struct login brad = {"brad","asdfgh", NULL};
	struct login barry = {"barry","zxcvbn", NULL};

	fopen_s(&ptr_myfile,"users.dat","wb");
	if (!ptr_myfile)
	{
		printf("Unable to open file!");
		return;
	}

	fwrite(&bill, sizeof(struct login), 1, ptr_myfile);
	fwrite(&brad, sizeof(struct login), 1, ptr_myfile);
	fwrite(&barry, sizeof(struct login), 1, ptr_myfile);

	fclose(ptr_myfile);
}
char * searchLoginList(struct login *head, char *s)
{
	struct login *temp;
	int i = 1;

	temp = (struct login*)malloc(sizeof(struct login));
	temp = head;
	
	while(temp != NULL)
	{

		if (strcmp(s,temp->name)==0)
		{
			printf("login found at login # %d \n", i);
			printf("    login: %s \n", temp->name);
			return temp->pass;
		}

		i++;
		temp = temp->next;
	}
	return NULL;
}
void displayMenu(struct employee *eHead)
{
	struct employee *head;
	int choice;
	system("cls");
	head = eHead;

	do
	{
		/*
		1) Add employee
		2) Display employee details
		3) Update employee
		4) Delete employee
		5) Display all employees by department
		6) Employee Report
		*/


		system("cls");
		printf("1: Add employee\n");
		printf("2: Delete Employee\n");
		printf("3: Add an employee to registry\n");
		printf("5: Display Employees by Department\n");
		printf("6: Search for an employee by ID number\n");
		printf("7: Department Report\n");
		printf("Enter a menu option: ");
		fflush(stdin);
		scanf_s("%d", &choice,1);	

		switch(choice)
		{
		case 1:
			addEmployee(&head);
			break;

		case 2:
			deleteEmp(&head, getEmpID());
			break;

		case 3:
			do
			{
				printf("1) Find Employee by Name\n ");
				printf("2) Find Employee by ID\n ");
				printf("Selection:");
				fflush(stdin);
				scanf_s("%d", &choice,1);
			}while(choice != 1 && choice != 2);

			switch(choice)
			{
				case 1:
					updateEmployee(findEmpName(head, getEmpName()));
					break;
				case 2:
					updateEmployee(findEmpID(head, getEmpID()));
					break;

			}
			break;

		case 4:
			//deleteFromStart(&head);
			break;

		case 5:
			listEmployees(head);
			break;

		case 6:
			
			findEmpID(head, getEmpID());
			system("pause");
			break;

		case 7:
			reporter(head);
			break;

		case 9:
			break;

		default:
			printf("Invalid choice.\n");
		}
	}while(choice != 9);

}
