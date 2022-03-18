#include "function.h"

Command deal_with_command (char * s)
{
    Command a;
    int i = 0,j = 0;
    while(s[i] != ' ' && s[i] != '\0')
    {
         a.command[j] = s[i];
         i++, j++;   
    }
    a.command[j] = '\0', j = 0;
    while(s[i] == ' ')
         i++;//skip the blank spaces
    if(s[i] == '-')
    {
        while(s[i] != ' ' && s[i] != '\0')
        {
            a.option[j] = s[i];
            i++, j++;
        }
    }//if the option exists,store it
    a.option[j] = '\0', j = 0;
    while(s[i] == ' ')
        i++;//skip the blank spaces
    while(s[i] != ' ' && s[i] != '\0')
    {
         a.file1[j] = s[i];
         i++, j++;   
    }
    a.file1[j] ='\0', j = 0;
    while(s[i] == ' ')
         i++;//skip the blank spaces
    while(s[i] != ' ' && s[i] != '\0')
    {
         a.file2[j] = s[i];
         i++, j++;
    }
    a.file2[j] = '\0', j = 0;
    while(s[i] == ' ')
         i++;//skip the blank spaces
    while(s[i] != '\0')
    {
         a.rest[j] = s[i];
         i++, j++;
    }
    a.rest[j] = s[i];
    a.legal = true;
    return a;
}

File* deal_with_file (char * s)
{
    char str[1024];
    FILE* fp = fopen(s,"r");
    File* head = NULL, *tail=NULL;
    if(fscanf(fp,"%[^\n]",str) == 0)
        str[0]='\0';
    fgetc(fp);//skip the enter
    int k = 1;
    while(!feof(fp))
    {
        File* p = new File;
        strcpy(p->line,str);
        p->n = k, k++;
        p->next = NULL;
        if(head == NULL)
            head = p;
        else
            tail->next = p;
        tail = p;
        if(fscanf(fp,"%[^\n]",str)==0)
        {
            str[0]='\0';
        }
        fgetc(fp);
    }
    fclose(fp);
    return head;
} 
