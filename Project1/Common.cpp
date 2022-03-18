#include"Common.h"

//以下为文件读取函数：

Course* Read_Course(const char* file)//此函数传过去的s必为current_course和defaultcourse之一
{
	FILE* fp = fopen(file, "r");
	if (fp == NULL)
		return NULL;
	else
	{
		Course* head = NULL, * tail = NULL;
		char number[30];
		fscanf(fp, "%s\t", number);
		while (!feof(fp))
		{
			Course* p = (Course*)malloc(sizeof(Course));
			strcpy(p->course_id, number);
			fscanf(fp, "%s\t%s\t", p->course_name, p->teacher_name);
			fscanf(fp, "%d\t%d\t", &p->all, &p->now);
			char category[10];
			fscanf(fp, "%s\n", category);
			if (!strcmp("专业课", category))
				p->category = 1;
			else p->category = 0;
			p->next = NULL;
			if (head == NULL)
				head = p;
			else
				tail->next = p;
			tail = p;
			fscanf(fp, "%s\t", number);
		}
		fclose(fp);
		return head;
	}
}
Account* Read_Account()
{
	FILE* file = fopen("student.txt", "r");
	if (file == NULL)
		return NULL;
	Account* head = NULL, * tail = NULL;
	char Student[40], ID[20], password[20];
	fscanf(file, "%s", Student);
	while (!feof(file))
	{
		Account* p = (Account*)malloc(sizeof(Account));
		int i = 0, j = 0;
		for (; Student[i] != ','; i++)
			ID[i] = Student[i];
		ID[i] = '\0'; i++;//补结束符，i+1指向下一位
		for (; Student[i] != '\0'; i++, j++)
			password[j] = Student[i];
		password[j] = '\0';//补结束符
		strcpy(p->ID, ID);
		strcpy(p->Password, password);
		p->next = NULL;
		if (head == NULL)
			head = p;
		else
			tail->next = p;
		tail = p;
		/*printf("%s\n", p->ID);
		printf("%s\n", p->Password);*/
		fseek(file, sizeof('\n'), SEEK_CUR);
		fscanf(file, "%s", Student);
	}
	fclose(file);
	return head;
}
Student_Class* Read_Student_Class(char* file)
{
	FILE* fp = fopen(file, "r");
	if (file == NULL)
		return NULL;
	Student_Class* head = NULL, * tail = NULL;
	char number[4];
	fscanf(fp, "%s\t", number);//读入课程编号
	while (!feof(fp))
	{
		Student_Class* p = (Student_Class*)malloc(sizeof(Student_Class));
		strcpy(p->course_id, number);
		fscanf(fp, "%s\n", p->assistant_ID);
		p->next = NULL;
		if (head == NULL)
			head = p;
		else
			tail->next = p;
		tail = p;
		fscanf(fp, "%s\t", number);
	}
	fclose(fp);
	return head;
}
Assistant_Class* Read_Assistant_Class()
{
	FILE* file = fopen("assistant.txt", "r");
	if (file == NULL)
		return NULL;
	Assistant_Class* head = NULL, * tail = NULL;
	char ID[4];
	fscanf(file, "%s\t", ID);//读入课程编号
	while (!feof(file))
	{
		Assistant_Class* p = (Assistant_Class*)malloc(sizeof(Assistant_Class));
		strcpy(p->course_id, ID);
		fscanf(file, "%s\n", p->assistant_name);
		p->next = NULL;
		if (head == NULL)
			head = p;
		else
			tail->next = p;
		tail = p;
		fscanf(file, "%s\t", ID);
	}
	fclose(file);
	return head;
}

//以下为文件写入函数：

void Write_Course(Course* head, const char* file)
{
	FILE* fp = fopen(file, "w+");
	if (fp == NULL)
	{
		printf("\n异常错误！请找工作人员检查程序是否正确！");
		exit(0);
	}
	while (head)
	{
		fprintf(fp, "%s\t%s\t%s\t%d\t%d\t", head->course_id, head->course_name, head->teacher_name, head->all, head->now);
		if (head->category)
			fprintf(fp, "专业课\n");
		else fprintf(fp, "非专业课\n");
		head = head->next;
	}
	fclose(fp);
}
void Write_Student(Student_Class* head, const char* file)
{
	FILE* fp = fopen(file, "w+");
	if (fp == NULL)
	{
		printf("\n异常错误！请找工作人员检查程序是否正确！");
		exit(0);
	}
	while (head)
	{
		fprintf(fp, "%s\t%s\n", head->course_id, head->assistant_ID);
		head = head->next;
	}
	fclose(fp);
}
void Write_Account(Account* head)
{

	FILE* file = fopen("student.txt", "w+");
	if (file == NULL)
	{
		printf("\n异常错误！请找工作人员检查程序是否正确！");
		exit(0);
	}
	while (head)
	{
		fprintf(file, "%s,%s\n", head->ID, head->Password);
		head = head->next;
	}
	fclose(file);
}
void Write_Assistant(Assistant_Class* head)
{

	FILE* file = fopen("assistant.txt", "w+");
	if (file == NULL)
	{
		printf("\n异常错误！请找工作人员检查程序是否正确！");
		exit(0);
	}
	while (head)
	{
		fprintf(file, "%s\t%s\n", head->course_id, head->assistant_name);
		head = head->next;
	}
	fclose(file);
}

