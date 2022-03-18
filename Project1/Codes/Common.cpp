#include"Common.h"

//����Ϊ�ļ���ȡ������

Course* Read_Course(const char* file)//�˺�������ȥ��s��Ϊcurrent_course��defaultcourse֮һ
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
			if (!strcmp("רҵ��", category))
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
		ID[i] = '\0'; i++;//����������i+1ָ����һλ
		for (; Student[i] != '\0'; i++, j++)
			password[j] = Student[i];
		password[j] = '\0';//��������
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
	fscanf(fp, "%s\t", number);//����γ̱��
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
	fscanf(file, "%s\t", ID);//����γ̱��
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

//����Ϊ�ļ�д�뺯����

void Write_Course(Course* head, const char* file)
{
	FILE* fp = fopen(file, "w+");
	if (fp == NULL)
	{
		printf("\n�쳣�������ҹ�����Ա�������Ƿ���ȷ��");
		exit(0);
	}
	while (head)
	{
		fprintf(fp, "%s\t%s\t%s\t%d\t%d\t", head->course_id, head->course_name, head->teacher_name, head->all, head->now);
		if (head->category)
			fprintf(fp, "רҵ��\n");
		else fprintf(fp, "��רҵ��\n");
		head = head->next;
	}
	fclose(fp);
}
void Write_Student(Student_Class* head, const char* file)
{
	FILE* fp = fopen(file, "w+");
	if (fp == NULL)
	{
		printf("\n�쳣�������ҹ�����Ա�������Ƿ���ȷ��");
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
		printf("\n�쳣�������ҹ�����Ա�������Ƿ���ȷ��");
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
		printf("\n�쳣�������ҹ�����Ա�������Ƿ���ȷ��");
		exit(0);
	}
	while (head)
	{
		fprintf(file, "%s\t%s\n", head->course_id, head->assistant_name);
		head = head->next;
	}
	fclose(file);
}

//����Ϊ�����ӡ������

void Title_All()
{
	printf("\n\n");
	Title_Gap();
	printf("1.ѧ��ע��  2.ѧ����¼  3.����Ա��½  4.�˳�ϵͳ\n");
	Title_Gap();
	printf("�����빦�ܱ��(1-4��������,�������������������):");
}
void Title_Admin()
{
	printf("\n\n");
	Title_Gap();
	printf("1.�˳���¼  2.¼��γ���Ϣ  3.�鿴ȫ���γ���Ϣ  4.���ӿγ�  5.ɾ���γ�  \n6.�޸Ŀγ�  7.�鿴����γ�  8.�鿴ȫ���γ�����  9.����ѧ������  10.�˳�ϵͳ\n");
	Title_Gap();
	printf("�����빦�ܱ��(1-10��������,�������������������):");
}
void Title_Student()
{
	printf("\n\n");
	Title_Gap();
	printf("1.�˳���¼  2.�鿴�γ���Ϣ  3.ѡ��  4.�鿴���˿α�  5.�˿�  \n6.�鿴ȫ���γ�����  7.���ֱ�������  8.ѡ���������  9.�޸�����  10.�˳�ϵͳ\n");
	Title_Gap();
	printf("�����빦�ܱ��(1-10��������,�������������������):");
}
void Title_Gap()
{
	for (int i = 0; i < 120; i++)
		printf("=");
	printf("\n");
}

//����Ϊѧ���͹���Ա����Ҫ�õ��ĺ���

bool Print_Current_Course()
{
	Course* head = Read_Course("current_course.txt");
	if (head == NULL)
		printf("\n********��δ����γ̣��޷��鿴�γ���Ϣ��********\n");
	else if (head != NULL)
	{
		printf("\n�γ�ID\t �γ�����        \t�ڿν�ʦ �������� Ŀǰ��ѡ �γ�����\n");
		while (head)
		{
			if (strlen(head->course_name) <= 7)
			{
				printf(" %s\t%s                \t %s\t   %d\t    %d\t", head->course_id, head->course_name, head->teacher_name, head->all, head->now);
				if (head->category)
					printf("   רҵ��\n");
				else printf("   ��רҵ��\n");
			}//Ϊ�˶������ۣ��ж��¿γ����ĳ���,<=7��16���ո�
			else if (strlen(head->course_name) <= 15)
			{
				printf(" %s\t%s        \t %s\t   %d\t    %d\t", head->course_id, head->course_name, head->teacher_name, head->all, head->now);
				if (head->category)
					printf("   רҵ��\n");
				else printf("   ��רҵ��\n");
			}//Ϊ�˶������ۣ��ж��¿γ����ĳ���,<=15��8���ո�
			else
			{
				printf(" %s\t%s\t %s\t   %d\t    %d\t", head->course_id, head->course_name, head->teacher_name, head->all, head->now);
				if (head->category)
					printf("   רҵ��\n");
				else printf("   ��רҵ��\n");
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
	Course* head_course = Read_Course("current_course.txt");//��ȡ�γ���Ϣ����ȡ�γ���
	bool find = false;
	while (cur)
	{
		while (head_course)
		{
			if (!strcmp(head_course->course_id, cur->course_id))
				break;
			head_course = head_course->next;
		}//��head_course�����ҵ�cur�Ŀγ���
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
		printf("\n********�����˾��ֱ������̣��޷��鿴ȫ���γ����̣�********\n");
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
