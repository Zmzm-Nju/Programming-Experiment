#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
extern bool END;

//����Ϊ�洢���ݵ���ؽṹ��

//�洢�γ������Ϣ�Ľṹ��
struct Course
{
	char course_id[4];//�γ̵�ID
	char course_name[30];//�γ���
	char teacher_name[20];//�ڿν�ʦ
	int all; //�γ̿���������
	int now; //�γ���ѡ����
	int category; //�γ����, 1��ʾרҵ��, 0��ʾ��רҵ��
	Course* next;
};
//�洢�˺������Ϣ�Ľṹ��
struct Account
{
	char ID[20]; //�˺�ID
	char Password[20]; //�˺�����
	Account* next;
};
//�洢����ID�Ľṹ��
struct Assistant
{
	char name[20];//��������
	Assistant* next;
};
//�洢ѧ��ѡ�������Ϣ�Ľṹ��
struct Student_Class
{
	char course_id[4]; //ѧ����ѡ�γ̵ı��
	char assistant_ID[20]; //ѧ����ѡ���̵�ID����������ΪNull
	Student_Class* next;
};
//�洢�γ����������Ϣ�Ľṹ��
struct Assistant_Class
{
	char course_id[4]; //���ſγ̵ı��
	char assistant_name[200]; //һ�����ַ������������������̵�ID���ö��Ÿ���
	Assistant_Class* next;
};

