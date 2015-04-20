#include "header.h"

struct sNode
{
	struct sNode *next;
	char s[20+1];
	int eNum;
	double annumSal;
	double totBonus;
	double totOutlay;
};
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

	struct tm hireDate;

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

	newNode->hireDate.tm_year = tempY-1900;
	newNode->hireDate.tm_mday = tempD;
	newNode->hireDate.tm_mon = tempM;

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
		printf("\t hireDate: %d-%d-%d\n", temp->hireDate.tm_mday, temp->hireDate.tm_mon, temp->hireDate.tm_year);
		printf("\t salary: %.2f\n", temp->salary);
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
	strtok(tempS, "\n");
	strcpy_s(emp->name, 40, tempS);

	fgets(tempS, 40, ptr_myFile);
	strtok(tempS, "\n");
	strcpy_s(emp->addr.street, 40, tempS);

	fgets(tempS, 40, ptr_myFile);
	strtok(tempS, "\n");
	strcpy_s(emp->addr.city, 40, tempS);

	fgets(tempS, 40, ptr_myFile);
	strtok(tempS, "\n");
	strcpy_s(emp->addr.prov, 40, tempS);

	fgets(tempS, 40, ptr_myFile);
	strtok(tempS, "\n");
	strcpy_s(emp->dept, 40, tempS);

	fgets(tempS, 40, ptr_myFile);
	emp->salary = atof(tempS);

	fgets(tempS, 40, ptr_myFile);
	strtok(tempS, "\n");
	strcpy_s(emp->email, 40, tempS);

	fgets(tempS, 40, ptr_myFile);
	emp->hireDate.tm_mday = atoi(tempS);
	fgets(tempS, 40, ptr_myFile);
	emp->hireDate.tm_mon = atoi(tempS);
	fgets(tempS, 40, ptr_myFile);
	emp->hireDate.tm_year = atoi(tempS) - 1900;
	emp->hireDate.tm_min = 0;
	emp->hireDate.tm_sec = 0;
	emp->hireDate.tm_hour = 0;

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
void findEmpID(struct employee *head)
{
	struct employee *temp;
	int id;
	FILE *ptr_myFile;

	temp = head;

	printf("Enter the Employee ID to searched for: ");
	fflush(stdin);
	scanf_s("%d", &id);

	//opening my file for reading
	fopen_s(&ptr_myFile,"employees.txt","r+");
	
	while(temp != NULL)
	{
		if (id == temp->id)
		{
			printf("Employee FOUND! \n");
			printEmployee(temp);
			return;
		}
		else	
		temp = temp->next;
	}

	printf("Employee NOT FOUND!\n");
	system("pause");
	system("cls");
}
void findEmpName(struct employee *head)
{
	char name[40+1];
	struct employee *temp;
	FILE *ptr_myFile;

	printf("Enter the employee name to searched for: ");
	fflush(stdin);
	gets_s(name,40+1);

	temp = head;

	//opening my file for reading
	fopen_s(&ptr_myFile,"employees.txt","r+");
	
	while(temp != NULL)
	{
		if (strcmp(name, temp->name)  == 0)
		{
			printf("Employee FOUND! \n");
			printEmployee(temp);
			system("pause");
			return;
		}
		else	
			temp = temp->next;
	}

	printf("Employee NOT FOUND!\n");
	system("pause");
	system("cls");
}
void printEmployee(struct employee * emp)
{

	printf("Employee  #%d: \n", emp->id);
	printf("\t Name: %s\n", emp->name);
	printf("\t Dept: %s\n", emp->dept);
	printf("\t HireDate: %d-%d-%d\n", emp->hireDate.tm_mday, emp->hireDate.tm_mon, emp->hireDate.tm_year + 1900);
	printf("\t Salary: %d\n", emp->salary);
	printf("\t Email Address: %s\n", emp->email);
	printf("\t Address: \n");
	printf("\t\t%s\n", emp->addr.street);
	printf("\t\t%s\n", emp->addr.city);
	printf("\t\t%s\n", emp->addr.prov);
}
void reporter(struct employee *head)
{
	struct employee *temp;
	struct sNode *sTemp;
	struct sNode *sHead;
	int flag = 1;
	double diff;
	time_t now;

	time(&now);
	sTemp = (struct sNode*)malloc(sizeof(struct sNode));
	sTemp->next = NULL;
	temp = head;
	sHead = sTemp;


	//this is the first department created
	//since the list of departments is empty, we just create one from the get go
	strcpy(sTemp->s, temp->dept);
	sTemp->eNum = 1;
	sTemp->annumSal = temp->salary;
	sTemp->totOutlay = temp->salary;

	diff = difftime(now ,mktime(&temp->hireDate));
	diff = diff/31557600;

	if(diff > 10)
		sTemp->totBonus = temp->salary * .05;

	else if(diff > 5)
		sTemp->totBonus = temp->salary * .04;

	else
		sTemp->totBonus = temp->salary * .03;
	sTemp->totOutlay += sTemp->totBonus;

	temp = temp->next;


	//Build a linked list of nodes containing the different departments listed
	while(temp != NULL)
	{
		int foundFlag = 0;

		while(sTemp != NULL && foundFlag == 0)
		{
			if(strcmp(sTemp->s, temp->dept) == 0)
			{
				foundFlag = 1;
				sTemp->eNum++;
				sTemp->annumSal += temp->salary;
				sTemp->totOutlay += temp->salary;

				diff = difftime(now ,mktime(&temp->hireDate));
				diff = diff/31557600;

				if(diff > 10)
					sTemp->totBonus += temp->salary * .05;

				else if(diff > 5)
					sTemp->totBonus += temp->salary * .04;

				else
					sTemp->totBonus += temp->salary * .03;
				sTemp->totOutlay += sTemp->totBonus;
			}
			sTemp = sTemp->next;
		}

		sTemp = sHead;

		if(foundFlag == 0)
		{
			
			struct sNode *newDept;

			newDept = (struct sNode*)malloc(sizeof(struct sNode));

			strcpy(newDept->s, temp->dept);
			newDept->eNum = 1;
			newDept->annumSal = temp->salary;
			newDept->totOutlay = temp->salary;
			newDept->next = sTemp;

			diff = difftime(now ,mktime(&temp->hireDate));
			diff = diff/31557600;

			if(diff > 10)
				newDept->totBonus = temp->salary * .05;
			else if(diff > 5)
				newDept->totBonus = temp->salary * .04;
			else
				newDept->totBonus = temp->salary * .03;

			newDept->totOutlay += newDept->totBonus;

			sHead = newDept;
			foundFlag = 1;
		}

		sTemp = sHead;
		temp=temp->next;
	}

	
	while(sTemp != NULL)
	{
		struct sNode *freeNode;

		printf("Department: %s \n  ", sTemp->s);
		printf(" Number of Staff: %d \n", sTemp->eNum);
		printf(" Total Salary per annum: %.2f \n", sTemp->annumSal);
		printf(" Total Bonuses per annum: %.2f \n", sTemp->totBonus);
		printf("Total Financial Outlay%.2f \n\n", sTemp->totOutlay);

		freeNode = sTemp;
		sTemp = sTemp->next;
		free(freeNode);
	}


	system("pause");
	system("cls");
}