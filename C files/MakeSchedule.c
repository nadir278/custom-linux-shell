#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include <fcntl.h>
#define MAX_LEN 100

int checkifblocked(char*);
void runoncourses (char*, char*);

int main()
{
    int helper, rbytes, sche, blocked=0, i, wbytes, coursecount=0;
    char id[MAX_LEN], buff[256], c, command[MAX_LEN], writecourse[MAX_LEN], dir[256]="/home/braude/student/";

    //open helper file
    if ((helper = open("/home/braude/schedulehelp.txt",O_RDONLY)) == -1)
		{ perror("ERROR open std_pass"); exit(1);}

    //read form file
	if ((rbytes = read(helper, buff,256)) == -1)
		{perror("ERROR READING FROM schedulehelp");return(-1);}
        buff[9] = '\0';

    strcpy(id,buff);    //id=logged in student id
    close(helper);

    //check if the student is blocked
    blocked = checkifblocked(id);
    if (blocked == 1)
    {
        printf("Blocked Acount ! permission denied\n");
        return 0;
    }
    


    //open student schedule file
    strcpy(dir,strcat(dir,id));
    strcpy(dir,strcat(dir,"/Schedule.txt"));
    if ((sche = open(dir,O_WRONLY|O_CREAT,0664)) == -1)
		{ perror("ERROR open Student schedule"); exit(1);}

    //get command from user
    do
    {
        scanf("%s",command);
        //run on cours list and show selected course
        if ((strcmp(command,"Exit") == 0))
            break;
        runoncourses(command, writecourse);
        if(strcmp(command,"Confirm") == 0)
        {
            coursecount++;
            lseek(sche,0,SEEK_END);
            wbytes = write(sche, writecourse, strlen(writecourse));
            if (wbytes == -1) { perror("failed write to schedulehelp"); exit(1); }
        }
    }while((strcmp(command,"Exit") != 0));

    //remove Schedule file if no course was confirmed
    if(coursecount == 0)
        if(remove(dir) != 0)
		    { perror("ERROR deleting Schedule"); exit(1);}
    
    return 0;
}



void runoncourses (char* courseid, char* writecourse)
{
    int i, rbytes, helper;
    char buff[256], cpybuff[256], c, *readcourseid;


    //open Courses list file
    if ((helper = open("/home/braude/Courses/Courses.txt",O_RDONLY)) == -1)
		{ perror("ERROR open std_pass"); exit(1);}

    //read from the file
    i=0;
    while ((rbytes = read(helper, &c, 1)) > 0)
    {
        buff[i++] = c;
        //if we read one full line
        if (c == '\n' || i == 256)
        {
            buff[i] = '\0';
            i = 0;
            strcpy(cpybuff,buff);
            readcourseid = strtok(cpybuff, " ");
            //show details of the requseted course
            if(strcmp(readcourseid, courseid) == 0)
            {
                printf("%s", buff);
                close(helper);
                strcpy(writecourse,buff);
            }

        }
    }
    close(helper);
}


int checkifblocked(char* id)
{
    int helper, i, rbytes, failed;
    char buff[256], c, *readid, *fail;

    //open faile counter file
    if ((helper = open("/home/braude/acc.txt",O_RDONLY)) == -1)
		{ perror("ERROR open acc"); exit(1);}
    

    //read from the file
    i=0;
    while ((rbytes = read(helper, &c, 1)) > 0)
    {
        buff[i++] = c;
        
        //if we read one full line
        if (c == '\n' || i == 256)
        {
            buff[i] = '\0';
            i = 0;
            readid = strtok(buff," ");    
            readid = strtok(NULL, " ");    //get id from file
            //check fail count for the student logged in
            if(strcmp(id,readid) == 0)
            {
                fail = strtok(NULL, " ");
                failed = atoi(fail);
                if (failed == 3)
                    return 1;
                else
                    return 0;
            }
        }
    }
}
