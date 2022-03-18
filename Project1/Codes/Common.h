#pragma once
#include"Struct.h"
extern bool END;

//����Ϊ�ļ���ȡ������

//���ı��ļ��ж�ȡ�γ�����, �β�fileΪ�ļ���
Course* Read_Course(const char* file);
//���ı��ļ��ж�ȡ�˺�����, �ļ���Ϊ"student.txt"
Account* Read_Account();
//���ı��ļ��ж�ȡѧ��ѡ������, �β�fileΪѧ�������ļ���
Student_Class* Read_Student_Class(char* file);
//���ı��ļ��ж�ȡ��������, �ļ���Ϊ"assistant.txt"
Assistant_Class* Read_Assistant_Class();


//����Ϊ�ļ�д�뺯����

//���γ�����д���ı��ļ�, headΪ����ͷ�ڵ㣬fileΪ�ļ���
void Write_Course(Course* head, const char* file);
//��ѧ��ѡ������д��ѧ�������ļ���headΪ����ͷ�ڵ㣬fileΪѧ�������ļ���
void Write_Student(Student_Class* head, const char* file);
//���˺�����д���ı��ļ���headΪ����ͷ�ڵ㣬�ļ���Ϊ"student.txt"
void Write_Account(Account* head);
//����������д���ı��ļ���headΪ����ͷ�ڵ㣬�ļ���Ϊ"assistant.txt"
void Write_Assistant(Assistant_Class* head);


//����Ϊ�����ӡ������

//�����ҳ�����
void Title_All();
//�������Ա�������
void Title_Admin();
//���ѧ���������
void Title_Student();
//�������֮��ָ���
void Title_Gap();


//����Ϊ����Ա��ѧ��������ͬ��Ҫ�õ��ĺ���

//ѧ�������Ա�鿴ȫ���γ���Ϣ
bool Print_Current_Course();
//��ѧ���α�(head)�а��γ�����γ�ID(number)����ĳ�γ̣����ʵ���ǿγ����Ļ����޸�Ϊ���Ӧ���
bool Search(Student_Class* head, char* number);
//��������ļ��ܺ���
void Secretword(char* key);
//ѧ�������Ա�鿴ȫ���γ�������Ϣ
bool Print_Current_Assistant();