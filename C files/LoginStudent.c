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
    int stdtxt, rbytes,rbytes1, i,j, acc, failed, wbytes, pid;
    char buff[256],buff1[256], *username, *pass, *id, c,d, inuser[MAX_LEN], inpass[MAX_LEN], *helper, failedc[16], *zero = "0";

	if (argc != 2) { perror("Incorrect amount of arguments"); exit(1); }        

    strcpy(inuser,argv[0]);
    strcpy(inpass,argv[1]);

    //open helper file
    if ((acc = open("/home/braude/acc.txt",O_RDWR)) == -1)
		{ perror("ERROR open acc"); exit(1);}

    //open students list
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
            username = strtok(buff," ");    //get username from read line
            pass = strtok(NULL, " ");       //get pass from read line
            id = strtok(NULL, " ");
            //check if username is correct
            if((strcmp(username, inuser) == 0))
                {
                    //check if password is incorrect
                    if((strcmp(pass, inpass) != 0))
                    {
                        j=0;
                        while ((rbytes1 = read(acc, &d, 1)) > 0)
                        {
                            buff1[j++] = d;
                            //if we read one full line
                            if (d == '\n' || j == 256)
                            {
                                buff1[j] = '\0';
                                j = 0;
                                helper = strtok(buff1," ");
                                //check if we are in the correct user line
                                if(strcmp(helper, username) == 0)
                                {
                                    helper = strtok(NULL, " ");
                                    helper = strtok(NULL, " ");     //helper = failed attempts
                                    failed = atoi(helper);
                                    failed++;
                                    lseek(acc,-2,SEEK_CUR);     
                                    sprintf(failedc,"%d",failed);
                                    wbytes = write(acc, failedc , 1);
                                    if (wbytes == -1) { perror("failed write to acc"); exit(1); }
                                    if (failed >= 3)
                                    {
                                        printf("%s account Blocked!\n",username);
                                        return 0;
                                    }  
                                    printf("Incorrect Password\n");
                                    exit(1);     
                                }
                            }
                        
                        }
                    }
                    //else password is correct
                    else
                    {
                        j=0;
                        while ((rbytes1 = read(acc, &d, 1)) > 0)
                        {
                            buff1[j++] = d;
                            //if we read one full line
                            if (d == '\n' || j == 256)
                            {
                                buff1[j] = '\0';
                                j = 0;
                                helper = strtok(buff1," ");
                                //check if we are in the correct user line
                                if(strcmp(helper, username) == 0)
                                {
                                    helper = strtok(NULL, " ");
                                    helper = strtok(NULL, " ");     //helper = failed attempts
                                    failed = atoi(helper);
                                    failed++;
                                    lseek(acc,-2,SEEK_CUR);     
                                    sprintf(failedc,"%d",failed);
                                    if (failed < 3){
                                        wbytes = write(acc, zero , 1);
                                        if (wbytes == -1) { perror("failed write to acc"); exit(1); }
                                    }
                                }
                            }
                        }
                        close(stdtxt);
                        makeschedualhelper(id);

                        pid = fork();
                        //replace child process code with Std_Shell code
                        if (pid == 0)
                        {
                            execl("/home/braude/Std_Shell", id, NULL);
                            perror("ERROR execl LoginStudent");
                            exit(1);
                        }
                        wait();
                        return 0;
                    }
                }
        }

    }
    close(acc);
    printf("Student Not Found!\n");

    return 0;
}


void makeschedualhelper (char* id)
{
    int rbytes, wbytes, help;
    char dir[MAX_LEN], helpern[]="\n";

    //create helper file
    if ((help = open("/home/braude/schedulehelp.txt",O_WRONLY | O_CREAT, 0664)) == -1)
		{ perror("ERROR open acc"); exit(1);}

    wbytes = write(help, id, strlen(id));
    if (wbytes == -1) { perror("failed write to schedulehelp"); exit(1); }

    wbytes = write(help, helpern, strlen(helpern));
    if (wbytes == -1) { perror("failed write to schedulehelp"); exit(1); }

    close(help);
}
