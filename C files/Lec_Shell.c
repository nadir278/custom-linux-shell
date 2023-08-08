#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include <fcntl.h>
#define MAX_LEN 100

void makeschedualhelper (char*);

int main()
{
    int pid ,stam, rbytes;
    char *command, *courseid, *coursename, *dayinweek, *timestart, *timeover, *id, buff[256];      
    memset(buff, 0, sizeof(buff));
    printf("LecShell> ");
    fflush(stdout);
    rbytes = read(STDIN_FILENO, buff, 256);
    if(rbytes == -1){
        perror("ERROR: failed to read from console");
        exit(1);
    }
    buff[strlen(buff)-1] = '\0';
    command = strtok(buff," ");
    while(strcmp(command,"LogOut") != 0 )
    {
        //check if SetCourses was typed
        if ((strcmp(command, "SetCourses\n") == 0) || (strcmp(command, "SetCourses") == 0))
        {
            courseid = strtok(NULL, " ");
            coursename = strtok(NULL, " ");
            dayinweek = strtok(NULL, " ");
            timestart = strtok(NULL, " ");
            timeover = strtok(NULL, " ");
            if(courseid== NULL || coursename == NULL || dayinweek == NULL || timestart == NULL || timeover == NULL  ){
                
                printf("SetCourses: missing parameters \nLecShell> ");
                fflush(stdout);
                memset(buff, 0, sizeof(buff));
                rbytes = read(STDIN_FILENO, buff, 256);
                if(rbytes == -1){
                    perror("ERROR: failed to read from console");
                    exit(1);
            }
            buff[strlen(buff)-1] = '\0';
            command = strtok(buff," ");
            continue;
            }
            pid = fork();
            //replace child process code with ShowCourses code
            if (pid == 0)
            {
                execl("/home/braude/SetCourses", courseid, coursename, dayinweek, timestart, timeover, NULL );
                perror("ERROR execl SetCourses");
                exit(1);
            }
            wait();
        }


        //check if GetSchedule was typed
        else if (strcmp(command, "GetSchedule") == 0)
        {
            id = strtok(NULL, " ");
            pid = fork();
            //replace child process code with GetSchedule code
            if (pid == 0)
            {
                execl("/home/braude/GetSchedule", id, NULL);
                perror("ERROR execl GetSchedule");
                exit(1);
            }
            wait();
        }

        //check if DeleteStudent was typed
       else if (strcmp(command, "DeleteStudent") == 0) 
        {
            id = strtok(NULL, " ");
            pid = fork();
            //replace child process code with DeleteStudent code
            if (pid == 0)
            {
                execl("/home/braude/DeleteStudent", id, NULL);
                perror("ERROR execl DeleteStudent");
                exit(1);
            }
            wait();
        }

                //check if Freeze was typed
       else if (strcmp(command, "Freeze") == 0) 
        {
            id = strtok(NULL, " ");;
            pid = fork();
            //replace child process code with Freeze code
            if (pid == 0)
            {
                execl("/home/braude/Freeze", id, NULL);
                perror("ERROR execl Freeze");
                exit(1);
            }
            wait();
        }
                        //check if Approve was typed
        else if (strcmp(command, "Approve") == 0) 
        {
            id = strtok(NULL, " ");
            pid = fork();
            //replace child process code with Approve code
            if (pid == 0)
            {
                execl("/home/braude/Approve", id, NULL);
                perror("ERROR execl Approve");
                exit(1);
            }
            wait();
        }
                     //check if ShowCourses was typed
        else if (strcmp(command, "ShowCourses") == 0) 
        {

            pid = fork();
            //replace child process code with Approve code
            if (pid == 0)
            {
                execl("/home/braude/ShowCourses", NULL);
                perror("ERROR execl ShowCourses");
                exit(1);
            }
            wait();
        }
        else if (strcmp(command,"LogOut") == 0){
            //check if LogOut was typed
            pid = fork();
            //replace child process code with LogOut code
            if (pid == 0)
            {
                execl("/home/braude/LogOut", NULL);
                perror("ERROR execl LogOut");
                exit(1);
            }
        }
        else{
            printf("Not supported\n");
        }
        memset(buff, 0, sizeof(buff));
        printf("LecShell> ");
        fflush(stdout);
        rbytes = read(STDIN_FILENO, buff, 256);
        if(rbytes == -1){
            perror("ERROR: failed to read from console");
            exit(1);
        }
        buff[strlen(buff)-1] = '\0';
        command = strtok(buff," ");
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
