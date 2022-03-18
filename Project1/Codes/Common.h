#pragma once
#include"Struct.h"
extern bool END;

//以下为文件读取函数：

//从文本文件中读取课程数据, 形参file为文件名
Course* Read_Course(const char* file);
//从文本文件中读取账号数据, 文件名为"student.txt"
Account* Read_Account();
//从文本文件中读取学生选课数据, 形参file为学生个人文件名
Student_Class* Read_Student_Class(char* file);
//从文本文件中读取助教数据, 文件名为"assistant.txt"
Assistant_Class* Read_Assistant_Class();


//以下为文件写入函数：

//将课程数据写入文本文件, head为链表头节点，file为文件名
void Write_Course(Course* head, const char* file);
//将学生选课数据写入学生个人文件，head为链表头节点，file为学生个人文件名
void Write_Student(Student_Class* head, const char* file);
//将账号数据写入文本文件，head为链表头节点，文件名为"student.txt"
void Write_Account(Account* head);
//将助教数据写入文本文件，head为链表头节点，文件名为"assistant.txt"
void Write_Assistant(Assistant_Class* head);


//以下为标题打印函数：

//输出主页面标题
void Title_All();
//输出管理员界面标题
void Title_Admin();
//输出学生界面标题
void Title_Student();
//输出标题之间分隔符
void Title_Gap();


//以下为管理员和学生操作共同需要用到的函数

//学生或管理员查看全部课程信息
bool Print_Current_Course();
//在学生课表(head)中按课程名或课程ID(number)查找某课程，如果实参是课程名的话，修改为其对应编号
bool Search(Student_Class* head, char* number);
//密码输入的加密函数
void Secretword(char* key);
//学生或管理员查看全部课程助教信息
bool Print_Current_Assistant();