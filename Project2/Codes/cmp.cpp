#include "function.h"
#include "cmp.h"

void cmp(Command a)
{
    a.legal=cmp_legal(a);
    if(!a.legal)
    {
        cout << "The form of Command \"cmp\" is illegal!" << endl;
        cout << "Try \"man cmp\" for more information." << endl;
        return;
    }
    bool exist = true;
    FILE* fp1 = fopen(a.file1,"r");
    FILE* fp2 = fopen(a.file2,"r");
    if(fp1 == NULL)
    {
        cout << "cmp: " << a.file1 << ": No such file or directory" << endl;
        exist = false;
    }
    else
        fclose(fp1);
    if(fp2 == NULL)
    {
        cout << "cmp: " << a.file2 << ": No such file or directory" << endl;
        exist = false;
    }
    else
        fclose(fp2);
    if(!exist) return;//Judge whether both of the two files exist
    bool same = true;
    int byte = 0;//Record the bytes of the file
    File* head1 = deal_with_file(a.file1);
    File* head2 = deal_with_file(a.file2);
    while(head1&&head2)
    {
        if(strcmp(head1->line,head2->line))
        {
            same = false;
            break;
        }//Find differences,then jump out of the loop
        byte = byte + strlen(head1->line) + 1;//'\n'
        head1 = head1->next;
        head2 = head2->next;
    }
    if(head1 && !head2)
    {
        printf("cmp: EOF on %s\n", a.file2); 
        return;
    }
    if(head2 && !head1)
    {
        printf("cmp: EOF on %s\n", a.file1);
        return;
    }//One of the two files has come to its end
    if(!same)
    {   
        int n =0;
        while(head1->line[n] && head2->line[n])
        {
            if(head1->line[n] != head2->line[n])
                 break;
            n++;
            byte = byte + 1;
        }
        printf("%s %s differ: byte %d, line %d\n",a.file1, a.file2, byte+1, head1->n);
    }//Both of the two files haven't come to their ends
}



bool cmp_legal(Command a)
{
    if(a.option[0] != '\0')
       return false;//No Options
    if(a.file1[0] == '\0'||a.file2[0] == '\0')
       return false;//The number of files is less than 2, illegal
    if(a.rest[0] != '\0')
       return false;//There should be nothing after the two files
    return true;
}


