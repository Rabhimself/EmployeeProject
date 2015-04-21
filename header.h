#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

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
int getEmpID();
struct employee * findEmpID(struct employee *head, int id);
struct employee *  findEmpName(struct employee *head, char *s);
void printEmployee(struct employee * emp);
void reporter(struct employee *head);
int verifyEmail(char * s);
char * getEmpName();
void deleteEmp(struct employee **head, int id);
void updateEmployee(struct employee *emp);
void listEmployees(struct employee *head);