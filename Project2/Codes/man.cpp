#include "function.h"
#include "man.h"

void man(Command a)
{
    a.legal=man_legal(a);
    if(!a.legal)
    {
        cout << "The form of Command \"man\" is illegal!" << endl;
        cout << "Try \"man man\" for more information." << endl;   
        return;
    }
    if(!strcmp(a.file1,"cp"))
    {
        cout << endl << "NAME:" << endl;
        cout << "cp - copy files and directories." << endl;
        cout << "SYNOPSIS:" << endl;
        cout << "cp (-r) file1 file2" << endl;
        cout << "DESCRIPTION:" << endl;
        cout << "The Command will copy file1 to file2." << endl;
        cout << "With the OPTION '-r', it will copy directories recursively." << endl;
        cout << "If the file or directory 'file1' does not exist,then the action will be failed." << endl << endl;  
    }
    else if(!strcmp(a.file1,"cmp"))
    {    
        cout << endl << "NAME:" << endl;
        cout << "cmp - compare two files byte by byte." << endl;
        cout << "SYNOPSIS:" << endl;
        cout << "cmp file1 file2" << endl;
        cout << "DESCRIPTION:" << endl;
        cout << "The Command will compare two files byte by byte." << endl;
        cout << "If they are totally the same, nothing will happen." << endl;
        cout << "Or the shell will show you which byte and line does the first difference appear on." << endl << endl;
    }    
    else if(!strcmp(a.file1,"cat"))
    {
        cout << endl << "NAME:" << endl;
        cout << "cat - concatenate files and print on the standard output." << endl;
        cout << "SYNOPSIS:" << endl;
        cout << "cat file1" << endl;
        cout << "DESCRIPTION:" << endl;
        cout << "The Command will concatenate FILE(s) to standard output." << endl;
        cout << "By the way,this command needs no OPTIONS." << endl << endl;
    }
    else if(!strcmp(a.file1,"wc"))
    {     
        cout << endl << "NAME:" << endl;
        cout << "wc - print newline, word, and byte counts for each file." << endl;
        cout << "SYNOPSIS:" << endl;
        cout << "cp (-c/-w/-l) file1" << endl;
        cout << "DESCRIPTION:" << endl;
        cout << "The Command will print newline, word, and byte counts of the FILE." << endl;
        cout << "A word is a non-zero-length sequence of characters delimited by white space." << endl;
        cout << "-c, --bytes  print the byte counts." << endl;
        cout << "-w, --words  print the word counts." << endl;
        cout << "-l, --lines  print the newline counts." << endl << endl;
    }
    else if(!strcmp(a.file1,"man"))
    {
        cout << endl << "NAME:" << endl;
        cout << "man - an interface to the on-line reference manuals." << endl;
        cout << "SYNOPSIS:" << endl;
        cout << "man cp/wc/cat/cmp/man" << endl;
        cout << "DESCRIPTION:" << endl;
        cout << "The Command will show you the way to use another command." << endl;
        cout << "The name, synopsis and descriptions will be included." << endl << endl;
    }
    else if(!strcmp(a.file1,"sh"))
    {
        cout << endl << "NAME:" << endl;
        cout << "dash - command interpreter (shell)" << endl;
        cout << "SYNOPSIS:" << endl;
        cout << "sh text.sh" << endl;
        cout << "DESCRIPTION:" << endl;
        cout << "The Command can help you to deal with many command lines in one time." << endl;
        cout << "The contents in 'text.sh' should only be command lines seperated by 'Enter'." << endl << endl;
    }

    else
        cout << "No manual entry for " << a.file1 << endl;
}

bool man_legal(Command a)
{
    if(a.option[0]!='\0')  
       return false;//No Options
    if(a.file1[0]=='\0')
       return false;//If there is no command stored in file1,the command line isillegal
    if(a.file2[0]!='\0')
       return false;//Just one command stored in file1 is legal
    if(a.rest[0]!='\0')
       return false;//Just one command stored in file1 is legal
    return true;
}

