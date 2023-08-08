#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include <fcntl.h>
#define MAX_LEN 100

void create_dir_by_id();

int main(int argc, char* argv[])
{
    int result, pid;
    char command[MAX_LEN], inuser[MAX_LEN], inpass[MAX_LEN];

	if (argc != 1) { perror("Incorrect amount of arguments"); exit(1); }    
  
    //creating courses folder
    result = mkdir("Courses", 0777);
    if (result != 0) {
        printf("Failed to create courses directory\n");
        exit(1);
    }

    //creating student folder
    result = mkdir("student", 0777);
    if (result != 0) {
        printf("Failed to create student directory\n");
        exit(1);
    }
    //create directory to each student
    create_dir_by_id();

    printf("LockedShell> ");
    scanf("%s", command);
    while(strcmp(command,"exit") != 0 )
    {
        //check if LoginStudent was typed
        if (strcmp(command, "LoginStudent") == 0)
        {  
            scanf("%s %s", inuser, inpass);
            pid = fork();
            //replace child process code with LoginStudent code
            if (pid == 0)
            {
                
                execl("/home/braude/LoginStudent", inuser, inpass, NULL);
                perror("ERROR execl LoginStudent");
                exit(1);
            }
            wait();
        }
        //check if LoginLecturer was typed
        else if (strcmp(command, "LoginLecturer") == 0)
        {  
            scanf("%s %s", inuser, inpass);
            pid = fork();
            //replace child process code with LoginLecturer code
            if (pid == 0)
            {
                
                execl("/home/braude/LoginLecturer", inuser, inpass, NULL);
                perror("ERROR execl LoginLecturer");
                exit(1);
            }
            wait();
        }
        else if(strcmp(command, "exit") != 0) {
            printf("Not supported\n");
        }
        printf("LockedShell> ");
        scanf("%s", command);
        
    }

     //check if exit was typed
    pid = fork();
    //replace child process code with exit code
    if (pid == 0)
    {
        execl("/home/braude/exit", NULL);
        perror("ERROR execl exit");
        exit(1);
    }
    wait();

    return 0;
}

void create_dir_by_id()
{
    int stdtxt, acc, rbytes, i, result, wbytes;
    char buff[256], c, *id, dir[MAX_LEN], helperzero[] = " 0\n", *name, helperspace[] = " ";

    //create helper file
    if ((acc = open("/home/braude/acc.txt",O_WRONLY | O_CREAT, 0664)) == -1)
		{ perror("ERROR open acc"); exit(1);}

    //open students list
    if ((stdtxt = open("/home/braude/std_pass.txt",O_RDONLY)) == -1)
		{ perror("ERROR open std_pass"); exit(1);}

    //read from student list file
    i = 0;
    while ((rbytes = read(stdtxt, &c, 1)) > 0) 
    {
        buff[i++] = c;
        if (c == '\n' || i == 256 )
        {
            buff[i] = '\0';
            i = 0;
            strcpy(dir,"/home/braude/student/");
            //reach the id in the line
            name = strtok(buff," ");

            //add to helper file name of each student  and space
            if (strcmp(name, "Acount") != 0)
            {
                wbytes = write(acc, name, strlen(name));
                if (wbytes == -1) { perror("failed write to acc"); exit(1); }
                wbytes = write(acc, helperspace, strlen(helperspace));
                if (wbytes == -1) { perror("failed write to acc"); exit(1); }
            }
            id = strtok(NULL," ");
            id = strtok(NULL," ");// get id
            if (strcmp(id,"ID") == 0){continue;}

            //write to help file id and num of failed attempts of each student
            wbytes = write(acc, id, 9);
            if (wbytes == -1) { perror("failed write to acc"); exit(1); }
            wbytes = write(acc, helperzero, strlen(helperzero));
            if (wbytes == -1) { perror("failed write to acc"); exit(1); }

            // create directory to each student
            strcpy(dir,strcat(dir,id));
            result = mkdir(dir, 0777);
            if (result != 0)
            {
                printf("Failed to create directory\n");
                exit(1);
            }
        }        
    }
    close(stdtxt);
    close(acc);
}
