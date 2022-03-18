#ifndef ZMZM_CALCULATE
#define ZMZM_CALCULATE

Poly* Der_Poly(Poly *A);//多项式求导
Poly* Add_Poly(Poly *A,Poly *B);//多项式加法
Poly* Mul_Poly(Poly *A,Poly *B);//多项式乘法
Poly* Int_Poly(Poly *A,string Interval);//多项式定积分，为了与其他多项式运算保持一致，结果储存在单节点链表中
double String_to_double(string number);//数字转换，从string到double

#endif
