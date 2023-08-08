#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include <fcntl.h>
#define MAX_LEN 100


int main(int argc, char* argv[])
{
    if(argc!= 1){perror("Not enough parameters!"); exit(1);}
    int i,rbytes, wbytes, flag = 0, acctxt;
    char c, buff[256], *id, dir[256]="/home/braude/student/", inid[MAX_LEN], dirdir[256], *failures, *str = "3";
    if ((acctxt = open("/home/braude/acc.txt",O_RDWR)) == -1)
		{ perror("ERROR open acc.txt"); exit(1);}

    strcpy(inid, argv[0]);
     //read from the file
    i=0;
    while ((rbytes = read(acctxt, &c, 1)) > 0)
    {
        buff[i++] = c;
        
        //if we read one full line
        if (c == '\n' || i == 256)
        {
            buff[i] = '\0';
            i = 0;
            id = strtok(buff, " ");
            id = strtok(NULL, " "); //get ID from read line
            if((strcmp(id, inid) == 0))
                {
                    lseek(acctxt, -2 , SEEK_CUR);
                    write(acctxt, str, strlen(str));
                    if (wbytes == -1) { perror("failed write to acctxt"); exit(1); }
                    strcpy(dir,strcat(dir,id));
                    chmod(dir, 0111);
                    printf("%s Froze successfully\n",id);
                    close(acctxt);
                    exit(1);
                }
        }
    }
    close(acctxt);
    printf("Student not found!\n");
}