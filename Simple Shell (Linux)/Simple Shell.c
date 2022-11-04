#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <signal.h>

/*Function produces a signal every time a child teriminates*/
void sighandle(int signo)

{	/*Creating a Log file*/
	FILE *f;
	f = fopen ("6071.txt","a");
	if(signo == SIGCHLD)
	{
	fprintf(f,"Child was terminated\n");
	fclose(f);
	}
}

/*Function that counts the number of words in the command line entered by the user*/
unsigned countWords(char *str)
{
    int state = 0;
    int wc = 0;

    while (*str)
    {
        if (*str == ' ')
            state = 0;

        else if (state == 0)
        {
            state = 1;
            ++wc;
        }
        ++str;
    }
    return wc;
}

/*Main Function*/
int main()
{
	printf("\nWelcome\n\n");
	/*Creating a Log file*/
	FILE *f;
	f = fopen ("6071.txt","w");

	signal(SIGCHLD,sighandle);

    while(1)
    {
    	/*Aquiring the Command Line from the user*/
    	printf("Please Enter your Command: ");
        char sent[100];
        scanf("%[^\n]%*c", sent);

        /*Exiting the Program*/
        if (strcmp(sent, "exit") == 0)
        	exit(0);

	/*If the command is of one word*/
        if (countWords(sent) == 1)
        {
            pid_t pid = fork();

            if (pid < 0)
            {
                printf("Fork failed unable to creat a child process.\n");
            }

            else if (pid == 0)  /* Child Process */
            {
                char *args[] = {sent, NULL};
                execvp(args[0], args);
            }

            else   /* Parent Process */
            {

                int status;
                waitpid(pid, &status, WUNTRACED|WCONTINUED);

            }
        }

        /*If the command is of two words*/
        if (countWords(sent) == 2)
        {
            pid_t pid = fork();

            char* token1 = strtok(sent, " ");
            char* token2 = strtok(NULL, " ");

            if (pid < 0)
            {
                printf("Fork failed unable to creat a child process.\n");
            }

            else if (pid == 0)  /* Child Process */
            {
                char *args[] = {token1,token2, NULL};

                /*Check if the second word was the character '&'*/
                if (strcmp(token2,"&") == 0)
                {
                strcpy(args[0],token1);
                args[1] = NULL;
                }
                execvp(args[0], args);
            }

            else   /* Parent Process */
            {
                int status;
                if(strcmp(token2,"&") != 0)
                waitpid(pid, &status, WUNTRACED|WCONTINUED);
            }
        }
    }
    fclose(f);
    return 0;
}
