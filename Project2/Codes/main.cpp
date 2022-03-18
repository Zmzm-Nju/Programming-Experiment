#include "function.h"
#include "sh.h"
#include "cp.h"
#include "wc.h"
#include "man.h"
#include "cat.h"
#include "cmp.h"
int main()
{
    char s[200];
    while(true)
    {
        cout << "Please input your command:";
        scanf("%[^\n]",s);
        getchar();//store the 'enter'
        Command a = deal_with_command(s);
        if(!strcmp(a.command,"exit")) break;
        else if(!strcmp(a.command,"cp")) cp(a);
        else if(!strcmp(a.command,"sh")) sh(a);
        else if(!strcmp(a.command,"wc")) wc(a);
        else if(!strcmp(a.command,"man")) man(a);
        else if(!strcmp(a.command,"cat")) cat(a);
        else if(!strcmp(a.command,"cmp")) cmp(a);
        else
            cout << "No command '"<< a.command <<"' found!" << endl;
    }
    cout << "Successfully Exit!" << endl;
    return 0;
}
