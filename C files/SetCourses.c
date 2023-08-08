#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include <fcntl.h>
#define MAX_LEN 100

int main(int argc, char* argv[])
{
    int courses, wbytes;
    char courseid[MAX_LEN], coursename[MAX_LEN], dayinweek[MAX_LEN], timestart[MAX_LEN], timeover[MAX_LEN], newline[MAX_LEN], header[MAX_LEN];


    if(argc!=5){perror("SetCourses: missing parameters!");} //if parameters passed different than 5

    strcpy(courseid,argv[0]);
    strcpy(coursename,argv[1]);
    strcpy(dayinweek,argv[2]);
    strcpy(timestart,argv[3]);
    strcpy(timeover,argv[4]); //Get arguments into variables

    strcpy(newline, strcat(newline, courseid));
    strcpy(newline, strcat(newline, " "));
    strcpy(newline, strcat(newline, coursename));
    strcpy(newline, strcat(newline, " "));
    strcpy(newline, strcat(newline, dayinweek));
    strcpy(newline, strcat(newline, " "));
    strcpy(newline, strcat(newline, timestart));
    strcpy(newline, strcat(newline, " "));
    strcpy(newline, strcat(newline, timeover));
    strcpy(newline, strcat(newline, "\n"));    //Creating the line peice by peice

    strcpy(header, "Id Name day start end\n"); //Header creating string


    if ((courses = open("/home/braude/Courses/Courses.txt",O_RDONLY, 0664)) == -1) //Checking if file exists, if nott open new file and write header.
		{ 
        if ((courses = open("/home/braude/Courses/Courses.txt",O_WRONLY | O_CREAT, 0664)) == -1)
		      {perror("ERROR open courses"); exit(1);}//Open Courses.txt file
        wbytes = write(courses, header, strlen(header));
        if (wbytes == -1) { perror("failed write to courses"); exit(1);}
        close(courses);
    } 

    if ((courses = open("/home/braude/Courses/Courses.txt",O_WRONLY, 0664)) == -1) 
		{ perror("ERROR open courses"); exit(1);}    //Open Courses.txt file

    lseek(courses, 0, SEEK_END); 

    wbytes = write(courses, newline, strlen(newline));
    if (wbytes == -1) { perror("failed write to courses"); exit(1);} //writes new courses to the file
    printf("successfully created course\n");
    close(courses);
    return 0;

}