//以下为标题打印函数：

void Title_All()
{
	printf("\n\n");
	Title_Gap();
	printf("1.学生注册  2.学生登录  3.管理员登陆  4.退出系统\n");
	Title_Gap();
	printf("请输入功能编号(1-4以内数字,请勿输入数字以外符号):");
}
void Title_Admin()
{
	printf("\n\n");
	Title_Gap();
	printf("1.退出登录  2.录入课程信息  3.查看全部课程信息  4.增加课程  5.删除课程  \n6.修改课程  7.查看具体课程  8.查看全部课程助教  9.重置学生密码  10.退出系统\n");
	Title_Gap();
	printf("请输入功能编号(1-10以内数字,请勿输入数字以外符号):");
}
void Title_Student()
{
	printf("\n\n");
	Title_Gap();
	printf("1.退出登录  2.查看课程信息  3.选课  4.查看个人课表  5.退课  \n6.查看全部课程助教  7.举手报名助教  8.选择个人助教  9.修改密码  10.退出系统\n");
	Title_Gap();
	printf("请输入功能编号(1-10以内数字,请勿输入数字以外符号):");
}
void Title_Gap()
{
	for (int i = 0; i < 120; i++)
		printf("=");
	printf("\n");
}

//以下为学生和管理员都需要用到的函数

bool Print_Current_Course()
{
	Course* head = Read_Course("current_course.txt");
	if (head == NULL)
		printf("\n********尚未导入课程！无法查看课程信息！********\n");
	else if (head != NULL)
	{
		printf("\n课程ID\t 课程名称        \t授课教师 上限人数 目前已选 课程类型\n");
		while (head)
		{
			if (strlen(head->course_name) <= 7)
			{
				printf(" %s\t%s                \t %s\t   %d\t    %d\t", head->course_id, head->course_name, head->teacher_name, head->all, head->now);
				if (head->category)
					printf("   专业课\n");
				else printf("   非专业课\n");
			}//为了对齐美观，判断下课程名的长度,<=7则补16个空格
			else if (strlen(head->course_name) <= 15)
			{
				printf(" %s\t%s        \t %s\t   %d\t    %d\t", head->course_id, head->course_name, head->teacher_name, head->all, head->now);
				if (head->category)
					printf("   专业课\n");
				else printf("   非专业课\n");
			}//为了对齐美观，判断下课程名的长度,<=15则补8个空格
			else
			{
				printf(" %s\t%s\t %s\t   %d\t    %d\t", head->course_id, head->course_name, head->teacher_name, head->all, head->now);
				if (head->category)
					printf("   专业课\n");
				else printf("   非专业课\n");
			}
			head = head->next;
		}
	}
	return false;
}
bool Search(Student_Class* head, char* number)
{
	if (head == NULL)
		return false;
	Student_Class* cur = head;
	Course* head_course = Read_Course("current_course.txt");//读取课程信息，获取课程名
	bool find = false;
	while (cur)
	{
		while (head_course)
		{
			if (!strcmp(head_course->course_id, cur->course_id))
				break;
			head_course = head_course->next;
		}//从head_course里面找到cur的课程名
		if (!strcmp(cur->course_id, number) || !strcmp(head_course->course_name, number))
		{
			find = true; break;
		}
		cur = cur->next;
	}
	if (find)
		strcpy(number, cur->course_id);
	return find;
}
void Secretword(char* key) 
{
	unsigned char c;
	int i = 0;
	while ((c = _getch()) != '\r') 
	{
		if (i < 20 && isprint(c)) 
		{
			key[i] = c;
			i++;
			putchar('*');
		}
		else if (i > 0 && c == '\b') 
		{
			i--;
			putchar('\b');
			putchar(' ');
			putchar('\b');
		}
	}
	printf("\n");
	key[i] = '\0';
}
bool Print_Current_Assistant()
{
	Assistant_Class* head = Read_Assistant_Class();
	if (head == NULL)
	{
		printf("\n********尚无人举手报名助教！无法查看全部课程助教！********\n");
		FILE* fp = fopen("assistant.txt", "w+");
		fclose(fp);
		return false;
	}
	printf("\n\n");
	Title_Gap();
	while (head)
	{
		printf("%s\t%s\n", head->course_id, head->assistant_name);
		head = head->next;
	}
	Title_Gap();
	return false;
}
