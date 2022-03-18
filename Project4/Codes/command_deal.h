#ifndef ZMZM_COMMAND_DEAL
#define ZMZM_COMMAND_DEAL

bool Expression_Legal(string s,string exe[],int k);//判断表达式的合法性
bool Is_Operator(char ch);//判断某个字符串是否是运算符
bool A_bigger_than_B(char A,char B);//比较A和B优先级的大小
int  String_Split (string s, string exe[]);//混合多项式拆分，返回所得string个数
Poly* Transform_And_Calculate(string exe[], int k);//转化后缀表达式并计算
 
#endif
