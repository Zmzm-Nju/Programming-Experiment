#include "common.h"
#include "control.h"
#include "calculate.h"
#include "command_deal.h"
vector<Poly*> polys;
int main()
{
    int status = 0;//判断计算器所执行的功能
    bool exit = false;//判断是否退出
    while(!exit)
    {
        Title();
        scanf("%d",&status);
        while(status > 7 || status < 1)
        {
            printf("序号输入有误!请重新输入:");
            scanf("%d",&status);
        }
        switch(status)
        {
            case 1: Input();break;
            case 2: View();break;
            case 3: View_All();break;
            case 4: Calculate();break;
            case 5: Calculate_One();break;
            case 6: Extract();break;
            case 7: exit = true;break;
        }
    }
    printf("退出成功！感谢您的使用！\n");
    for (int i = 0; i < polys.size();i++)
        Delete_Poly(polys[i]);//删除链表
    return 0;
}


