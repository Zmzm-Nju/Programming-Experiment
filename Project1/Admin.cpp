#include"Admin.h"
#include"Common.h"
//以下为管理员操作函数：

int  Login_In_Admin()
{
	printf("\n\n");
	Title_Gap();
	printf("请输入您的管理员账号(输入'E'返回上一级页面）：");
	char account[20];
	scanf("%s", account);
	while (strcmp("Admin", account))
	{
		if (account[0] == 'E' && account[1] == '\0')
		{
			printf("\n********取消管理员登陆成功！返回上一界面！********\n");
			return 0;
		}
		printf("\n账号错误，请重新输入您的账号(输入'E'返回上一级页面)：");
		scanf("%s", account);
	}
	printf("\n请输入您的密码(共有3次输入机会)：");
	char password[20];
	for (int i = 0; i < 3; i++)
	{
		Secretword(password);
		if (!strcmp("admin", password))
		{
			printf("\n********登陆成功！欢迎使用选课管理系统！********\n");
			Title_Gap();
			return 1;
		}
		else if (i != 2)
			printf("\n请输入您的密码(还有%d次输入机会)：", 2 - i);
		else
			printf("\n********管理员登陆失败！返回上一级页面！********\n");
	}
	return 0;
}
bool Admin(int k)
{
	switch (k)
	{
	case 1:return Exit_Landing_Admin(); break;
	case 2:return Set_Up_Current_Course(); break;
	case 3:return Print_Current_Course(); break;
	case 4:return Add_Course(); break;
	case 5:return Delete_Course(); break;
	case 6:return Modify_Course(); break;
	case 7:return View_Course(); break;
	case 8:return Print_Current_Assistant(); break;
	case 9:return Renew_Student_Password(); break;
	case 10:return Exit_System_Admin(); break;
	}
	return false;
}
bool Exit_Landing_Admin()
{
	printf("\n是否确定要退出登录？输入1确认，否则默认为取消退出(仅支持输入数字)：");
	int m = 0;
	scanf_s("%d", &m);
	if (m == 1)
	{
		printf("\n********退出登录成功！返回系统主页面！********\n");
		return true;
	}
	else
	{
		printf("\n********取消退出登录成功！返回上一级页面！********\n");
		return false;
	}
}
bool Set_Up_Current_Course()
{
	FILE* file = fopen("current_course.txt", "r");
	if (file == NULL)
	{
		Course* Head_Course = Read_Course("defaultcourse.txt");
		if (Head_Course == NULL)
			printf("\n********资源文件(defaultcourse.txt)不存在！请检查是否出错！********\n");
		if (Head_Course != NULL)
		{
			Write_Course(Head_Course, "current_course.txt");
			printf("\n********课程信息录入成功！********\n");
		}
	}
	else
	{
		printf("\n********课程信息已录入，无需重复录入!********\n");
		fclose(file);
	}
	return false;
}
bool Add_Course()
{
	Course* head = Read_Course("current_course.txt");
	if (head == NULL)
		printf("\n********尚未导入课程！无法查看课程信息！********\n");
	else if (head != NULL)
	{
		printf("\n请依次输入需要添加的课程信息：\n");
		Course* p = (Course*)malloc(sizeof(Course));
		printf("1.课程名称(输入'E'返回上一级界面)：");
		char Name[30];
		scanf("%s", Name);
		if (Name[0] == 'E' && Name[1] == '\0')
		{
			printf("\n********取消添加课程成功！返回上一界面！********\n");
			return false;
		}
		strcpy(p->course_name, Name);
		printf("2.授课教师：");
		scanf("%s", p->teacher_name);
		printf("3.容纳人数：");
		scanf("%d", &p->all);
		printf("4.已选人数：");
		scanf("%d", &p->now);
		char category[30];
		printf("5.课程类别：");
		scanf("%s", category);
		if (!strcmp("专业课", category))
			p->category = 1;
		else p->category = 0;
		//printf("%s\t%s\t%d\t%d\t%d\n",p->course_name, p->teacher_name, p->all, p->now, p->category);
		Course* cur = head;
		while (cur != NULL)//遍历链表，检查是否有相同课程
		{
			if (!strcmp(p->course_name, cur->course_name) && !strcmp(p->teacher_name, cur->teacher_name))
			{
				printf("\n********已有此课程！添加失败！********\n");
				return false;
			}
			cur = cur->next;
		}
		p->next = NULL;
		cur = head;
		while (cur->next)
			cur = cur->next;
		Str_Plus(p->course_id, cur->course_id);
		cur->next = p;
		Write_Course(head, "current_course.txt");
		printf("\n********添加成功！********\n");
		Print_Current_Course();
	}
	return false;
}
bool Modify_Course()
{
	Course* head = Read_Course("current_course.txt");
	if (head == NULL)
		printf("\n********尚未导入课程！无法修改课程信息！********\n");
	else if (head != NULL)
	{
		printf("\n请输入需要修改信息课程的ID(输入'E'返回上一级界面)：");
		char Back[4];
		scanf("%s", Back);
		if (Back[0] == 'E' && Back[1] == '\0')
		{
			printf("\n********取消修改课程信息成功！返回上一界面！********\n");
			return false;
		}
		bool find = false;
		Course* b = head;
		while (b)
		{
			if (!strcmp(b->course_id, Back))
			{
				find = true; break;
			}//如果找到该课程，退出时b刚好指向该课程对应节点
			b = b->next;
		}
		if (!find)
			printf("\n********无此课程！修改课程信息失败！********\n");
		else
		{
			printf("\n请选择需要修改的具体信息：(1.任课教师  2.容纳人数)");
			int n = 0;
			scanf("%d", &n);
			while (n > 2 || n <= 0)
			{
				printf("\n此输入无效！请输入有效的功能编号(1-2以内数字,请勿输入数字以外符号)：");
				scanf_s("%d", &n);
			}//循环获得有效输入，此时n必为1-2之间某一数字
			if (n == 1)
			{
				printf("\n具体修改为：");
				char teacher[30];
				scanf("%s", teacher);
				if (!strcmp(teacher, b->teacher_name))
					printf("\n********修改失败!任课老师已经为该老师！********\n");
				else
				{
					strcpy(b->teacher_name, teacher);
					Write_Course(head, "current_course.txt");
					printf("\n********修改成功！********\n");
					Print_Current_Course();
				}
			}
			if (n == 2)
			{
				printf("\n具体修改为：");
				int k = 0;
				scanf_s("%d", &k);
				if (k < b->now)
					printf("\n********修改失败!修改后容纳人数小于已选人数！********\n");
				else
				{
					b->all = k;
					Write_Course(head, "current_course.txt");
					printf("\n********修改成功！********\n");
					Print_Current_Course();
				}
			}
		}
	}
	return false;
}
bool Delete_Course()
{
	Course* head = Read_Course("current_course.txt");
	if (head == NULL)
		printf("\n********尚未导入课程！无法删除课程！********\n");
	else if (head != NULL)
	{
		printf("\n请输入需要删除课程的ID(输入'E'返回上一级界面)：");
		char ID[10];
		scanf("%s", ID);
		if (ID[0] == 'E' && ID[1] == '\0')
		{
			printf("\n********取消删除课程成功！返回上一界面！********\n");
			return false;
		}
		if (!strcmp(ID, head->course_id))//头节点单独搬出来处理
		{
			if (head->now != 0)
				printf("\n********已有学生选择此课程！删除课程失败！********\n");
			else 
			{
				Course* cur = head;
				Write_Course(head->next, "current_course.txt");
				printf("\n********删除成功！********\n");
				Print_Current_Course();
				free(cur);
			}
		}
		else
		{
			bool find = false;
			Course* pre = NULL, * cur = head;
			while (cur)
			{
				if (!strcmp(cur->course_id, ID))
				{
					find = true; break;
				}//如果找到该课程，退出时cur刚好指向该课程对应节点
				pre = cur;
				cur = cur->next;
			}
			if (!find)
				printf("\n********无此课程！删除课程失败！********\n");
			else
			{
				if (cur->now != 0)
					printf("\n********已有学生选择此课程！删除课程失败！********\n");
				else
				{
					pre->next = cur->next;
					free(cur);
					Write_Course(head, "current_course.txt");
					printf("\n********删除课程成功！********\n");
					Print_Current_Course();
				}
			}
		}
	}
	return false;
}
bool View_Course()
{
	Course* head = Read_Course("current_course.txt");
	if (head == NULL)
		printf("\n********尚未导入课程！无法查看课程！********\n");
	else if (head != NULL)
	{
		printf("\n请输入需要查看的课程的ID(输入'E'返回上一级界面)：");
		char ID[4];
		scanf("%s", ID);
		if (ID[0] == 'E' && ID[1] == '\0')
		{
			printf("\n********取消查看课程信息成功！返回上一界面！********\n");
			return false;
		}
		bool find = false;
		while (!find)
		{
			Course* cur = head;
			while (cur)
			{
				if (!strcmp(cur->course_id, ID))
				{
					find = true; break;
				}//如果找到该课程，退出时cur刚好指向该课程对应节点
				cur = cur->next;
			}
			if (!find)
			{
				printf("\n无此课程！查看课程失败！请重新输入课程ID:");
				scanf("%s", ID);
			}
			else if (find)
			{
				printf("\n");
				Title_Gap();
				printf(" %s\t%s\t%s\t%d\t%d\t", cur->course_id, cur->course_name, cur->teacher_name, cur->all, cur->now);
				if (cur->category)
					printf(" 专业课\n");
				else printf(" 非专业课\n");
				Title_Gap();
				printf("\n还希望进行以下哪项操作:1.查看选课学生名单  2.查看课程报名助教名单\n");
				printf("请输入操作编号：");
				int a = 0;
				scanf_s("%d", &a);
				if (a == 1)
				{
					Account* m = Read_Account();//读取所有账户
					if (m == NULL)
					{
						FILE* fp = fopen("student.txt", "w+");
						fclose(fp);
						printf("\n********查看失败！暂无学生选课！********\n");
					}//返回NULL则新建一个文件
					int k = 0;
					Title_Gap();
					printf("选择该课程的学生有：\n");
					while (m)
					{
						char file[25] = { '\0' };
						strcpy(file, m->ID);
						strcat(file, ".txt");
						Student_Class* n = Read_Student_Class(file);
						if (Search(n, ID))
						{
							printf("%s ", m->ID);
							k++;
						}
						if (k == 5)
						{
							printf("\n");
							k = 0;
						}//控制一行输出五个
						m = m->next;
					}
					printf("\n");
					printf("选择该门课的同学共有%d人,距离满课还差%d人。\n", cur->now, cur->all-cur->now);
					Title_Gap();
				}
				else if (a == 2)
				{
					Assistant_Class* head = Read_Assistant_Class();
					if (head == NULL)
					{
						FILE* fp = fopen("assistant.txt", "w+");
						fclose(fp);
						printf("\n********查看失败！该课程暂无助教！********\n");
					}//返回NULL则新建一个文件
					else
					{
						Assistant_Class* b = head;
						while (b)
						{
							if (!strcmp(b->course_id, ID))
							{
								printf("\n该门课的助教有：%s\n", b->assistant_name);
								break;
							}//如果找到该课程，退出时b刚好指向该课程对应节点
							b = b->next;
						}
						if (b == NULL)//到最后也没找到这门课
							printf("\n********查看失败！该课程暂无助教！********\n");
					}
				}
			}
		}
	}
	return false;
}
bool Renew_Student_Password()
{
	Account* head = Read_Account();
	printf("\n请输入需要重置密码的学生的ID(输入'E'返回上一级):");
	char ID[20];
	scanf("%s", ID);
	if (ID[0] == 'E' && ID[1] == '\0')
	{
		printf("\n********取消重置学生密码成功！返回上一界面！********\n");
		return false;
	}
	bool find = false;
	while (!find)
	{
		Account* cur = head;
		while (cur)
		{
			if (!strcmp(cur->ID, ID))
			{
				find = true; break;
			}//如果找到该学生，退出时cur刚好指向该学生对应节点
			cur = cur->next;
		}
		if (!find)
		{
			printf("\n无此学生！无法重置学生密码！请重新输入学生ID(输入'E'返回上一级):");
			scanf("%s", ID);
			if (ID[0] == 'E' && ID[1] == '\0')
			{
				printf("\n********取消重置学生密码成功！返回上一界面！********\n");
				return false;
			}
		}
		else if (find)
		{
			printf("\n是否确认要重置该学生密码？输入1确认，否则默认为取消，返回上一级页面(仅支持输入数字)：");
			int m = 0;
			scanf_s("%d", &m);
			if (m == 1)
			{
				strcpy(cur->Password, "NJUCS2020");
				printf("\n********重置学生密码成功！********\n");
			}
			else
				printf("\n********取消重置学生密码成功！返回上一级页面！********\n");
		}
	}
	Write_Account(head);
	return false;
}
bool Exit_System_Admin()
{
	printf("\n是否确定要退出系统？输入1确认，否则默认为取消退出(仅支持输入数字)：");
	int m = 0;
	scanf_s("%d", &m);
	if (m == 1)
	{
		END = true;
		return true;
	}
	else
	{
		printf("\n********取消退出系统成功！返回上一级页面！********\n");
		return false;
	}
}
void Str_Plus(char* str1, char* str2)
{
	str1[3] = '\0';
	//考虑进位的情况，既然只有三位不妨直接分情况讨论
	if (str2[2] == '9' && str2[1] == '9')
	{
		str1[0] = str2[0] + 1;
		str1[1] = '0';
		str1[2] = '0';
	}
	else if (str2[2] == '9')
	{
		str1[0] = str2[0];
		str1[1] = str2[1] + 1;
		str1[2] = '0';
	}
	else
	{
		str1[0] = str2[0];
		str1[1] = str2[1];
		str1[2] = str2[2] + 1;
	}
}