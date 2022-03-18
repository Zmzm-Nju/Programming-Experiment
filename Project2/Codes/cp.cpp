#include "function.h"
#include "cp.h"

void cp(Command a)
{
    a.legal=cp_legal(a);
    if(!a.legal)
    {
        cout << "The form of Command \"cp\" is illegal!" << endl;
        cout << "Try \"man cp\" for more information." << endl;
        return;
    }
    if(a.option[0]=='\0')
        copy_file(a.file1,a.file2);
    else if(!strcmp(a.option,"-r"))
    {
        if(!strcmp(a.file1,a.file2))
        {
            printf("cp: cannot copy a directory, '%s', into itself, '%s/%s'\n",a.file1,a.file1,a.file1);
            return;
        }
        char dir1[256],dir2[256];
        getcwd(dir1, sizeof(dir1));
        strcat(dir1,"/");
        strcat(dir1,a.file1);
        getcwd(dir2, sizeof(dir2));
        strcat(dir2,"/");
        strcat(dir2,a.file2);
        DIR* dirp1 = opendir(dir1);
        if(dirp1 == NULL)
        {
            cout << "cp: cannot stat '"<< a.file1 << "': No such file or directory" << endl;
            return ;
        }
        closedir(dirp1);
        DIR* dirp2 = opendir(dir2);   
        if(dirp2 == NULL)
            mkdir(dir2,S_IRWXU);
        else
        {
            closedir(dirp2);
            strcat(dir2,"/");
            strcat(dir2,a.file1);
            mkdir(dir2,S_IRWXU);
        }
        copy_dir(dir1,dir2);
    }
    else
    {
        printf("cp: invalid option -- '%s'\n",a.option+1);
        printf("Try 'man cp' for more informtion.\n");
    }
}

bool cp_legal(Command a)
{
    if(a.file1[0] == '\0'||a.file2[0] == '\0')
       return false;//The number of files is less than 2, illegal
    if(a.rest[0] != '\0')
       return false;//There should be nothing after the two files
    return true;
}

void copy_file(char*s1,char*s2)
{
    if(!strcmp(s1,s2))
    {
        printf("cp: '%s' and '%s' are the same file\n",s1,s2);
        return;
    }
    ifstream in;
    in.open(s1, ios::in|ios::binary);
    if(!in.is_open())
    {
        cout <<"cp: cannot stat '"<< s1 <<"': No such file or directory"<< endl;
        return;
    }
    ofstream out;
    out.open(s2,ios::out|ios::binary|ios::trunc);
    if(!out.is_open())
    {
        cout << "Unknown error!" << endl;
        return;
    }
    out << in.rdbuf();
    in.close();
    out.close();
    return;
}

void copy_dir(char*dir1,char*dir2)
{
    DIR* dirp1 = opendir(dir1);
    DIR* dirp2 = opendir(dir2);
    if(dirp2 == NULL)
        mkdir(dir2,S_IRWXU);
    dirent* cur = readdir(dirp1);
    char file1[256];
    char file2[256];
    while(cur != NULL)
    {
        if(!strcmp(cur->d_name,"..")||!strcmp(cur->d_name,"."))
        {
            cur = readdir(dirp1);
            continue;
        }
        strcpy(file1,dir1);
        strcat(file1,"/");
        strcat(file1,cur->d_name);
        strcpy(file2,dir2);
        strcat(file2,"/");
        strcat(file2,cur->d_name);
        if(cur->d_type == 8)
           copy_file(file1,file2);
        if(cur->d_type == 4)
           copy_dir(file1,file2);
        cur = readdir(dirp1);
    }
    closedir(dirp1);
}

