#include "function.h"
#include "wc.h"

void wc(Command a)
{
    a.legal=wc_legal(a);
    if(!a.legal)
    {
        cout << "The form of Command \"wc\" is illegal!" << endl;
        cout << "Try \"man wc\" for more information." << endl;
        return;
    }
    FILE* fp = fopen(a.file1,"r");
    if(fp == NULL)
    {
        cout << "wc: " << a.file1 << ": No such file or directory" << endl;
        return;
    }
    else
        fclose(fp);
    File* head = deal_with_file(a.file1);
    if(!strcmp(a.option,"-c"))
    {
        int byte = 0;
        while(head)
        {
            byte = byte + strlen(head->line) + 1;//'\n'
            head = head->next;
        }
        printf("%d %s\n",byte,a.file1);
    }
    else if(!strcmp(a.option,"-w"))
    {
        int word = 0;
        while(head)
        {
            if(head->line[0] && head->line[0]!=' ' && head->line[0]!='\t')
                    word++;//'Enter' is also a kind of delimiter
            for(int m = 0;head->line[m] && head->line[m+1]; m++)
            {
                if((head->line[m]==' '||head->line[m]=='\t')&&(head->line[m+1]!=' '&&head->line[m+1]!='\t'))
                {
                    word++;//Converted from delimiter to character,word++
                }
            }
            head = head->next;
        }
        printf("%d %s\n", word, a.file1);
    }
    else if(!strcmp(a.option,"-l"))
    {
        while(head->next)
            head = head->next;
        printf("%d %s\n",head->n,a.file1);
    }
    else if(a.option[0] == '\0')
    {
        int byte = 0;
        File* cur = head;
        while(cur)
        {
            byte = byte + strlen(cur->line) + 1;//'\n'
            cur = cur->next;
        }
        int word = 0;
        cur = head;
        while(cur)
        {
            if(cur->line[0] && cur->line[0]!=' ' && cur->line[0]!='\t')
                    word++;//'Enter' is also a kind of delimiter
            for(int m = 0;cur->line[m] && cur->line[m+1]; m++)
            {
                if((cur->line[m]==' '||cur->line[m]=='\t')&&(cur->line[m+1]!=' '&&cur->line[m+1]!='\t'))
                {
                    word++;//Converted from delimiter to character,word++
                }
            }
            cur = cur->next;
        }
        cur = head;
        while(cur->next)
            cur = cur->next;
        printf("%d %d %d %s\n",cur->n,word,byte,a.file1);
    }
    else 
    {
        printf("wc: invalid option -- '%s'\n",a.option+1);
        printf("Try 'man wc' for more informtion.\n");
    }
    return;
}



bool wc_legal(Command a)
{
    if(a.file1[0] == '\0')
       return false;//Lack of file name, illegal
    if(a.file2[0] != '\0')
       return false;//More than one file, illegal
    if(a.rest[0] != '\0')
       return false;//There should be nothing after the two file names
    return true;
}


