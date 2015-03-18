#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int getPass(char pw[]);//masks characters for password input and returns
void doLogin();//does the login...
void builder();//builds default user logins
struct login * loginReader( struct login **head);//loads the login information from users.dat
char * searchLoginList(struct login *head, char *s);
void displayMenu();
void addEmployee();
struct employee *loadEmployees();
void displayNodes();
int validateEmpID(int id, struct employee *head);
struct employee *getEmp(FILE *ptr_myFile);
void findEmpID(struct employee *head, int id);
void findEmpName(struct employee *head, char const *n);