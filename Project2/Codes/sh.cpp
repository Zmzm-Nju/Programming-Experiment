#include "function.h"
#include "sh.h"
#include "cp.h"
#include "wc.h"
#include "man.h" 
#include "cat.h"
#include "cmp.h"

void sh(Command a)
{
    a.legal=sh_legal(a);
    if(!a.legal)
    {
        cout << "The form of Command \"sh\" is illegal!" << endl;
        cout << "Try \"man sh\" for more information." << endl;
        return;
    }
    FILE* fp = fopen(a.file1,"r");
    if(fp == NULL)
    {
        cout << "sh: 0: Can't open " << a.file1 << endl;
        return;
    }
    char str[100];
    fscanf(fp,"%[^\n]",str);
    fgetc(fp);
    while(!feof(fp))
    {  
        Command b = deal_with_command(str);
        if(!strcmp(a.command,"exit")) break;
        else if(!strcmp(b.command,"cp")) cp(b);
        else if(!strcmp(b.command,"sh")) sh(b);
        else if(!strcmp(b.command,"wc")) wc(b);
        else if(!strcmp(b.command,"man")) man(b);
        else if(!strcmp(b.command,"cat")) cat(b);
        else if(!strcmp(b.command,"cmp")) cmp(b);
        else
            cout << "No command '"<< a.command <<"' found!" << endl;
        if(fscanf(fp,"%[^\n]",str)!=1) break;
        fgetc(fp);
    }
    fclose(fp);
}

bool sh_legal(Command a)
{
   if(a.option[0]!='\0')
       return false;//No Options
    if(a.file1[0]=='\0')
       return false;//If there is no file name stored in file1,the command line is illegal
    if(a.file2[0]!='\0')
       return false;//Just one file can be dealt with
    if(a.rest[0]!='\0')
       return false;//Just one file can be dealt with
    return true;
}


