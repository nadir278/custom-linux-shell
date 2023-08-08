#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include <fcntl.h>
#define MAX_LEN 100

void makeschedualhelper (char*);

int main(int argc, char* argv[])
{
    int lectxt, i, rbytes, pid;
    char inuser[MAX_LEN], inpass[MAX_LEN], c, *username, *pass, *id, buff[256];

    if (argc != 2) { perror("Incorrect amount of arguments"); exit(1); }        

    strcpy(inuser,argv[0]);
    strcpy(inpass,argv[1]);

     //open students list
    if ((lectxt = open("/home/braude/lec_pass.txt",O_RDONLY)) == -1)
		{ perror("ERROR open lec_pass"); exit(1);}

    //read from the file
    i=0;
    while ((rbytes = read(lectxt, &c, 1)) > 0)
    {
        buff[i++] = c;
        
        //if we read one full line
        if (c == '\n' || i == 256)
        {
            buff[i] = '\0';
            i = 0;
            username = strtok(buff," ");    //get username from read line
            pass = strtok(NULL, " ");       //get pass from read line
            id = strtok(NULL, " ");
            //check if username is correct
            if((strcmp(username, inuser) == 0))
                {
                    //check if password is correct
                    if((strcmp(pass, inpass) == 0))
                    {
                        close(lectxt);
                        pid = fork();
                        //replace child process code with Lec_Shell code
                        if (pid == 0)
                        {
                            execl("/home/braude/Lec_Shell", NULL);
                            perror("ERROR execl LecShell");
                            exit(1);
                        }
                        wait();
                        return 0;
                    }
                    else {printf("Incorrect Password!\n"); exit(1);} //passord is incorrect

                }
        }
    }
    printf("Lecturer not found!\n");

    return 0;
}