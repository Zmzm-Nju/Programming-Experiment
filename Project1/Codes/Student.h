#pragma once
#include"Struct.h"
extern bool END;

//以下为学生操作函数：

//学生注册账号
void Student_Register();

//学生登陆账号
int  Login_In_Student(char* id);

//在main函数中，通过k控制学生的相关操作，并传递学生id
bool Student(int k, char* id);

//学生退出登录
bool Exit_Landing_Stu(char* id);

//学生选课
bool Choose_Course(char* id);

//学生打印个人课表
bool Print_Stu_Course(char* id);

//学生退课
bool Drop_Course(char* id);

//学生举手报名助教
bool Become_Assistant(char* id);

//学生选择个人助教
bool Choose_Assistant(char* id);

//学生修改密码
bool Change_Password(char* id);

//学生退出系统
bool Exit_System_Stu(char* id);

//查询该学生已经是几门课的助教
int  Number_Assistant_Course(char* id);

//判断某学生(id)是否为某门课(course_id)助教
bool Search_Assistant(char* id, char* course_id);

//删除某门课(course_id)的某个助教(id)
void Delete_Assistant(char* id, char* course_id);

//为某门课(course_id)添加某个助教(id)
void Add_Assistant(char* id, char* course_id);

//将某门课的助教名单存入链表中，name为大字符串，储存了所有助教的id，用逗号隔开
Assistant* Divide_Assistant(char* name);

//检查某学生的助教是否退课
void Check_Assistant(char*);

//根据学生课表(head),对学生选课情况进行提醒
void Warning(Student_Class* head);