#pragma once
#include"Struct.h"
extern bool END;

//����Ϊѧ������������

//ѧ��ע���˺�
void Student_Register();

//ѧ����½�˺�
int  Login_In_Student(char* id);

//��main�����У�ͨ��k����ѧ������ز�����������ѧ��id
bool Student(int k, char* id);

//ѧ���˳���¼
bool Exit_Landing_Stu(char* id);

//ѧ��ѡ��
bool Choose_Course(char* id);

//ѧ����ӡ���˿α�
bool Print_Stu_Course(char* id);

//ѧ���˿�
bool Drop_Course(char* id);

//ѧ�����ֱ�������
bool Become_Assistant(char* id);

//ѧ��ѡ���������
bool Choose_Assistant(char* id);

//ѧ���޸�����
bool Change_Password(char* id);

//ѧ���˳�ϵͳ
bool Exit_System_Stu(char* id);

//��ѯ��ѧ���Ѿ��Ǽ��ſε�����
int  Number_Assistant_Course(char* id);

//�ж�ĳѧ��(id)�Ƿ�Ϊĳ�ſ�(course_id)����
bool Search_Assistant(char* id, char* course_id);

//ɾ��ĳ�ſ�(course_id)��ĳ������(id)
void Delete_Assistant(char* id, char* course_id);

//Ϊĳ�ſ�(course_id)���ĳ������(id)
void Add_Assistant(char* id, char* course_id);

//��ĳ�ſε������������������У�nameΪ���ַ������������������̵�id���ö��Ÿ���
Assistant* Divide_Assistant(char* name);

//���ĳѧ���������Ƿ��˿�
void Check_Assistant(char*);

//����ѧ���α�(head),��ѧ��ѡ�������������
void Warning(Student_Class* head);