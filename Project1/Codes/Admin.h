#pragma once
#include"Struct.h"
extern bool END;

//以下为管理员操作函数：

//管理员登陆
int  Login_In_Admin();

//main函数中控制管理员的相关操作
bool Admin(int k);

//管理员退出登录
bool Exit_Landing_Admin();

//管理员导入课程信息
bool Set_Up_Current_Course();

//管理员添加课程
bool Add_Course();

//管理员修改课程信息
bool Modify_Course();

//管理员删除课程
bool Delete_Course();

//查看课程具体信息
bool View_Course();

//管理员重置学生密码
bool Renew_Student_Password();

//管理员退出系统
bool Exit_System_Admin();

//获取添加课程的课程编号,str1为新课程编号，str2为原来最后一个课程编号
void Str_Plus(char* str1, char* str2);
