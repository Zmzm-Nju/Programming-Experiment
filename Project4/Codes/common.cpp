#include "common.h"
extern vector<Poly*> polys;

void Title()
{
    for(int i = 0; i < 62; i++)
        printf("=");
        printf("\n");
    printf("1.输入多项式 2.查看多项式 3.查看全部多项式\n4.混合运算   5.多项式求值 6.一次/二次多项式求根  7.退出计算器\n");
    for(int i = 0; i < 62; i++)
        printf("=");
        printf("\n");
    printf("请输入您需要执行的功能:");
}

Poly* Search_Poly(string name)
{
    Poly* cur = NULL;
    for (int i = 0; i < polys.size();i++)
    {
        if (polys[i]->name ==  name)
        {
            cur = polys[i];
            break;
        }
    }
    return cur;
}

Poly* Modify_Poly(Poly *head)
{
    string name = head->name;
    while(head!=NULL && fabs(head->coe) < EPS)
    {
        Poly *p = head;
        head = head->next;
        delete(p);
    }//头节点单独处理
    if(head != NULL)//如果链表不为空,即系数不全为0
    {
        bool del = false;
        //判断是否删除节点,以确定if语句后需不需要有一个cur=cur->next
        Poly *pre = head,*cur = head->next;
        while(cur)         
        {
            del = false;
            if(fabs(cur->coe) < EPS)
            {
                Poly *p = cur;
                pre->next = cur->next;
                cur = cur->next;
                delete(p);
                del = true;
            }
            if(!del)
            {
                pre = pre->next;
                cur = cur->next;
            } 
        }//删除系数为0的节点
    }
    if(head == NULL)//在输入系数全为0的情况下，链表节点会被删完，次数我们仍>需要保留一个常数项节点0
    {
        Poly* p = new Poly;
        p->n = 0;
        p->coe = 0;
        p->name = name;
        p->next = NULL;
        head = p;
    }
    return head;
}

Poly* Copy_Poly(Poly *poly)
{
    Poly* head = NULL,*tail = NULL;
    while(poly)
    {
        Poly* p = new Poly;
        p->n = poly->n;
        p->coe = poly->coe;
        p->name = "\0";
        p->next = NULL;
        if(head == NULL)
            head = p;
        else
            tail->next=p;
        tail = p;
        poly = poly->next;
    }
    return head;
}


void Delete_Poly(Poly* poly)
{
    while(poly)
    {
        Poly* cur = poly;
        poly = poly->next;
        delete(cur);
    }
}

void Print_Poly(Poly* poly)
{
    Poly* cur = poly;
    if(cur->coe < 0)
        printf("-");//该项<0，输出'-'
    if(fabs(fabs(cur->coe) - 1) > EPS)
        printf("%g",fabs(cur->coe));//系数不为1or-1,输出系数     
    if(cur->n != 1&&cur->n != 0)
        printf("x^%d",cur->n);//指数不为1or0，输出'x^n'
    else if(cur->n == 1)
        printf("x");          //指数为1,只输出'x'
    else if(cur->n == 0 && fabs(fabs(cur->coe) - 1) < EPS)
        printf("1");  
    cur = cur->next;//第一项前面不需要加号
    while(cur)
    {
        if(cur->coe > 0)
            printf(" +");//该项>0，输出'+'
        else if(cur->coe < 0)
            printf(" -");//该项<0，输出'-'
        if(fabs(fabs(cur->coe) - 1) > EPS)
            printf("%g",fabs(cur->coe));//系数不为1or-1,输出系数 
        if(cur->n != 1&&cur->n != 0)
            printf("x^%d",cur->n);//指数不为1or0，输出'x^n'
        else if(cur->n == 1)
            printf("x");          //指数为1,只输出'x'
        else if(cur->n == 0 && fabs(fabs(cur->coe) - 1) < EPS)
            printf("1");          //指数为0,仅当系数为1or-1,输出'1'
        cur = cur->next;
   }
}

double Calculate_Poly(double n,Poly *poly)
{
    double sum = 0;
    Poly *cur = poly;
    while(cur)
    {
        sum = sum + cur->coe*pow(n,cur->n);    
        cur = cur->next;
    }
    return sum;
}


