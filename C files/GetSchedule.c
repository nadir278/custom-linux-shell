#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include <fcntl.h>
#define MAX_LEN 100


void lecGetSchedule();





int main(int argc, char* argv[])
{
    int helper, rbytes, sche;
    char buff[256], id[MAX_LEN], dir[256]="/home/braude/student/";

    
    if (argc != 0){
        lecGetSchedule(argv[0]);
        exit(1);
    }
    //get id of logged in student
    //open helper file
    if ((helper = open("/home/braude/schedulehelp.txt",O_RDONLY)) == -1)
		{ perror("ERROR open std_pass"); exit(1);}

    //read form file
	if ((rbytes = read(helper, buff,256)) == -1)
		{perror("ERROR READING FROM schedulehelp");return(-1);}
        buff[9] = '\0';

    strcpy(id,buff);    //id=logged in student id
    close(helper);

    //open student schedule file
    strcpy(dir,strcat(dir,id));
    strcpy(dir,strcat(dir,"/Schedule.txt"));
    if ((sche = open(dir,O_RDONLY,0664)) == -1)
		{ printf("ERROR Schedule.txt does not exist\n");}
    else
    {
        //read form file
	    if ((rbytes = read(sche, buff,256)) == -1)
		    {perror("ERROR READING FROM schedulehelp");return(-1);}
    
        printf("%s",buff);
        close(sche);
    }
    
    
}


void lecGetSchedule(char* inid){

    int stdtxt, i,rbytes, sche;
    char c, buff[MAX_LEN], *id, dir[256]="/home/braude/student/";
    if ((stdtxt = open("/home/braude/std_pass.txt",O_RDONLY)) == -1)
		{ perror("ERROR open std_pass"); exit(1);}

    //read from the file
    i=0;
    while ((rbytes = read(stdtxt, &c, 1)) > 0)
    {
        buff[i++] = c;
        
        //if we read one full line
        if (c == '\n' || i == 256)
        {
            buff[i] = '\0';
            i = 0;
            id = strtok(buff, " ");
            id = strtok(NULL, " ");
            id = strtok(NULL, " "); //get ID from read line
            if((strcmp(id, inid) == 0))
                {
                    strcpy(dir,strcat(dir,id));
                    strcpy(dir,strcat(dir,"/Schedule.txt"));
                    if ((sche = open(dir,O_RDONLY,0664)) == -1)
		                { printf("Student not register!\n"); exit(1);}
                    else {
                            i = 0;
                            while ((rbytes = read(sche, &c, 1)) > 0) 
                            {
                                buff[i++] = c;
                                //print each line apart from the first;
                                if (c == '\n' || i == 256 )
                                {
                                    buff[i] = '\0';
                                    i = 0;
                                    printf("%s", buff);
                                }
                            }
                            exit(1); 
                    }
                }
        }
    }

    printf("Student not found\n");
}