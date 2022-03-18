#include"Common.h"
#include"Student.h"
//以下为学生操作函数：
void Student_Register()
{
	Account* head = Read_Account(), * cur = head;
	char ID[20], password1[20], password2[20];
	printf("\n********欢迎注册学生选课系统！********\n");
	printf("\n请输入您的ID：(不超过20个字符，由数字和小写字母构成，输入'E'返回上一级界面)：");
	scanf("%s", ID);
	if (ID[0] == 'E' && ID[1] == '\0')
	{
		printf("\n********取消注册账号成功！返回上一界面！********\n");
		return;
	}
	if (cur == NULL)
	{
		bool same = false;
		while (!same)
		{
			printf("\n请输入您的密码(不超过20个字符，由数字和小写字母构成，输入'E'返回上一级界面)：");
			Secretword(password1);
			if (password1[0] == 'E' && password1[1] == '\0')
			{
				printf("\n********取消注册账号成功！返回上一界面！********\n");
				return;
			}
			printf("\n确认密码：");
			Secretword(password2);
			if (!strcmp(password1, password2))
			{
				Account* p = (Account*)malloc(sizeof(Account));
				strcpy(p->ID, ID);
				strcpy(p->Password, password1);
				p->next = NULL;
				head = p;
				Write_Account(head);
				same = true;
			}
			else
				printf("\n********两次密码输入不一致！请重新输入！********\n\n");
		}
	}
	else
	{
		while (cur)
		{
			if (!strcmp(cur->ID, ID))
			{
				printf("\n该ID已存在！请重新输入您的ID：(输入'E'返回上一级界面)：");
				scanf("%s", ID);
				if (ID[0] == 'E' && ID[1] == '\0')
				{
					printf("\n********取消注册账号成功！返回上一界面！********\n");
					return ;
				}
				cur = head; continue;
			}
			cur = cur->next;
		}
		bool same = false;
		while (!same)
		{
			printf("\n请输入您的密码(不超过20个字符，由数字和小写字母构成，输入'E'返回上一级界面)：");
			Secretword(password1);
			if (password1[0] == 'E' && password1[1] == '\0')
			{
				printf("\n********取消注册账号成功！返回上一界面！********\n");
				return;
			}
			printf("\n确认密码：");
			Secretword(password2);
			if (!strcmp(password1, password2))
			{
				Account* p = (Account*)malloc(sizeof(Account));
				strcpy(p->ID, ID);
				strcpy(p->Password, password1);
				p->next = NULL;
				cur = head;
				while (cur->next)
					cur = cur->next;
				cur->next = p;
				Write_Account(head);
				same = true;
			}
			else
				printf("\n********两次密码输入不一致！请重新输入！\n\n");
		}
	}
	char file[25];
	strcpy(file, ID);
	strcat(file, ".txt");
	FILE* fp = fopen(file, "w+");
	if (fp == NULL)
		printf("\n********出现异常错误！请向技术人员寻求帮助！********\n");
	else
	{
		fclose(fp);
		printf("\n********注册成功！欢迎使用本系统！********\n");
		printf("\n请记住您的账号和密码，若忘记密码，可找管理员重置！\n");
	}
}
int  Login_In_Student(char* id)
{
	Account* head = Read_Account(), * cur = head;
	if (head == NULL)
	{
		printf("\n********尚未注册账号，先注册再登陆！********\n");
		FILE* file = fopen("student.txt", "w+");
		fclose(file);
		return false;
	}
	printf("\n\n");
	Title_Gap();
	printf("请输入您的学生账号(输入'E'返回上一级页面）：");
	char ID[20], password[20];
	scanf("%s", ID);
	bool find = false;
	while (!find)
	{
		if (ID[0] == 'E' && ID[1] == '\0')
		{
			printf("\n********取消登陆成功！返回上一界面！********\n");
			return 0;
		}
		Account* cur = head;
		while (cur)
		{
			if (!strcmp(cur->ID, ID))
			{
				strcpy(password, cur->Password);
				find = true; break;
			}
			cur = cur->next;
		}
		if (!find)
		{
			printf("\n此账号尚未注册，请重新输入您的账号(输入'E'返回上一级界面)：");
			scanf("%s", ID);
			if (ID[0] == 'E' && ID[1] == '\0')
			{
				printf("\n********取消登陆成功！返回上一界面！********\n");
				return 0;
			}

		}
	}
	printf("\n请输入您的密码(共有3次输入机会)：");
	char password_In[20];
	for (int i = 0; i < 3; i++)
	{
		Secretword(password_In);
		if (!strcmp(password_In, password))
		{
			printf("\n\n********登陆成功！欢迎使用选课管理系统！********\n");
			Title_Gap();
			Check_Assistant(ID);
			strcpy(id, ID);
			return 1;
		}
		else if (i != 2)
			printf("\n密码错误！请重新输入您的密码(还有%d次输入机会)：", 2 - i);
		else
			printf("\n********登陆失败！返回上一级页面！\n");
	}
	return 0;
}
bool Student(int k, char* id)
{
	switch (k)
	{
	case 1:return Exit_Landing_Stu(id); break;
	case 2:return Print_Current_Course(); break;
	case 3:return Choose_Course(id); break;
	case 4:return Print_Stu_Course(id); break;
	case 5:return Drop_Course(id); break;
	case 6:return Print_Current_Assistant(); break;
	case 7:return Become_Assistant(id); break;
	case 8:return Choose_Assistant(id); break;
	case 9:return Change_Password(id); break;
	case 10:return Exit_System_Stu(id); break;
	}
	return false;
}
bool Exit_Landing_Stu(char* id)
{
	char file[25];
	strcpy(file, id);
	strcat(file, ".txt");
	Student_Class* head_student = Read_Student_Class(file);
	printf("\n");
	Warning(head_student);
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
bool Choose_Course(char* id)
{
	char file[25];
	strcpy(file, id);
	strcat(file, ".txt");
	Course* head_course = Read_Course("current_course.txt");
	Student_Class* head_student = Read_Student_Class(file);
	if (head_course == NULL)
	{
		printf("\n********管理员尚未导入课程！无法选课！********\n");
		return false;
	}
	Student_Class* a = head_student;
	int z = 0;
	while (a)
	{
		z++;
		a = a->next;
	}
	if (z >= 10)
	{
		printf("\n********你已选择十门课程！无法继续选课！********\n");
		return false;
	}
	printf("\n请输入需要选择课程的ID：(输入'E'返回上一级界面)：");
	char ID[10];
	scanf("%s", ID);
	if (ID[0] == 'E' && ID[1] == '\0')
	{
		printf("\n********取消选课成功！返回上一界面！********\n");
		return false;
	}
	bool find = false;
	Course* cur = head_course;
	while (!find)
	{
		cur = head_course;
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
			printf("\n********无此课程！选课失败！********\n");
			printf("\n请重新输入需要选择课程的ID(输入'E'返回上一级界面)：");
			scanf("%s", ID);
			if (ID[0] == 'E' && ID[1] == '\0')
			{
				printf("\n********取消选课成功！返回上一界面！********\n");
				return false;
			}
		}
		else if (find && cur->all == cur->now)
		{
			printf("\n********该课程已满！选课失败！********\n");
			printf("\n请重新输入需要选择课程的ID(输入'E'返回上一级界面)：");
			scanf("%s", ID);
			if (ID[0] == 'E' && ID[1] == '\0')
			{
				printf("\n********取消选课成功！返回上一界面！********\n");
				return false;
			}
			find = false;
		}
		else if (Search(head_student, ID))
		{
			printf("\n********你已选择该课程！选课失败！********\n");
			printf("\n请重新输入需要选择课程的ID(输入'E'返回上一级界面)：");
			scanf("%s", ID);
			if (ID[0] == 'E' && ID[1] == '\0')
			{
				printf("\n********取消选课成功！返回上一界面！********\n");
				return false;
			}
			find = false;
		}
	}//出循环时,已经选定一门未满的课
	if (head_student == NULL)//该生还未选课，链表为空
	{
		Student_Class* p = (Student_Class*)malloc(sizeof(Student_Class));
		strcpy(p->course_id, cur->course_id);
		strcpy(p->assistant_ID, "Null");
		p->next = NULL;
		Write_Student(p, file);
	}
	else if (head_student != NULL)
	{
		Student_Class* p = (Student_Class*)malloc(sizeof(Student_Class));
		strcpy(p->course_id, cur->course_id);
		strcpy(p->assistant_ID, "Null");
		p->next = NULL;
		//选择恰当的地方插入p
		if (strcmp(p->course_id, head_student->course_id) < 0)
		{
			p->next = head_student;
			head_student = p;
		}//插入头节点单独处理
		else
		{
			Student_Class* a = head_student;
			while (a->next)
			{
				if (strcmp(p->course_id, a->next->course_id) > 0)
					a = a->next;
				else break;
			}
			p->next = a->next;
			a->next = p;
		}
		Write_Student(head_student, file);
	}
	cur = head_course;
	while (cur)
	{
		if (!strcmp(cur->course_id, ID))
			(cur->now)++;
		cur = cur->next;
	}
	Write_Course(head_course, "current_course.txt");
	printf("\n********选课成功！该课程已添加至个人课表！********\n");
	Print_Stu_Course(id);
	return false;
}
bool Print_Stu_Course(char* id)
{
	char file[25];
	strcpy(file, id);
	strcat(file, ".txt");
	Course* head_course = Read_Course("current_course.txt");
	Student_Class* head_student = Read_Student_Class(file);
	if (head_student == NULL)
	{
		printf("\n********您尚未选课！无法打印个人课表！********\n\n");
		Warning(head_student);
		return false;
	}
	printf("\n\n");
	Title_Gap();
	printf("课程ID\t 课程名称        \t授课教师   课程类型   个人助教\n");
	while (head_course)
	{
		if (Search(head_student, head_course->course_id))
		{
			if (strlen(head_course->course_name) <= 7)
			{
				printf(" %s\t%s                \t %s\t", head_course->course_id, head_course->course_name, head_course->teacher_name);
				if (head_course->category)
					printf("   专业课\t");
				else
					printf("   非专业课\t");
				Student_Class* cur = head_student;
				while (cur)
				{
					if (!strcmp(cur->course_id, head_course->course_id))
					{
						printf("%s\n", cur->assistant_ID);
						break;
					}
					cur = cur->next;
				}
			}//为了对齐美观，判断下课程名的长度,<=7则补16个空格
			else if (strlen(head_course->course_name) <= 15)
			{
				printf(" %s\t%s        \t %s\t", head_course->course_id, head_course->course_name, head_course->teacher_name);
				if (head_course->category)
					printf("   专业课\t");
				else
					printf("   非专业课\t");
				Student_Class* cur = head_student;
				while (cur)
				{
					if (!strcmp(cur->course_id, head_course->course_id))
					{
						printf("%s\n", cur->assistant_ID);
						break;
					}
					cur = cur->next;
				}
			}//为了对齐美观，判断下课程名的长度,<=15则补8个空格
			else
			{
				printf(" %s\t%s\t %s\t", head_course->course_id, head_course->course_name, head_course->teacher_name);
				if (head_course->category)
					printf("   专业课\t");
				else
					printf("   非专业课\t");
				Student_Class* cur = head_student;
				while (cur)
				{
					if (!strcmp(cur->course_id, head_course->course_id))
					{
						printf("%s\n", cur->assistant_ID);
						break;
					}
					cur = cur->next;
				}
			}
		}
		head_course = head_course->next;
	}
	Title_Gap();
	Warning(head_student);
	return false;
}
bool Drop_Course(char* id)
{
	char file[25];
	strcpy(file, id);
	strcat(file, ".txt");
	Course* head_course = Read_Course("current_course.txt");
	Student_Class* head_student = Read_Student_Class(file);
	if (head_student == NULL)
	{
		printf("\n********你尚未选课！无法退课！********\n");
		return false;
	}
	printf("\n请输入需要退出课程的课程名或者ID(输入'E'返回上一级界面)：");
	char number[30];
	scanf("%s", number);
	if (number[0] == 'E' && number[1] == '\0')
	{
		printf("\n********取消退课成功！返回上一界面！********\n");
		return false;
	}
	bool find = Search(head_student, number);
	while (!find)
	{
		printf("\n********你未选此课程！退课失败！********\n");
		printf("\n请重新输入需要退出课程的ID(输入'E'返回上一级界面)：");
		scanf("%s", number);
		if (number[0] == 'E' && number[1] == '\0')
		{
			printf("\n********取消退课成功！返回上一界面！********\n");
			return false;
		}
		find = Search(head_student, number);
	}//出循环时，已经找到需要退的课程，而且已修改为课程名
	if (!strcmp(head_student->course_id, number))
	{
		Student_Class* temp = head_student;
		head_student = head_student->next;
		free(temp);
		Write_Student(head_student, file);
		printf("\n********退课成功！********\n");
		Print_Stu_Course(id);
	}//头节点单独处理
	else
	{
		Student_Class* pre = head_student, * cur = head_student->next;
		while (cur)
		{
			if (!strcmp(cur->course_id, number))
			{
				pre->next = cur->next;
				free(cur);
				Write_Student(head_student, file);
				printf("\n********退课成功！********\n");
				Print_Stu_Course(id); break;
			}
			pre = cur;
			cur = cur->next;
		}
	}
	Course* pro = head_course;
	while (pro)
	{
		if (!strcmp(pro->course_id, number))
		{
			pro->now = pro->now - 1; break;
		}
		pro = pro->next;
	}
	Write_Course(head_course, "current_course.txt");
	if (Search_Assistant(id, number))
		Delete_Assistant(id, number);
	return false;
}
bool Become_Assistant(char* id)
{
	char file[25];
	strcpy(file, id);
	strcat(file, ".txt");
	Student_Class* head_student = Read_Student_Class(file);
	if (head_student == NULL)
	{
		printf("\n********你尚未选课！无法举手报名助教！********\n");
		return false;
	}
	if (Number_Assistant_Course(id) >= 2)
	{
		printf("\n********你已经是两门课的助教！无法再举手报名助教！********\n");
		return false;
	}
	printf("\n请输入需要举手报名助教课程的课程名或者ID(输入'E'返回上一级界面)：");
	char number[30];
	scanf("%s", number);
	if (number[0] == 'E' && number[1] == '\0')
	{
		printf("\n********取消举手报名助教成功！返回上一界面！********\n");
		return false;
	}
	bool find = Search(head_student, number);
	bool already = true;//最开始设为true，以进入循环判断
	while (!find || already)
	{
		if (!find)
		{
			printf("\n********你未选此课程！举手报名助教失败！********\n");
			printf("\n请重新输入需要举手报名助教课程的课程名或者ID(输入'E'返回上一级界面)：");
			scanf("%s", number);
			if (number[0] == 'E' && number[1] == '\0')
			{
				printf("\n********取消举手报名助教成功！返回上一界面！********\n");
				return false;
			}
			find = Search(head_student, number); continue;
		}
		if (find)
		{
			already = Search_Assistant(id, number);
			if (already)
			{
				printf("\n********你已经是此课程助教！举手报名助教失败！********\n");
				printf("\n请重新输入需要举手报名助教的课程名或者ID(输入'E'返回上一级界面)：");
				scanf("%s", number);
				if (number[0] == 'E' && number[1] == '\0')
				{
					printf("\n********取消举手报名助教成功！返回上一界面！********\n");
					return false;
				}
			}
			else break;
		}
	}//出循环时，已经找到报名助教的课程，而且已修改为课程名
	Add_Assistant(id, number);
	printf("\n********举手报名助教成功！********\n");
	return false;
}
bool Choose_Assistant(char* id)
{
	char file[25];
	strcpy(file, id);
	strcat(file, ".txt");
	Student_Class* head_student = Read_Student_Class(file), * cur = head_student;
	if (head_student == NULL)
	{
		printf("\n********你尚未选课！无法选择个人助教！********\n");
		return false;
	}
	Assistant_Class* pre = Read_Assistant_Class();
	if (pre == NULL)
	{
		printf("\n********尚无人举手报名助教！无法选择个人助教！********\n");
		FILE* fp = fopen("assistant.txt", "w+");
		fclose(fp);
		return false;
	}
	printf("\n请输入需要选择助教课程的课程名或者ID(输入'E'返回上一级界面)：");
	char number[30];
	scanf("%s", number);
	if (number[0] == 'E' && number[1] == '\0')
	{
		printf("\n********取消选择个人助教成功！返回上一界面！********\n");
		return false;
	}
	bool find = Search(head_student, number);
	bool have_assistant = true;//最开始设为true，以进入循环判断
	while (!find || have_assistant)
	{
		if (!find)
		{
			printf("\n********你未选此课程！选择个人助教失败！********\n");
			printf("\n请重新输入需要选择个人助教课程的课程名或者ID(输入'E'返回上一级界面)：");
			scanf("%s", number);
			if (number[0] == 'E' && number[1] == '\0')
			{
				printf("\n********取消选择个人助教成功！返回上一界面！********\n");
				return false;
			}
			find = Search(head_student, number); continue;
		}
		if (find)
		{
			cur = head_student;
			have_assistant = false;
			while (cur)
			{
				if (!strcmp(cur->course_id, number) && strcmp(cur->assistant_ID, "Null"))
				{
					have_assistant = true; break;
				}
				cur = cur->next;
			}
			if (have_assistant)
			{
				printf("\n********你此课程已经拥有助教！选择个人助教失败！********\n");
				printf("\n请重新输入需要选择个人助教课程的课程名或者ID(输入'E'返回上一级界面)：");
				scanf("%s", number);
				if (number[0] == 'E' && number[1] == '\0')
				{
					printf("\n********取消选择个人助教成功！返回上一界面！********\n");
					return false;
				}
				find = Search(head_student, number); continue;
			}
			else break;
		}
	}//出循环时，已经找到报名助教的课程，而且已修改为课程名
	while (pre)
	{
		if (!strcmp(pre->course_id, number))
			break;
		pre = pre->next;
	}//如果找到该课程，退出时pre刚好指向该课程对应节点，否则为NULL
	if (pre != NULL)
	{
		printf("\n该门课的助教有：%s\n", pre->assistant_name);
		printf("\n请输入你想选择助教的ID(输入'E'返回上一级界面)：");
		char Assistant_ID[20];
		scanf("%s", Assistant_ID);
		if (Assistant_ID[0] == 'E' && Assistant_ID[1] == '\0')
		{
			printf("\n********取消选择个人助教成功！返回上一界面！********\n");
			return false;
		}
		while (!strcmp(Assistant_ID, id) || !Search_Assistant(Assistant_ID, number))
		{
			if (!strcmp(Assistant_ID, id))
			{
				printf("\n********不能选择自己当自己的助教！********\n");
				printf("\n该门课的助教有：%s\n", pre->assistant_name);
				printf("\n请输入你想选择助教的ID(输入'E'返回上一级界面)：");
				scanf("%s", Assistant_ID);
				if (Assistant_ID[0] == 'E' && Assistant_ID[1] == '\0')
				{
					printf("\n********取消选择个人助教成功！返回上一界面！********\n");
					return false;
				} 
				continue;
			}
			if (!Search_Assistant(Assistant_ID, number))
			{
				printf("\n********输入ID有误！此人不是本课程助教！********\n");
				printf("\n该门课的助教有：%s\n", pre->assistant_name);
				printf("\n请输入你想选择助教的ID(输入'E'返回上一级界面)：");
				scanf("%s", Assistant_ID);
				if (Assistant_ID[0] == 'E' && Assistant_ID[1] == '\0')
				{
					printf("\n********取消选择个人助教成功！返回上一界面！********\n");
					return false;
				} 
				continue;
			}
		}
		cur = head_student;
		while (cur)
		{
			if (!strcmp(cur->course_id, number))
				break;
			cur = cur->next;
		}
		strcpy(cur->assistant_ID, Assistant_ID);
		Write_Student(head_student, file);
		printf("\n********选择个人助教成功！********\n");
		Print_Stu_Course(id);
	}
	else 
		printf("\n********此课程暂无助教！选择个人助教失败！********\n");
	return false;
}
bool Change_Password(char* id)
{
	Account* head = Read_Account(), * cur = head;
	while (cur)
	{
		if (!strcmp(cur->ID, id))
			break;
		cur = cur->next;
	} 
	printf("\n请验证您现在的密码(输入'E'返回上一级):");
	char password[20];
	Secretword(password);
	if (password[0] == 'E' && password[1] == '\0')
	{
		printf("\n********取消修改密码成功！返回上一界面！********\n");
		return false;
	}
	if (strcmp(cur->Password, password))
	{
		printf("\n********密码错误！修改密码失败！返回上一界面！********\n");
		return false;
	}
	bool same = false;
	while (!same)
	{
		char password1[20], password2[20];
		printf("\n请输入您的新密码(不超过20个字符，由数字和小写字母构成，输入'E'返回上一级界面)：");
		Secretword(password1);
		if (password1[0] == 'E' && password1[1] == '\0')
		{
			printf("\n********取消修改密码成功！返回上一界面！********\n");
			return false;
		}
		printf("\n确认密码：");
		Secretword(password2);
		if (!strcmp(password1, password2))
		{
			strcpy(head->Password, password1);
			printf("\n********修改密码成功！********\n");
			same = true;
		}
		else
			printf("\n********两次密码输入不一致！请重新输入！********\n\n");
	}
	Write_Account(head);
	return false;
}
bool Exit_System_Stu(char* id)
{
	char file[25];
	strcpy(file, id);
	strcat(file, ".txt");
	Student_Class* head_student = Read_Student_Class(file);
	printf("\n");
	Warning(head_student);
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
		printf("\n********取消退出系统成功！返回上一级页面！********");
		return false;
	}
}
int  Number_Assistant_Course(char* id)
{
	int n = 0;
	Assistant_Class* head = Read_Assistant_Class();
	if (head == NULL)
	{
		FILE* fp = fopen("assistant.txt", "w+");
		fclose(fp);
		return 0;
	}
	while (head)
	{
		if (Search_Assistant(id, head->course_id))
			n++;
		head = head->next;
	}
	return n;
}
bool Search_Assistant(char* id, char* course_id)
{
	Assistant_Class* head = Read_Assistant_Class();
	if (head == NULL)
	{
		FILE* fp = fopen("assistant.txt", "w+");
		fclose(fp);
		return false;
	}
	bool find = false;
	while (head)
	{
		if (!strcmp(head->course_id, course_id))
		{
			find = true; break;
		}
		head = head->next;
	}
	if (!find)
		return false;
	else if (find)
	{
		Assistant* cur = Divide_Assistant(head->assistant_name);
		while (cur)
		{
			if (!strcmp(id, cur->name))
				return true;
			cur = cur->next;
		}
	}
	return false;
}
void Delete_Assistant(char* id, char* course_id)
{
	Assistant_Class* head = Read_Assistant_Class(), * pre = head;
	while (pre)
	{
		if (!strcmp(pre->course_id, course_id))
			break;
		pre = pre->next;
	}//退出循环时pre指向需要删助教的课程
	Assistant* cur = Divide_Assistant(pre->assistant_name);//拆分助教名字
	if (!strcmp(cur->name, id))
	{
		cur = cur->next;
		if (cur == NULL)
		{
			if (pre == head)
				head = head->next;
			else
			{
				Assistant_Class* pro = head;
				while (pro->next != pre)
					pro = pro->next;
				pro->next = pre->next;
			}
			Write_Assistant(head);
		}//删除了唯一的一个助教，则删去课程名
		else
		{
			char name[100];
			strcpy(name, cur->name);
			cur = cur->next;//第一个名字复制过去
			while (cur)
			{
				strcat(name, ",");
				strcat(name, cur->name);
				cur = cur->next;
			}//后面的名字拼接至大字符串中
			strcpy(pre->assistant_name, name);
			Write_Assistant(head);
		}
	}//头节点单独处理
	else
	{
		Assistant* a = cur, * b = cur->next;
		while (b)
		{
			if (!strcmp(b->name, id))
			{
				a->next = b->next; break;
			}
			a = b;
			b = b->next;
		}
		char name[100];
		strcpy(name, cur->name);
		cur = cur->next;//第一个名字复制过去
		while (cur)
		{
			strcat(name, ",");
			strcat(name, cur->name);
			cur = cur->next;
		}//后面的名字拼接至大字符串中
		strcpy(pre->assistant_name, name);
		Write_Assistant(head);
	}
}
void Add_Assistant(char* id, char* course_id)
{
	Assistant_Class* head = Read_Assistant_Class(), * cur = head;
	if (head == NULL)
	{
		Assistant_Class* p = (Assistant_Class*)malloc(sizeof(Assistant_Class));
		strcpy(p->course_id, course_id);
		strcpy(p->assistant_name, id);
		p->next = NULL;
		Write_Assistant(p);
		return;
	}
	while (cur)
	{
		if (!strcmp(cur->course_id, course_id))
			break;
		cur = cur->next;
	}//查找课程名
	if (cur != NULL)
	{
		strcat(cur->assistant_name, ",");
		strcat(cur->assistant_name, id);
		Write_Assistant(head);
	}//课程已经有助教
	else if (cur == NULL)
	{
		Assistant_Class* p = (Assistant_Class*)malloc(sizeof(Assistant_Class));
		strcpy(p->course_id, course_id);
		strcpy(p->assistant_name, id);
		if (strcmp(p->course_id, head->course_id) < 0)
		{
			p->next = head;
			head = p;
		}//插入头节点单独处理
		else
		{
			cur = head;
			while (cur->next)
			{
				if (strcmp(p->course_id, cur->next->course_id) > 0)
					cur = cur->next;
				else break;
			}
			p->next = cur->next;
			cur->next = p;
		}
		Write_Assistant(head);
	}
}
Assistant* Divide_Assistant(char* name)
{
	int i = 0, j = 0;
	Assistant* head = NULL, * tail = NULL;
	while (name[i])
	{
		Assistant* p = (Assistant*)malloc(sizeof(Assistant));
		p->next = NULL;
		while (name[i] != ',' && name[i] != '\0')
		{
			p->name[j] = name[i];
			i++, j++;
		}
		p->name[j] = '\0';
		if (head == NULL)
			head = p;
		else
			tail->next = p;
		tail = p;
		if (name[i] == ',')
			i++;
		j = 0;
	}
	return head;
}
void Check_Assistant(char* id)
{
	char file[25];
	strcpy(file, id);
	strcat(file, ".txt");
	Student_Class* head = Read_Student_Class(file), * cur = head;
	while (cur)
	{
		if (strcmp(cur->assistant_ID, "Null"))
		{
			if (!Search_Assistant(cur->assistant_ID, cur->course_id))
			{
				printf("\n********系统提示：您选择的编号为\"%s\"的课程的助教\"%s\"已退课！********\n", cur->course_id, cur->assistant_ID);
				strcpy(cur->assistant_ID, "Null");
			}
		}
		cur = cur->next;
	}
	Write_Student(head, file);
}
void Warning(Student_Class* head)
{
	Course* head_course = Read_Course("current_course.txt");
	int i = 0, j = 0;
	while (head_course)
	{
		if (Search(head, head_course->course_id))
		{
			if (head_course->category)i++;
			else j++;
		}
		head_course = head_course->next;
	}
	if (i < 4 || j < 2)
	{
		printf("根据学院要求，每名学生至少应该选择4门专业课和2门非专业课\n");
		if (i < 4)
			printf("目前已选专业课%d门，还差%d门！\n", i, 4 - i);
		if (j < 2)
			printf("目前已选非专业课%d门，还差%d门！\n", j, 2 - j);
		printf("选课数量不达标，请及时选课！\n");
	}
}