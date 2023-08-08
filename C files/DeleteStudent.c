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
    int stdtxt, i,rbytes, wbytes, flag = 0;
    char c, buff[256], *id, dir[256]="/home/braude/student/", inid[MAX_LEN], dirdir[256], buffer[256];
    if ((stdtxt = open("/home/braude/std_pass.txt",O_RDONLY)) == -1)
		{ perror("ERROR open std_pass"); exit(1);}
    strcpy(inid, argv[0]);
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
            strcpy(buffer, buff);
            id = strtok(buff, " ");
            id = strtok(NULL, " ");
            id = strtok(NULL, " "); //get ID from read line
            if((strcmp(id, inid) == 0))
                {
                    strcpy(dir,strcat(dir,id));
                    strcpy(dirdir,dir);
                    strcpy(dir,strcat(dir,"/Schedule.txt"));
                    remove(dir); //Remove schedule file
                    rmdir(dirdir); //Remove student dir
                    printf("Removed succesfully\n");
                    flag = 1;
                    continue;
                }
        }
    }
    close(stdtxt);
    return 0;
}
