#pragma once
#include"Struct.h"
extern bool END;

//����Ϊ����Ա����������

//����Ա��½
int  Login_In_Admin();

//main�����п��ƹ���Ա����ز���
bool Admin(int k);

//����Ա�˳���¼
bool Exit_Landing_Admin();

//����Ա����γ���Ϣ
bool Set_Up_Current_Course();

//����Ա��ӿγ�
bool Add_Course();

//����Ա�޸Ŀγ���Ϣ
bool Modify_Course();

//����Աɾ���γ�
bool Delete_Course();

//�鿴�γ̾�����Ϣ
bool View_Course();

//����Ա����ѧ������
bool Renew_Student_Password();

//����Ա�˳�ϵͳ
bool Exit_System_Admin();

//��ȡ��ӿγ̵Ŀγ̱��,str1Ϊ�¿γ̱�ţ�str2Ϊԭ�����һ���γ̱��
void Str_Plus(char* str1, char* str2);
