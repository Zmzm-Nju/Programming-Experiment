#include "common.h"
#include "control.h"
#include "calculate.h"
#include "command_deal.h"
extern vector<Poly*> polys;

void Input()
{
    bool exit = false;
    while(!exit)
    {
        int n = 0;
        char str[100];
        Poly* head = NULL,*tail = NULL;
        printf("请输入多项式名称:");//获取多项式名称
        scanf("%s",str);
        string name = str;
        Poly *cur = Search_Poly(name);
        while(cur != NULL)
        {
            printf("该多项式已存在，请重新输入名称:");
            scanf("%s",str);
            name = str;
            cur = Search_Poly(name);
        }
        printf("请输入多项式长度:");//获取多项式长度
        scanf("%d",&n);
        printf("请输入多项式各项系数:");
        for(int i = 0; i < n; i++)
        {
            Poly* p = new Poly;
            p->n = n-i-1;
            scanf("%lf",&p->coe);//获取多项式系数
            p->name = name;
            if(head == NULL)
                head = p;
            else
                tail->next=p;
            tail = p;
        }
        head = Modify_Poly(head);
        polys.push_back(head);//属于该多项式的链表头节点存入vector中
        printf("输入成功，是否继续输入(y/n):");
        char ch;
        scanf(" %c",&ch);
        if(ch != 'y')
            exit = true;
        printf("\n");
    }
}

void View()
{
    char ch = '\0';
    while(true)
    {
        char str[100];
        string name;
        printf("请输入需要查看的多项式的名称:");
        scanf("%s",str);
        name = str;
        Poly* cur = Search_Poly(name);
        if(cur != NULL)
        {
            cout << name << " = ";
            Print_Poly(cur);
            printf("\n查看成功!是否继续查看:(y/n)");
            scanf(" %c",&ch);
            printf("\n");
            if(ch != 'y') break; 
        }
        else
        {
            printf("不存在该多项式!是否重新输入:(y/n)");
            scanf(" %c",&ch);
            printf("\n");
            if(ch != 'y') break;
        }
    }
}

void View_All()
{
    printf("当前所有已输入多项式有:\n");
    for (int i = 0; i < polys.size();i++)
    {
        cout << polys[i]->name << " = " ;
        Print_Poly(polys[i]);
        printf("\n");
    }
    printf("\n");
}

void Calculate_One()
{
    char ch = '\0';
    while(true)
    {
        char str[100];
        string name;
        printf("请输入需要计算的多项式的名称:");
        scanf("%s",str);
        name = str;
        Poly* cur = Search_Poly(name);
        if(cur != NULL)
        {
            double num;
            printf("请输入数字的大小:");
            scanf("%lf",&num);
            cout << name << " = ";
            Print_Poly(cur);
            printf("在x = %g处的值为 %g\n",num,Calculate_Poly(num,cur));
            printf("计算成功!是否继续计算:(y/n)");
            scanf(" %c",&ch);
            printf("\n");
            if(ch != 'y') break;
        }
        else
        {
            printf("不存在该多项式!是否重新输入:(y/n)");
            scanf(" %c",&ch);
            printf("\n");
            if(ch != 'y') break;
        }
    }
}


void Calculate()
{
    bool exit = false;
    char ch = '\0';
    char str[100] = "\0";
    while(true)
    {
    Begin:
        printf("请输入混合表达式:");
        string s;
        scanf("%s",str);
        s = str;
        string exe[100];
        int k = String_Split(s,exe);//将混合表达式拆分至string数组exe中
        if(Expression_Legal(s,exe,k) == false)
        {
            printf("表达式不合法!是否重新输入:(y/n)");
            scanf(" %c",&ch);
            printf("\n");
            if(ch != 'y') return;
            else goto Begin;
        }
        for(int i = 0; i < k; i++)
        {
            if(!Is_Operator(exe[i][0]) && Search_Poly(exe[i]) == NULL)
            {
                cout <<"多项式"<< exe[i] <<"不存在!是否重新输入:(y/n)";
                scanf(" %c",&ch);
                printf("\n");
                if(ch != 'y') return;
                else goto Begin;
            }
        }//查询多项式是否都存在
        Poly *p = Transform_And_Calculate(exe, k);
        cout << s << " = ";
        Print_Poly(p);
        printf("\n运算成功!是否继续运算:(y/n)");
        scanf(" %c",&ch);
        printf("\n");
        if(ch != 'y')  return;
    }
}

void Extract()
{
    char ch = '\0';
    char str[100] = "\0";
    string name = "\0";
    Poly *cur = NULL;
    double a = 0,b = 0,c = 0;
    while(true)
    {
        printf("请输入需要求根的一次/二次多项式的名称:");
        scanf("%s",str);
        name = str;
        cur = Search_Poly(name);
        if(cur == NULL)
        {
            printf("不存在此多项式!是否重新输入(y/n):");
            scanf(" %c",&ch);
            printf("\n");
            if(ch != 'y')  break;
        }
        else if(cur->n > 2 || cur->n == 0)
        {
            printf("不是一次/二次多项式!是否重新输入(y/n):");
            scanf(" %c",&ch);
            printf("\n");
            if(ch != 'y')  break;
        }
        else if(cur->n == 1)
        {
            a = cur-> coe;
            if(cur->next != NULL) b = cur->next->coe;
            Print_Poly(cur);
            printf(" = 0 的解是: x = %g\n",-b/a);
            a = 0, b = 0, c = 0;
            printf("计算成功!是否继续计算(y/n):");
            scanf(" %c",&ch);
            printf("\n");
            if(ch != 'y')  break;
        }
        else
        {
            a = cur->coe;//a为二次项系数
            if(cur->next != NULL)//下一个节点存在
            {
                if(cur->next->n == 1) b = cur->next->coe;
                else if(cur->next->n == 0) c = cur->next->coe; 
                if(cur->next->next != NULL) c = cur->next->next->coe;
            }
            Print_Poly(cur);
            printf(" = 0 的解是: ");
            double disc = b*b-4*a*c;
	    if(disc >= -EPS && disc <= EPS)
		printf("x1 = x2 = %g\n",-b/(2*a));
	    else if(disc > 0)
		printf("x1 = %g, x2 = %g\n",
				(-b+sqrt(disc))/(2*a),
				(-b-sqrt(disc))/(2*a));
	    else
		printf("x1 = %g+%gi, x2 = %g-%gi\n",
                                       -b/(2*a),sqrt(fabs(disc))/(2*a),  
                                       -b/(2*a),sqrt(fabs(disc))/(2*a));
            printf("计算成功!是否继续计算(y/n):");
            scanf(" %c",&ch);
            printf("\n");
            if(ch != 'y')  break;
        }
    }
}


