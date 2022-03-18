#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
extern bool END;

//以下为存储数据的相关结构：

//存储课程相关信息的结构体
struct Course
{
	char course_id[4];//课程的ID
	char course_name[30];//课程名
	char teacher_name[20];//授课教师
	int all; //课程可容纳人数
	int now; //课程已选人数
	int category; //课程类别, 1表示专业课, 0表示非专业课
	Course* next;
};
//存储账号相关信息的结构体
struct Account
{
	char ID[20]; //账号ID
	char Password[20]; //账号密码
	Account* next;
};
//存储助教ID的结构体
struct Assistant
{
	char name[20];//助教名字
	Assistant* next;
};
//存储学生选课相关信息的结构体
struct Student_Class
{
	char course_id[4]; //学生所选课程的编号
	char assistant_ID[20]; //学生所选助教的ID，无助教则为Null
	Student_Class* next;
};
//存储课程助教相关信息的结构体
struct Assistant_Class
{
	char course_id[4]; //该门课程的编号
	char assistant_name[200]; //一个大字符串，储存了所有助教的ID，用逗号隔开
	Assistant_Class* next;
};

