#include "header.h"

struct employee
{
	int id;
	char name[40+1];
	char dept[20+1];
	double salary;
	char email[40+1];//validate on entry

	struct address
	{
		char street[40+1];
		char city[40+1];
		char prov[40+1];//state/prov/county

	}addr;

	struct date
	{
		int day;
		int month;
		int year;
	}hireDate;

	struct employee *next;
};
struct employee *loadEmployees()
{
	//declarations
	struct employee *head;
	struct employee *firstNode;
	struct employee *newNode;

	FILE *ptr_myFile;
	
	//opening my file for reading
	fopen_s(&ptr_myFile,"employees.txt","r+");

	//make sure it opened right
	if (ptr_myFile == NULL)
	{
		printf("Unable to open file!");
	}
	//create the first node in the list, getEmp returns a pointer to an
	//employee pulled from my file
	firstNode = getEmp(ptr_myFile);
	//ensure my .next is NULL, to avoid any pad ptr nonsense
	firstNode->next = NULL;
	//make this node my head node
	head = firstNode;

	//fill out the rest of the list from the file, so long as the file pointer hasnt reached the end
	while (!feof(ptr_myFile)) 
	{
		//newNode will be reused for each employee pulled from the file
		newNode = getEmp(ptr_myFile);
		//push it to the head of the list
		newNode->next = head;
		head = newNode;
	}

	//done. close the file
	fclose(ptr_myFile);

	//and return the pointer to the head node
	return head;
}
void addEmployee(struct employee **head)
{
	char tempS[40+1] ={""};
	int tempD = 0, tempM = 0, tempY = 0, validFlag;
	struct employee *newNode;

	newNode = (struct employee*)malloc(sizeof(struct employee));

	do
	{
		printf("ID:");
		fflush(stdin);
		scanf_s("%d", &newNode->id);//check for dupes
		if (validFlag = validateEmpID(newNode->id, *head) == 1)
			printf("Employee with that ID already exists!\n");
		system("pause");
		system("cls");
	}while(validFlag == 1);
		
	printf("Name: ");
	fflush(stdin);
	gets_s(newNode->name, 40);

	printf("Address ");

	printf("Street: ");
	fflush(stdin);
	gets_s(newNode->addr.street, 40);

	printf("City: ");
	fflush(stdin);
	gets_s(newNode->addr.city, 40);


	printf("State/Province/County: ");
	fflush(stdin);
	gets_s(newNode->addr.prov, 40);

	printf("Department: ");
	fflush(stdin);
	gets_s(newNode->dept, 40);

	printf("Salary:");
	fflush(stdin);
	scanf_s("%d", &newNode->salary);

	
	printf("Email:");
	fflush(stdin);
	gets_s(newNode->email, 40);
	

	newNode->next = NULL;

	do{
		printf("Hire Date (DD MM YYYY): ");
		scanf_s("%d %d %d",&tempD, &tempM, &tempY );
	}while((tempD < 1 || tempD > 31) ||	(tempM < 1 || tempM > 12) || (tempY < 1900 || tempY > 2015));

	newNode->hireDate.day = tempD;
	newNode->hireDate.month = tempM;
	newNode->hireDate.year = tempY;

	if((*head)->id != 0)
	{
		newNode->next = *head;
		*head = newNode;
	}
	else
		*head = newNode;
}
void displayNodes(struct employee *head)
{
	struct employee *temp;
	int i = 1;

	temp = (struct employee*)malloc(sizeof(struct employee));
	temp = head;

	
	while(temp != NULL)
	{
		printf("Employee  #%d: \n", temp->id);
		printf("\t Name: %s\n", temp->name);
		printf("\t dept: %s\n", temp->dept);
		printf("\t hireDate: %d-%d-%d\n", temp->hireDate.day, temp->hireDate.month, temp->hireDate.year);
		printf("\t salary: %d\n", temp->salary);
		printf("\t email: %s\n\n", temp->email);
		temp = temp->next;
	}
	system("pause");
}
struct employee *getEmp(FILE *ptr_myFile)
{

	char tempS[40+1];
	struct employee *emp;

	emp = (struct employee*)malloc(sizeof(struct employee));

	fgets(tempS, 40, ptr_myFile);
	emp->id = atoi(tempS);

	fgets(tempS, 40, ptr_myFile);
	strcpy_s(emp->name, 40, tempS);

	fgets(tempS, 40, ptr_myFile);
	strcpy_s(emp->addr.street, 40, tempS);

	fgets(tempS, 40, ptr_myFile);
	strcpy_s(emp->addr.city, 40, tempS);

	fgets(tempS, 40, ptr_myFile);
	strcpy_s(emp->addr.prov, 40, tempS);

	fgets(tempS, 40, ptr_myFile);
	strcpy_s(emp->dept, 40, tempS);

	fgets(tempS, 40, ptr_myFile);
	emp->salary = atof(tempS);

	fgets(tempS, 40, ptr_myFile);
	strcpy_s(emp->email, 40, tempS);

	fgets(tempS, 40, ptr_myFile);
	emp->hireDate.day = atoi(tempS);
	fgets(tempS, 40, ptr_myFile);
	emp->hireDate.month = atoi(tempS);
	fgets(tempS, 40, ptr_myFile);
	emp->hireDate.year = atoi(tempS);
	return emp;
}
int validateEmpID(int id, struct employee *head)
{
	struct employee *temp;
	temp = head;

	while(temp != NULL)
	{
		if (id == temp->id)
		{
			return 1;
		}
		else	
			temp = temp->next;
	}
	return 0;
}
void findEmpID(struct employee *head, int id)
{
	struct employee *temp;
	FILE *ptr_myFile;

	temp = head;

	//opening my file for reading
	fopen_s(&ptr_myFile,"employees.txt","r+");
	
	while(temp != NULL)
	{
		if (id == temp->id)
		{
			printf("Employee FOUND! \n");
			printf("Employee  #%d: \n", temp->id);
			printf("\t Name: %s\n", temp->name);
			printf("\t dept: %s\n", temp->dept);
			printf("\t hireDate: %d-%d-%d\n", temp->hireDate.day, temp->hireDate.month, temp->hireDate.year);
			printf("\t salary: %d\n", temp->salary);
			printf("\t email: %s\n\n", temp->email);
			return;
		}
		else	
		temp = temp->next;
	}

	printf("Employee NOT FOUND!\n");
	system("pause");
	system("cls");
}
void findEmpName(struct employee *head, char *n)
{

	struct employee *temp;
	char *name;	
	FILE *ptr_myFile;


	temp = head;

	//opening my file for reading
	fopen_s(&ptr_myFile,"employees.txt","r+");
	
	while(temp != NULL)
	{
		if (strcmp(name, temp->name)  == 0)
		{
			printf("Employee FOUND! \n");
			printf("Employee  #%d: \n", temp->id);
			printf("\t Name: %s\n", temp->name);
			printf("\t dept: %s\n", temp->dept);
			printf("\t hireDate: %d-%d-%d\n", temp->hireDate.day, temp->hireDate.month, temp->hireDate.year);
			printf("\t salary: %d\n", temp->salary);
			printf("\t email: %s\n\n", temp->email);
			return;
		}
		else	
		temp = temp->next;
	}

	printf("Employee NOT FOUND!\n");
	system("pause");
	system("cls");
}