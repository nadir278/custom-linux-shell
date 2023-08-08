#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include <fcntl.h>
#define MAX_LEN 100

int main(int argc, char* argv[])
{
    int pid ,stam;
    char command[MAX_LEN];
	if (argc != 1) { perror("Incorrect amount of arguments"); exit(1); }        

    printf("StdShell> ");
    scanf("%s", command);
    while(strcmp(command,"LogOut") != 0 )
    {
        //check if ShowCourses was typed
        if (strcmp(command, "ShowCourses") == 0)
        {
            pid = fork();
            //replace child process code with ShowCourses code
            if (pid == 0)
            {
                execl("/home/braude/ShowCourses", NULL);
                perror("ERROR execl ShowCourse");
                exit(1);
            }
            wait();
        }

        //check if GetNewCourse was typed
        else if (strcmp(command, "GetNewCourse") == 0)
        {
            pid = fork();
            //replace child process code with GetNewCourse code
            if (pid == 0)
            {
                execl("/home/braude/GetNewCourse", NULL);
                perror("ERROR execl GetNewCourse");
                exit(1);
            }
            wait();
        }

        //check if MakeSchedule was typed
        else if (strcmp(command, "MakeSchedule") == 0)
        {
            pid = fork();
            //replace child process code with MakeSchedule code
            if (pid == 0)
            {
                execl("/home/braude/MakeSchedule", NULL);
                perror("ERROR execl MakeSchedule");
                exit(1);
            }
            wait();
        }

        //check if GetSchedule was typed
        else if (strcmp(command, "GetSchedule") == 0)
        {
            pid = fork();
            //replace child process code with GetSchedule code
            if (pid == 0)
            {
                execl("/home/braude/GetSchedule", NULL);
                perror("ERROR execl GetSchedule");
                exit(1);
            }
            wait();
        }
        else if(strcmp(command, "LogOut") != 0) {
            printf("Not supported\n");
        }

        
        printf("StdShell> ");
        scanf("%s", command);

    }
    //check if LogOut was typed
    pid = fork();
    //replace child process code with LogOut code
    if (pid == 0)
    {
        execl("/home/braude/LogOut", NULL);
        perror("ERROR execl LogOut");
        exit(1);
    }
    wait();

    return 0;
}