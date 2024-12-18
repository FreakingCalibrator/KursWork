#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string>
#include <regex.h>
#include <malloc.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#define STRING "/dev/"
#define PATTERN "^sd.$"
char** a;
void RegCat();
void CashCat();
char** arr=(char**)malloc(1*sizeof(char*));
char** arrpr=(char**)malloc(1*sizeof(char*));
pid_t pid=fork();
size_t size=-1;
size_t sizepr=-1;
int main()
{
    while (1){
    RegCat();//сначала происходит регистрация 
    CashCat();//далее происходит работа с данными и открытие шлюзов
    sleep(1);//задержка в 1 секунду
    }
    return 0;
}
void CashCat()
{
    int k;
    char command[30];
    if (size!=sizepr){
        system("systemctl disable --now vblade.service");
        system("systemctl enable --now vblade.service");
        if (sizepr=-1)
            k=0;
        else
            k=sizepr;
        for (int i=0;i<k;++i)
        {
            free(arrpr[i]);
        }
        arrpr=(char**)realloc((char**)arrpr,(size+1)*sizeof(char*));
        sizepr=-1;
        for (int i=0;i<size+1;++i)
        {
            arrpr[i]=(char*)malloc(10*sizeof(char));
            memcpy(arrpr[i], arr[i],10);
            sprintf(command,"vbladed 9 %d -r eth0 %s",i,arr[i]);
            printf("%s\n",command);
        }
        printf("CashCat:\n");
        for (int i=0;i<size+1;++i)
        {
            printf(arrpr[i]);
            printf("            ");
            printf(arr[i]);
            printf("            ");
            printf("%d      %d", size, sizepr);
            printf("\n");
        }
        printf("-------------------------------------------\n");
    }
    for (int i=0;i<size+1;++i)
    {
        free(arr[i]);
    }
    free(arr);
    sizepr=size;
    size=-1;
    char** arr=(char**)malloc(1*sizeof(char*));
}
void RegCat()
{
    int i=0;
    char string[20];
    bool pattern2flg=0;
    regex_t preg, preg2;
    DIR *mydir;
    char pattern2[20]={0};
    struct dirent *myfile;
    //struct stat mystat;
    int err,regerr, err2, regerr2;
    //mydir = opendir(argv[1]);
    mydir = opendir(STRING);
    err = regcomp (&preg, PATTERN, REG_EXTENDED);
    if (err != 0) {
        char buff[512];
        regerror(err, &preg, buff, sizeof(buff));
        //printf("%s",buff);
    }
    char errbuf[512];
    regmatch_t pm, pm2;
    while((myfile = readdir(mydir)) != NULL)
    {       
        regerr = regexec (&preg, myfile->d_name, 0, &pm, 0);
        if (regerr == 0) {
            i=0;
            //printf("%s-true\n", myfile->d_name);
            sprintf(pattern2, "^%s.$",myfile->d_name);
            //printf("pattern==%s\n", pattern2);
            err2 = regcomp (&preg2, pattern2, REG_EXTENDED);
            pattern2flg=1;
            DIR *mydir1;
            struct dirent *myfile1;
            mydir1 = opendir(STRING);
            if (err2 != 0) {
                char buff2[512];
                regerror(err2, &preg2, buff2, sizeof(buff2));
                //printf("%s",buff2);
            }
            while((myfile1 = readdir(mydir1)) != NULL){
                regerr2 = regexec (&preg2, myfile1->d_name, 0, &pm2, 0);
                if (regerr2 == 0) {
                    ++i;
                    size++;
                    sprintf(string,"/dev/%s",myfile1->d_name);
                    //sprintf(command,"vbladed 9 1 eth0 /dev/%s", myfile1->d_name);

                    if (size)
                    {
                        arr=(char**)realloc((char**)arr,(size+1)*sizeof(char*));
                    }
                    arr[size]=(char*)malloc(10*sizeof(char));
                    sprintf(arr[size],"%s",string);

                    if (pid==0){
                        int l;
                        //system(command);
                        //printf("%s-%d\n",string,l);
                    }
                }
            }
            if (!i){
                sprintf(string,"/dev/%s",myfile->d_name);
                size++;
                if (size)
                    {
                        arr=(char**)realloc((char**)arr,(size+1)*sizeof(char*));
                    }
                arr[size]=(char*)malloc(10*sizeof(char));
                sprintf(arr[size],"%s",string);
                //sprintf(command,"vbladed 9 %d eth0 /dev/%s",i, myfile->d_name);
                    //execl("vblade", "9","1","wlp3s0",string,NULL);
                    if (pid==0){
                        int l;
                        //system(command);
                        //printf("%s-%d\n",string,l);
                    }
            }
            closedir(mydir1);
        }
    }
    closedir(mydir);
}
