#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int getPass(char pw[]);//masks characters for password input and returns
int doLogin();//does the login...
int builder();//builds default user records
struct rec * reader();

struct rec
	{
		char name[7];
		char pass[7];
	}

main()
{

	
	
}

//getPass uses getch() from the conio.h library, which gets a character without echoing
//if return was not pressed, it will instead echo an asterisk.
//function returns a 0 if the password passed in matches the password entered
int getPass(char pw[])
{
	char c;
	char pass[7];
	int i = 0;

	do 
	{
	  c = getch();
	  
	  if(c != '\n') 
	  {
		putchar('*');
		pass[i++] = c;
	  }
	} while(i < 6 );
	pass[6] = '\0';
	return strcmp(pw,pass);
}
int doLogin()
{
   
   return(0);	
/*
	while(getPass(password) != 0)
	{
		printf("Incorrect password, try again.\n");
		system("pause");
		system("cls");
	}

	printf();
*/
}

struct rec * reader()
{
	FILE *ptr_myfile;
	struct rec my_record;

}
//just used to create new employee records//
int builder()
{	

	FILE *ptr_myfile;
	
	
	struct rec bill = {"bill","qwerty"};
	struct rec brad = {"brad","asdfgh"};
	struct rec barry = {"barry","zxcvbn"};

	ptr_myfile=fopen("users.bin","wb");
	if (!ptr_myfile)
	{
		printf("Unable to open file!");
		return 1;
	}

	fwrite(&bill, sizeof(struct rec), 1, ptr_myfile);
	fwrite(&brad, sizeof(struct rec), 1, ptr_myfile);
	fwrite(&barry, sizeof(struct rec), 1, ptr_myfile);

	fclose(ptr_myfile);
	return 0;
}