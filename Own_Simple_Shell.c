#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "signal.h"
#include "unistd.h"

int main(int count, char* argv[])
{	
	int temp;  
	char value[255];  
	signal(SIGINT, SIG_IGN);

	while(1)
	{
		int child, i = 0, j=0;
		char* strInput = value;
		char* strData = value;
		char** stackData = malloc(256);
		printf("$ ");
		fgets(strInput, 255, stdin);
		temp = strlen(strInput)-1;
		strInput[temp] = '\0';
		if (strcmp( strInput, "exit") == 0){
			exit(0);
		}

		stackData[j] = strtok(strData," ");

		while(stackData[j])
		{
		     	j++;
			stackData[j] = strtok(NULL, " ");
		}
		child = fork();
		if (child == -1)
		{
			perror("fork does not work\n");
			exit(0);
		}
		if (child == 0)
		{
			execvp(stackData[0], stackData);
			perror("Error\n");
			exit(0);
		}
		else
		{
			wait(&child);        
			free(stackData);
		}

	}
	return 0;
}
