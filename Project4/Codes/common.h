#ifndef ZMZM_COMMON
#define ZMZM_COMMON

#include <cmath>
#include <stack>
#include <string>
#include <vector>
#include <cstdio>
#include <sstream>
#include <iostream>
using namespace std;

struct Poly
{
    int n;//多项式该项的次数
    double coe;//多项式该项的系数
    string name;//多项式的名字
    Poly* next;
};

void Title();//标题打印函数
void Print_Poly(Poly* poly);//根据头节点输出该多项式
void Delete_Poly(Poly* poly);//删除链表
Poly* Copy_Poly(Poly *poly);//复制多项式,返回链表头节点
Poly* Modify_Poly(Poly *head);//修剪多项式，去掉系数为0节点
Poly* Search_Poly(string name);//vector中根据名字查询多项式,返回链表头节点
double Calculate_Poly(double n,Poly *poly);//计算多项式的值


const double EPS = 1e-6;

#endif
