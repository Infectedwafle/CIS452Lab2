#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdint.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/resource.h>

#define MAXLINE 80
#define MAXARG 20

void background (char * cmd);

int main(){
	int status;
	while (1)
	{
		char cmd[MAXLINE];
		printf("mysh$ ");
		fgets(cmd, MAXLINE, stdin); 	// read a command from the user
		 
		printf("%s\n", cmd);
		//if the command in cmd is “exit\n”, then terminate this program;
		if (strncmp(cmd, "exit\n", MAXLINE)==0){
			printf("Exiting");
			exit(0);
		}
		//otherwise, create a child process to handle that command.
		else
		{
			struct rusage usage;		
			int who = fork();

			if (who == 0){
				fflush (stdout);
				background(cmd);
			};
			
			printf("Waiting\n");
			wait(&status);
			printf("Done\n");
			getrusage(RUSAGE_CHILDREN, &usage);
			
			printf("Involuntary Context Switches: %ld\nCPU Time (microseconds): %ld\nUser Time (microseconds): %ld\n\n", usage.ru_nivcsw, usage.ru_stime.tv_usec, usage.ru_utime.tv_usec);	
			printf("CPU Time (seconds): %ld\nUser Time (seconds): %ld\n\n", usage.ru_stime.tv_sec, usage.ru_utime.tv_sec);	

		}
	}
}

void background (char * cmd)
{

	int i = 0;
	char *argv[MAXARG];

	// Here you may use strtok(cmd, "\t \n") to get each token 
	// from cmd and then storeit in array argv sequentially.
	// strtok() returns NULL when the end of cmd is reached.

	char *temp = strtok(cmd,"\t \n");
	while (temp != NULL){
		//printf("%s",temp);
		argv[i] = temp;
		i++;
		temp = strtok(NULL,"\t \n");
	}	
	putchar ('\n');
	execvp (argv[0], argv);
	exit(0);
		
}
