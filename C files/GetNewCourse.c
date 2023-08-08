#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include <fcntl.h>
#define MAX_LEN 100

int main()
{
    //printf("BENNNNNNNNNNNNNN");
    int rbytes, course, i;
    char buff[256],c;

    //open courses.txt
    if ((course = open("/home/braude/Courses/Courses.txt",O_RDONLY, 0664)) == -1)
		{ perror("ERROR open courses"); exit(1);}

    i = 0;
    //read from Courses list file
    while ((rbytes = read(course, &c, 1)) > 0) 
    {
        buff[i++] = c;
        //get to the last line
        if (c == '\n' || i == 256 )
        {
            buff[i] = '\0';
            i = 0;
        }
    }
    //print only the last line
    printf("%s", buff);

    return 0;
}