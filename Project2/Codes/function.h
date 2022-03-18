#ifndef ZMZM_Fun
#define ZMZM_Fun

struct Command
{
    char command[10];//the name of the command
    char option[5];//the option of the command(if it exists)
    char file1[50];//the name of the first file 
    char file2[50];//the name of the second file
    char rest[50];//the rest of the command line
    bool legal;//whether the command line is legal
};
struct File
{
    int  n;//the ordinal of the line
    char line[1024];//the content of the line
    File* next;
};
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;
File* deal_with_file (char * s);
Command deal_with_command (char * s);

#endif
