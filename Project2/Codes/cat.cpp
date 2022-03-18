#include "function.h"
#include "cat.h"

void cat(Command a)
{
    a.legal=cat_legal(a);
    if(!a.legal)
    {
        cout << "The form of Command \"cat\" is illegal!" << endl;
        cout << "Try \"man cat\" for more information." << endl;
        return;
    }
    FILE* fp = fopen(a.file1,"r");
    if(fp == NULL)
    {
        cout << "cat: " << a.file1 << ": No such file or directory" << endl;
        return;
    }
    else
        fclose(fp);
    File* head = deal_with_file(a.file1);
    while(head)
    {
        printf("%s\n",head->line);
        head = head->next;
    }
}

bool cat_legal(Command a)
{
    if(a.option[0]!='\0')
       return false;//No Options
    if(a.file1[0]=='\0')
       return false;//If there is no file name stored in file1,the command line is illegal
    if(a.file2[0]!='\0')
       return false;//Just one file can be displayed
    if(a.rest[0]!='\0')
       return false;//Just one file can be displayed
    return true;
}

