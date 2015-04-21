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
	struct employee *curNode;
	size_t cur_len;

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

	printf("Salary: ");
	fflush(stdin);
	scanf_s("%lf", &newNode->salary, 40);

	
	do
	{
		validFlag = 0;
		printf("Email Address: ");
		fflush(stdin);
		gets_s(newNode->email, 40);//check for dupes
		cur_len = strlen(newNode->email);
		newNode->email[ cur_len +1 ] = '\0';
		validFlag = verifyEmail(newNode->email);
		if (validFlag == 0)
			printf("Please enter a valid email address!\n");
		system("pause");
		system("cls");
	}while(validFlag == 0);
	
	newNode->next = NULL;

	do{
		printf("Hire Date (DD MM YYYY): ");
		scanf_s("%d %d %d",&tempD, &tempM, &tempY );
	}while((tempD < 1 || tempD > 31) ||	(tempM < 1 || tempM > 12) || (tempY < 1900 || tempY > 2015));

	newNode->hireDate.tm_year = tempY-1900;
	newNode->hireDate.tm_mday = tempD;
	newNode->hireDate.tm_mon = tempM;
	
	curNode = *head;

	while(curNode != NULL)//ensure the end of the list isn't accessed
	{
		if(newNode->id < curNode->id)//if the node is the lowest on the list
		{
			newNode->next = curNode;
			*head = newNode;
			break;
		}
		
		if(newNode->id > curNode->id)//if the id for the new node is greater than the current node
		{
			if(curNode->next != NULL)//we check if the next node is NULL
			{
				if(newNode->id < curNode->next->id)// then compare id's with the next one
				{
					newNode->next = curNode->next;//if it is, we insert it here
					curNode->next = newNode;
					break;
				}
				else// if the newNode's id is greater than the next as well, we move further down the list.
				{
					curNode = curNode->next;
				}
			}
			else//if it's the last one in the list, just put it on the end and null the next.
			{
				curNode->next = newNode;
				newNode->next = NULL;
				break;
			}
		}
	
	}

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
struct employee * findEmpID(struct employee *head, int id)
{
	struct employee *temp;

	temp = head;

	//opening my file for reading
	//fopen_s(&ptr_myFile,"employees.txt","r+");
	
	while(temp != NULL)
	{
		if (id == temp->id)
		{
			printf("Employee FOUND! \n");
			printEmployee(temp);
			return temp;
		}
		else	
		temp = temp->next;
	}

	printf("Employee NOT FOUND!\n");
	system("pause");
	system("cls");
	return NULL;
}
struct employee * findEmpName(struct employee *head, char *name)
{
	struct employee *temp;

	temp = head;
	
	while(temp != NULL)
	{
		if (strcmp(name, temp->name)  == 0)
		{
			printf("Employee FOUND! \n");
			printEmployee(temp);
			system("pause");
			return temp;
		}
		else	
			temp = temp->next;
	}

	printf("Employee NOT FOUND!\n");
	system("pause");
	system("cls");
	return NULL;
}
void printEmployee(struct employee *emp)
{

	printf("Employee  #%d: \n", emp->id);
	printf("\t Name: %s\n", emp->name);
	printf("\t Dept: %s\n", emp->dept);
	printf("\t HireDate: %d-%d-%d\n", emp->hireDate.tm_mday, emp->hireDate.tm_mon, emp->hireDate.tm_year + 1900);
	printf("\t Salary: %.2f\n", emp->salary);
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
int verifyEmail(char *s)
{
	int i = 0, flag = 0;
	while(s[i++] != '\0')
	{
		if(s[i] == '@')
		{
			flag++;
			break;
		}
	}
	if(strstr(s,".com\0"))
		flag++;
	if(strstr(s,"@.com\0"))
		flag--;
	if(flag == 2)
		return 1;
	else
		return 0;
}
int getEmpID()
{
	int id;
	printf("Enter the Employee ID to searched for: ");
	fflush(stdin);
	scanf_s("%d", &id);
	return id;
}
void deleteEmp(struct employee **head, int id)
{
	struct employee *prevEmp;
	struct employee *curEmp;

	prevEmp = *head;
	curEmp = *head;

	while(curEmp != NULL)
	{
		if(curEmp->id == id)
		{
			//To determine if the node found is the first in the list, we check to see if the curEmp is still pointing at the head
			if(curEmp != *head)
			{
				printf("Employee #%d found! Deleting %s!\n\n", curEmp->id, curEmp->name);
				prevEmp->next = curEmp->next;
				free(curEmp);
				break;
			}
			else
			{
				printf("Employee #%d found! Deleting %s!\n\n", curEmp->id, curEmp->name);
				*head = curEmp->next;
				free(curEmp);
				break;
			}
		}
		prevEmp = curEmp;
		curEmp = curEmp->next;
	}

	system("pause");
	system("cls");
}
char * getEmpName()
{
	static char name[40+1];

	printf("Enter the name to search for: ");
	fflush(stdin);
	gets_s(name,40+1);

	return name;
}
void updateEmployee(struct employee *emp)
{
	int choice;
	do
	{
		system("cls");
		printf("Update Employee Details\n");
		printf("1)Address\n");
		printf("2)Department\n");
		printf("3)Salary\n");
		printf("4)Return to main menu\n");
		printf("Selection:");
		fflush(stdin);
		scanf_s("%d", &choice);
	}while(choice < 0 || choice > 8);

	switch(choice)
	{
		case 1:
			printf("Street: ");
			fflush(stdin);
			gets_s(emp->addr.street, 40);
			printf("City: ");
			fflush(stdin);
			gets_s(emp->addr.city, 40);
			printf("State/Province/County: ");
			fflush(stdin);
			gets_s(emp->addr.prov, 40);
			break;
		case 2:
			printf("Department: ");
			fflush(stdin);
			gets_s(emp->dept, 40);
			break;
		case 3:
			printf("Salary: ");
			fflush(stdin);
			scanf_s("%lf", &emp->salary, 40);
			break;
		case 4:
			break;

	}

	
}
void listEmployees(struct employee *head)
{
	//search list for new department names
	//build an array of those names
	//go through array and for each department go through the list
	//each time the departments match, print
	char **depts;
	int i, len = 1;
	struct employee * temp = head;

	system("cls");
	depts = malloc(1 * sizeof(char*));
	depts[0] = malloc((20+1) * sizeof(char));


	while(temp != NULL)
	{
		int reallocFlag = 1;

		for(i = 0;i<len;i++)
		{
			if(strcmp(depts[i], temp->dept) == 0)
				reallocFlag = 0;
		}

		if (reallocFlag == 1)
		{
			strcpy(depts[len-1], temp->dept);
			depts = (char **)realloc(depts, (++len) * sizeof(char*));
			depts[len-1] =(char *) malloc((20+1) * sizeof(char));
		}

		temp = temp->next;
	}
	
	
	printf("Department Rosters\n\n");

	for(i = 0;i<len-1;i++)
	{
		printf("%s\n", depts[i]);
		printf("----------------------------------------\n");
		temp = head;
		while(temp != NULL)
		{
			if(strcmp(depts[i], temp->dept)==0)
				printf("  %s\n",temp->name);

			temp=temp->next;
		}
		printf("\n");
	}
	system("pause");
}