#include "common.h"
#include "calculate.h"
#include "command_deal.h"
extern vector<Poly*> polys;

bool Is_Operator(char ch)
{
    if(ch == '('||ch == ')') return true;
    if(ch == '+'||ch == '*') return true;
    if(ch == '$'||ch == '!') return true;
    return false;
}

bool Expression_Legal(string s,string exe[],int k)
{
    int left = 0, right = 0;
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == '(') left++;
        if(s[i] == ')') right++;
        if(right > left)  break; 
    }
    if(left != right)  return false;//先看括号是否配对
    int a = 0, b = 0, c = 0;
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == '$') a++;
        if(s[i] == '[') b++;
        if(s[i] == ']') c++;
    }
    if(a!=b || a!=c || b!=c)  return false;//再看定积分和中括号是否配对
    if(exe[0][0] == '+'||exe[0][0] == '*'||exe[0][0] == ')'||exe[0][0] == '!')
        return false;//以多项式名、左括号、定积分符开头
    if(exe[k-1][0] == '+'||exe[k-1][0] == '*'||exe[k-1][0] == '('||exe[k-1][0] == '$')  return false;//以右括号、多项式名、求导符结尾
    for(int i = 0;i < k - 1;i++)
    {
        if(exe[i][0] == '*'||exe[i][0] == '+')
            if(exe[i+1][0] == '+'||exe[i+1][0] == '*'||exe[i+1][0] == ')'||exe[i+1][0] == '!') return false;//加法和乘法后面只能是多项式名、左括号、定积分符号
        if(exe[i][0] == '$')
            if(exe[i+1][0] =='+'||exe[i+1][0]=='*'||exe[i+1][0]==')'||exe[i+1][0]=='!'||exe[i+1][0]=='$') return false;//定积分符号后只能接区间+左括号/多项式名
        if(exe[i][0] == '!')
            if(!Is_Operator(exe[i+1][0])||exe[i+1][0]=='('||exe[i+1][0]=='!'||exe[i+1][0]=='$') return false;//求导符号后面只能为双目运算符、右括号
        if(exe[i][0] == '(')
            if(exe[i+1][0] == '+'||exe[i+1][0] == '*'||exe[i+1][0] == ')'||exe[i+1][0] == '!') return false; //左括号后面只能是左括号、定积分符号或多项式名
        if(exe[i][0] == ')')
            if(!Is_Operator(exe[i+1][0]) || exe[i+1][0] == '(' || exe[i+1][0] == '$') return false;  //右括号后面只能是右括号，双目运算符或求导符号
        if(!Is_Operator(exe[i][0]))
            if(!Is_Operator(exe[i+1][0]) || exe[i+1][0] == '(' || exe[i+1][0] == '$') return false;//多项式名后面只能是右括号，双目运算符或求导符号
    }
    return true;
}

int String_Split (string s, string exe[])
{
    int k = 0;
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == '(') exe[k] = "(";
        else if(s[i] == ')') exe[k] = ")";
        else if(s[i] == '*') exe[k] = "*";
        else if(s[i] == '+') exe[k] = "+";
        else if(s[i] == '!') exe[k] = "!";
        else if(s[i] == '$')
        {
            int m = 0;
            for(int j = i;j < s.size();j++)
                if(s[j]!=']')
                    m++;
                else break;
            exe[k].assign(s,i,m+1);
            i += m;
        }
        else
        {
            int m = 0;
            for(int j = i;j < s.size();j++)
                if(Is_Operator(s[j]) != true)
                    m++;
                else break;
            exe[k].assign(s,i,m);
            i += m - 1;
        }
        k++;
    }
    return k;

}

bool A_bigger_than_B(char A,char B)
{
    if(A == '!' && (B == '!'||B == '$'||B == '*'||B == '+'))
        return true;
    if(A == '$' && (B == '$'||B == '*'||B == '+'))
        return true;
    if(A == '*' && (B == '*'||B == '+'))
        return true;
    if(A == '+' && (B == '+'))
        return true;
    return false;
}

Poly* Transform_And_Calculate(string exe[], int k)
{
    stack <string> polys;
    stack <string> opers;
    string temp;
    for( int i = 0;i < k ;i++)
    {
        if(!Is_Operator(exe[i][0])) polys.push(exe[i]);
        else if(Is_Operator(exe[i][0]))
        {
            if(opers.empty()) opers.push(exe[i]);
            else if(exe[i][0] == '(') opers.push(exe[i]);//左括号直接入栈
            else if(exe[i][0] == ')')
            {
                temp = opers.top();
                while(temp[0] != '(')
                {
                    opers.pop();//弹出操作符
                    polys.push(temp);//放入多项式栈
                    temp = opers.top();
                    }
                opers.pop();//弹出左括号
            }//碰到右括号，弹出操作符栈中的操作符，直到遇到左括号
            else
            {
                string temp = opers.top();
                while(A_bigger_than_B(temp[0],exe[i][0]) && temp[i] != '(')
                {
                    opers.pop();//弹出操作符
                    polys.push(temp);//放入多项式栈
                    if(!opers.empty())  temp = opers.top();
                    else break;
                }
                opers.push(exe[i]);
            }//对于其它操作符,逐个弹出操作符栈中元素,直到碰到比它优先级低的或'('
        }
    }
     while(!opers.empty())//如果存放完后,操作符栈不为空
    {
        temp = opers.top();
        opers.pop();//弹出操作符
        polys.push(temp);//放入多项式栈
    }
    stack <string> ss;
    while(!polys.empty())
    {
        temp = polys.top();
        polys.pop();
        ss.push(temp);//放入后缀表达式栈
    }//将栈中元素反向
    stack <Poly*> calculate;
    Poly *p = NULL, *q = NULL;
    while(!ss.empty())
    {
        temp = ss.top();
        if(!Is_Operator(temp[0]))
        {
            p = Search_Poly(temp);
            calculate.push(p);
        }
        else if(temp[0] == '!')
        {
            p = calculate.top();
            calculate.pop();
            p = Der_Poly(p);
            calculate.push(p);
        }
        else if(temp[0] == '$')
        {
            p = calculate.top();
            calculate.pop();
            p = Int_Poly(p,temp);
            calculate.push(p);
        }
        else if(temp[0] == '*')
        {
            p = calculate.top();
            calculate.pop();
            q = calculate.top();
            calculate.pop();
            p = Mul_Poly(p, q);
            calculate.push(p);
        }
        else if(temp[0] == '+')
        {
            p = calculate.top();
            calculate.pop();
            q = calculate.top();
            calculate.pop();
            p = Add_Poly(p, q);
            calculate.push(p);
        }
        ss.pop();
    }
    return calculate.top();
}
