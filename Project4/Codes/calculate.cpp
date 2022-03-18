#include "common.h"
#include "calculate.h"

Poly* Der_Poly(Poly *A)
{
    Poly *head = Copy_Poly(A), *cur = head;
    while(cur)
    {
        cur->coe *= cur->n;
        if(cur->n != 0) (cur->n)--;
        cur = cur->next;
    }
    head = Modify_Poly(head);
    return head;
}

Poly* Add_Poly(Poly *A,Poly *B)
{
    Poly* head = NULL;
    if(A->n >= B->n)
    {
        head = Copy_Poly(A);
        Poly *pre = head,*cur = head->next;
        while(B)
        {
            pre = head,cur = head->next;
            while(cur)
            {
                if(B->n == pre->n)
                {
                    pre->coe += B->coe;
                    break;
                }//次数相同，系数累加
                else if(B->n > cur->n)
                {
                    Poly *p = new Poly;
                    p->n = B->n;
                    p->coe = B->coe;
                    p->name = "\0";
                    pre->next = p;
                    p->next = cur;
                    break;
                }//刚好介于两节点系数之间，新建节点插入
                pre = pre->next;
                cur = cur->next;
            }
            if(cur == NULL)//cur为NULL还未找到恰当节点插入，则只能插入在最后一位
            {
                if(B->n == pre->n)
                    pre->coe += B->coe;
                else{
                    Poly *p = new Poly;
                    p->n = B->n;
                    p->coe = B->coe;
                    p->name = "\0";
                    pre->next = p;
                    p->next = NULL;
                }
            }
            B = B->next;
        }
    }
    else 
    {
        head = Copy_Poly(B);
        Poly *pre = head,*cur = head->next;
        while(A)
        {
            pre = head,cur = head->next;
            while(cur)
            {
                if(A->n == pre->n)
                {
                    pre->coe += A->coe;
                    break;
                }//次数相同，系数累加
                else if(A->n > cur->n)
                {
                    Poly *p = new Poly;
                    p->n = A->n;
                    p->coe = A->coe;
                    p->name = "\0";
                    pre->next = p;
                    p->next = cur;
                    break;
                 }//刚好介于两节点系数之间，新建节点插入
                pre = pre->next;
                cur = cur->next;
            }
            if(cur == NULL)//cur为NULL还未找到恰当节点插入，则只能插入在最后一位
            {
                if(A->n == pre->n)
                    pre->coe += A->coe;
                else{
                    Poly *p = new Poly;
                    p->n = A->n;
                    p->coe = A->coe;
                    p->name = "\0";
                    pre->next = p;
                    p->next = NULL;
                }
            }
            A = A->next;
        }
    }
    head = Modify_Poly(head);
    return head;
}

Poly* Mul_Poly(Poly *A,Poly *B)
{
    Poly* sum = Copy_Poly(A),*cur = sum;
    while(cur)
    {
        cur->n = cur->n + B->n;
        cur->coe = cur->coe * B->coe;
        cur = cur->next;
    }
    B = B->next;//A与B的第一个节点相乘，拿出来作为sum初始值
    while(B)
    {
        Poly* tmp = Copy_Poly(A), *cur = tmp;
        while(cur)
        {
            cur->n = cur->n + B->n;
            cur->coe = cur->coe * B->coe;
            cur = cur->next;
        }
        Poly *sp = sum;
        sum = Add_Poly(sp,tmp);
        Delete_Poly(sp);
        Delete_Poly(tmp);//删除中间产生的链表
        B = B->next;
    }//遍历B，逐项相乘，结果相加
    sum = Modify_Poly(sum);
    return sum;
} 

Poly* Int_Poly(Poly *A,string Interval)
{
    Poly* head = Copy_Poly(A), *cur = head;
    while(cur)
    {
        (cur->n)++;
        cur->coe = cur->coe/cur->n;
        cur = cur->next;
    }
    string s1,s2;
    int m = 0,n = 0;//查询两个数字的长度
    for(int i = 2;i < Interval.size();i++)
        if(Interval[i]!=',')
            m++;
        else break;
    for(int i = m + 3;i < Interval.size();i++)
        if(Interval[i]!=']')
            n++;
        else break;
    s1.assign(Interval,2,m);
    s2.assign(Interval,m+3,n);
    double a = Calculate_Poly(String_to_double(s2),head);
    double b = Calculate_Poly(String_to_double(s1),head);
    double c = a - b;
    Poly *p = new Poly;
    p->n = 0;
    p->coe = c;
    p->name = "\0";
    p->next = NULL;
    Delete_Poly(head);
    return p; 
}    

double String_to_double(string number)
{
    double num;
    stringstream ss;
    ss << number;
    ss >> num;
    return num;
}




