#include"Common.h"
#include"Student.h"
//����Ϊѧ������������
void Student_Register()
{
	Account* head = Read_Account(), * cur = head;
	char ID[20], password1[20], password2[20];
	printf("\n********��ӭע��ѧ��ѡ��ϵͳ��********\n");
	printf("\n����������ID��(������20���ַ��������ֺ�Сд��ĸ���ɣ�����'E'������һ������)��");
	scanf("%s", ID);
	if (ID[0] == 'E' && ID[1] == '\0')
	{
		printf("\n********ȡ��ע���˺ųɹ���������һ���棡********\n");
		return;
	}
	if (cur == NULL)
	{
		bool same = false;
		while (!same)
		{
			printf("\n��������������(������20���ַ��������ֺ�Сд��ĸ���ɣ�����'E'������һ������)��");
			Secretword(password1);
			if (password1[0] == 'E' && password1[1] == '\0')
			{
				printf("\n********ȡ��ע���˺ųɹ���������һ���棡********\n");
				return;
			}
			printf("\nȷ�����룺");
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
				printf("\n********�����������벻һ�£����������룡********\n\n");
		}
	}
	else
	{
		while (cur)
		{
			if (!strcmp(cur->ID, ID))
			{
				printf("\n��ID�Ѵ��ڣ���������������ID��(����'E'������һ������)��");
				scanf("%s", ID);
				if (ID[0] == 'E' && ID[1] == '\0')
				{
					printf("\n********ȡ��ע���˺ųɹ���������һ���棡********\n");
					return ;
				}
				cur = head; continue;
			}
			cur = cur->next;
		}
		bool same = false;
		while (!same)
		{
			printf("\n��������������(������20���ַ��������ֺ�Сд��ĸ���ɣ�����'E'������һ������)��");
			Secretword(password1);
			if (password1[0] == 'E' && password1[1] == '\0')
			{
				printf("\n********ȡ��ע���˺ųɹ���������һ���棡********\n");
				return;
			}
			printf("\nȷ�����룺");
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
				printf("\n********�����������벻һ�£����������룡\n\n");
		}
	}
	char file[25];
	strcpy(file, ID);
	strcat(file, ".txt");
	FILE* fp = fopen(file, "w+");
	if (fp == NULL)
		printf("\n********�����쳣������������ԱѰ�������********\n");
	else
	{
		fclose(fp);
		printf("\n********ע��ɹ�����ӭʹ�ñ�ϵͳ��********\n");
		printf("\n���ס�����˺ź����룬���������룬���ҹ���Ա���ã�\n");
	}
}
int  Login_In_Student(char* id)
{
	Account* head = Read_Account(), * cur = head;
	if (head == NULL)
	{
		printf("\n********��δע���˺ţ���ע���ٵ�½��********\n");
		FILE* file = fopen("student.txt", "w+");
		fclose(file);
		return false;
	}
	printf("\n\n");
	Title_Gap();
	printf("����������ѧ���˺�(����'E'������һ��ҳ�棩��");
	char ID[20], password[20];
	scanf("%s", ID);
	bool find = false;
	while (!find)
	{
		if (ID[0] == 'E' && ID[1] == '\0')
		{
			printf("\n********ȡ����½�ɹ���������һ���棡********\n");
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
			printf("\n���˺���δע�ᣬ���������������˺�(����'E'������һ������)��");
			scanf("%s", ID);
			if (ID[0] == 'E' && ID[1] == '\0')
			{
				printf("\n********ȡ����½�ɹ���������һ���棡********\n");
				return 0;
			}

		}
	}
	printf("\n��������������(����3���������)��");
	char password_In[20];
	for (int i = 0; i < 3; i++)
	{
		Secretword(password_In);
		if (!strcmp(password_In, password))
		{
			printf("\n\n********��½�ɹ�����ӭʹ��ѡ�ι���ϵͳ��********\n");
			Title_Gap();
			Check_Assistant(ID);
			strcpy(id, ID);
			return 1;
		}
		else if (i != 2)
			printf("\n�������������������������(����%d���������)��", 2 - i);
		else
			printf("\n********��½ʧ�ܣ�������һ��ҳ�棡\n");
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
	printf("\n�Ƿ�ȷ��Ҫ�˳���¼������1ȷ�ϣ�����Ĭ��Ϊȡ���˳�(��֧����������)��");
	int m = 0;
	scanf_s("%d", &m);
	if (m == 1)
	{
		printf("\n********�˳���¼�ɹ�������ϵͳ��ҳ�棡********\n");
		return true;
	}
	else
	{
		printf("\n********ȡ���˳���¼�ɹ���������һ��ҳ�棡********\n");
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
		printf("\n********����Ա��δ����γ̣��޷�ѡ�Σ�********\n");
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
		printf("\n********����ѡ��ʮ�ſγ̣��޷�����ѡ�Σ�********\n");
		return false;
	}
	printf("\n��������Ҫѡ��γ̵�ID��(����'E'������һ������)��");
	char ID[10];
	scanf("%s", ID);
	if (ID[0] == 'E' && ID[1] == '\0')
	{
		printf("\n********ȡ��ѡ�γɹ���������һ���棡********\n");
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
			}//����ҵ��ÿγ̣��˳�ʱcur�պ�ָ��ÿγ̶�Ӧ�ڵ�
			cur = cur->next;
		}
		if (!find)
		{
			printf("\n********�޴˿γ̣�ѡ��ʧ�ܣ�********\n");
			printf("\n������������Ҫѡ��γ̵�ID(����'E'������һ������)��");
			scanf("%s", ID);
			if (ID[0] == 'E' && ID[1] == '\0')
			{
				printf("\n********ȡ��ѡ�γɹ���������һ���棡********\n");
				return false;
			}
		}
		else if (find && cur->all == cur->now)
		{
			printf("\n********�ÿγ�������ѡ��ʧ�ܣ�********\n");
			printf("\n������������Ҫѡ��γ̵�ID(����'E'������һ������)��");
			scanf("%s", ID);
			if (ID[0] == 'E' && ID[1] == '\0')
			{
				printf("\n********ȡ��ѡ�γɹ���������һ���棡********\n");
				return false;
			}
			find = false;
		}
		else if (Search(head_student, ID))
		{
			printf("\n********����ѡ��ÿγ̣�ѡ��ʧ�ܣ�********\n");
			printf("\n������������Ҫѡ��γ̵�ID(����'E'������һ������)��");
			scanf("%s", ID);
			if (ID[0] == 'E' && ID[1] == '\0')
			{
				printf("\n********ȡ��ѡ�γɹ���������һ���棡********\n");
				return false;
			}
			find = false;
		}
	}//��ѭ��ʱ,�Ѿ�ѡ��һ��δ���Ŀ�
	if (head_student == NULL)//������δѡ�Σ�����Ϊ��
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
		//ѡ��ǡ���ĵط�����p
		if (strcmp(p->course_id, head_student->course_id) < 0)
		{
			p->next = head_student;
			head_student = p;
		}//����ͷ�ڵ㵥������
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
	printf("\n********ѡ�γɹ����ÿγ�����������˿α�********\n");
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
		printf("\n********����δѡ�Σ��޷���ӡ���˿α�********\n\n");
		Warning(head_student);
		return false;
	}
	printf("\n\n");
	Title_Gap();
	printf("�γ�ID\t �γ�����        \t�ڿν�ʦ   �γ�����   ��������\n");
	while (head_course)
	{
		if (Search(head_student, head_course->course_id))
		{
			if (strlen(head_course->course_name) <= 7)
			{
				printf(" %s\t%s                \t %s\t", head_course->course_id, head_course->course_name, head_course->teacher_name);
				if (head_course->category)
					printf("   רҵ��\t");
				else
					printf("   ��רҵ��\t");
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
			}//Ϊ�˶������ۣ��ж��¿γ����ĳ���,<=7��16���ո�
			else if (strlen(head_course->course_name) <= 15)
			{
				printf(" %s\t%s        \t %s\t", head_course->course_id, head_course->course_name, head_course->teacher_name);
				if (head_course->category)
					printf("   רҵ��\t");
				else
					printf("   ��רҵ��\t");
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
			}//Ϊ�˶������ۣ��ж��¿γ����ĳ���,<=15��8���ո�
			else
			{
				printf(" %s\t%s\t %s\t", head_course->course_id, head_course->course_name, head_course->teacher_name);
				if (head_course->category)
					printf("   רҵ��\t");
				else
					printf("   ��רҵ��\t");
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
		printf("\n********����δѡ�Σ��޷��˿Σ�********\n");
		return false;
	}
	printf("\n��������Ҫ�˳��γ̵Ŀγ�������ID(����'E'������һ������)��");
	char number[30];
	scanf("%s", number);
	if (number[0] == 'E' && number[1] == '\0')
	{
		printf("\n********ȡ���˿γɹ���������һ���棡********\n");
		return false;
	}
	bool find = Search(head_student, number);
	while (!find)
	{
		printf("\n********��δѡ�˿γ̣��˿�ʧ�ܣ�********\n");
		printf("\n������������Ҫ�˳��γ̵�ID(����'E'������һ������)��");
		scanf("%s", number);
		if (number[0] == 'E' && number[1] == '\0')
		{
			printf("\n********ȡ���˿γɹ���������һ���棡********\n");
			return false;
		}
		find = Search(head_student, number);
	}//��ѭ��ʱ���Ѿ��ҵ���Ҫ�˵Ŀγ̣��������޸�Ϊ�γ���
	if (!strcmp(head_student->course_id, number))
	{
		Student_Class* temp = head_student;
		head_student = head_student->next;
		free(temp);
		Write_Student(head_student, file);
		printf("\n********�˿γɹ���********\n");
		Print_Stu_Course(id);
	}//ͷ�ڵ㵥������
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
				printf("\n********�˿γɹ���********\n");
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
		printf("\n********����δѡ�Σ��޷����ֱ������̣�********\n");
		return false;
	}
	if (Number_Assistant_Course(id) >= 2)
	{
		printf("\n********���Ѿ������ſε����̣��޷��پ��ֱ������̣�********\n");
		return false;
	}
	printf("\n��������Ҫ���ֱ������̿γ̵Ŀγ�������ID(����'E'������һ������)��");
	char number[30];
	scanf("%s", number);
	if (number[0] == 'E' && number[1] == '\0')
	{
		printf("\n********ȡ�����ֱ������̳ɹ���������һ���棡********\n");
		return false;
	}
	bool find = Search(head_student, number);
	bool already = true;//�ʼ��Ϊtrue���Խ���ѭ���ж�
	while (!find || already)
	{
		if (!find)
		{
			printf("\n********��δѡ�˿γ̣����ֱ�������ʧ�ܣ�********\n");
			printf("\n������������Ҫ���ֱ������̿γ̵Ŀγ�������ID(����'E'������һ������)��");
			scanf("%s", number);
			if (number[0] == 'E' && number[1] == '\0')
			{
				printf("\n********ȡ�����ֱ������̳ɹ���������һ���棡********\n");
				return false;
			}
			find = Search(head_student, number); continue;
		}
		if (find)
		{
			already = Search_Assistant(id, number);
			if (already)
			{
				printf("\n********���Ѿ��Ǵ˿γ����̣����ֱ�������ʧ�ܣ�********\n");
				printf("\n������������Ҫ���ֱ������̵Ŀγ�������ID(����'E'������һ������)��");
				scanf("%s", number);
				if (number[0] == 'E' && number[1] == '\0')
				{
					printf("\n********ȡ�����ֱ������̳ɹ���������һ���棡********\n");
					return false;
				}
			}
			else break;
		}
	}//��ѭ��ʱ���Ѿ��ҵ��������̵Ŀγ̣��������޸�Ϊ�γ���
	Add_Assistant(id, number);
	printf("\n********���ֱ������̳ɹ���********\n");
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
		printf("\n********����δѡ�Σ��޷�ѡ��������̣�********\n");
		return false;
	}
	Assistant_Class* pre = Read_Assistant_Class();
	if (pre == NULL)
	{
		printf("\n********�����˾��ֱ������̣��޷�ѡ��������̣�********\n");
		FILE* fp = fopen("assistant.txt", "w+");
		fclose(fp);
		return false;
	}
	printf("\n��������Ҫѡ�����̿γ̵Ŀγ�������ID(����'E'������һ������)��");
	char number[30];
	scanf("%s", number);
	if (number[0] == 'E' && number[1] == '\0')
	{
		printf("\n********ȡ��ѡ��������̳ɹ���������һ���棡********\n");
		return false;
	}
	bool find = Search(head_student, number);
	bool have_assistant = true;//�ʼ��Ϊtrue���Խ���ѭ���ж�
	while (!find || have_assistant)
	{
		if (!find)
		{
			printf("\n********��δѡ�˿γ̣�ѡ���������ʧ�ܣ�********\n");
			printf("\n������������Ҫѡ��������̿γ̵Ŀγ�������ID(����'E'������һ������)��");
			scanf("%s", number);
			if (number[0] == 'E' && number[1] == '\0')
			{
				printf("\n********ȡ��ѡ��������̳ɹ���������һ���棡********\n");
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
				printf("\n********��˿γ��Ѿ�ӵ�����̣�ѡ���������ʧ�ܣ�********\n");
				printf("\n������������Ҫѡ��������̿γ̵Ŀγ�������ID(����'E'������һ������)��");
				scanf("%s", number);
				if (number[0] == 'E' && number[1] == '\0')
				{
					printf("\n********ȡ��ѡ��������̳ɹ���������һ���棡********\n");
					return false;
				}
				find = Search(head_student, number); continue;
			}
			else break;
		}
	}//��ѭ��ʱ���Ѿ��ҵ��������̵Ŀγ̣��������޸�Ϊ�γ���
	while (pre)
	{
		if (!strcmp(pre->course_id, number))
			break;
		pre = pre->next;
	}//����ҵ��ÿγ̣��˳�ʱpre�պ�ָ��ÿγ̶�Ӧ�ڵ㣬����ΪNULL
	if (pre != NULL)
	{
		printf("\n���ſε������У�%s\n", pre->assistant_name);
		printf("\n����������ѡ�����̵�ID(����'E'������һ������)��");
		char Assistant_ID[20];
		scanf("%s", Assistant_ID);
		if (Assistant_ID[0] == 'E' && Assistant_ID[1] == '\0')
		{
			printf("\n********ȡ��ѡ��������̳ɹ���������һ���棡********\n");
			return false;
		}
		while (!strcmp(Assistant_ID, id) || !Search_Assistant(Assistant_ID, number))
		{
			if (!strcmp(Assistant_ID, id))
			{
				printf("\n********����ѡ���Լ����Լ������̣�********\n");
				printf("\n���ſε������У�%s\n", pre->assistant_name);
				printf("\n����������ѡ�����̵�ID(����'E'������һ������)��");
				scanf("%s", Assistant_ID);
				if (Assistant_ID[0] == 'E' && Assistant_ID[1] == '\0')
				{
					printf("\n********ȡ��ѡ��������̳ɹ���������һ���棡********\n");
					return false;
				} 
				continue;
			}
			if (!Search_Assistant(Assistant_ID, number))
			{
				printf("\n********����ID���󣡴��˲��Ǳ��γ����̣�********\n");
				printf("\n���ſε������У�%s\n", pre->assistant_name);
				printf("\n����������ѡ�����̵�ID(����'E'������һ������)��");
				scanf("%s", Assistant_ID);
				if (Assistant_ID[0] == 'E' && Assistant_ID[1] == '\0')
				{
					printf("\n********ȡ��ѡ��������̳ɹ���������һ���棡********\n");
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
		printf("\n********ѡ��������̳ɹ���********\n");
		Print_Stu_Course(id);
	}
	else 
		printf("\n********�˿γ��������̣�ѡ���������ʧ�ܣ�********\n");
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
	printf("\n����֤�����ڵ�����(����'E'������һ��):");
	char password[20];
	Secretword(password);
	if (password[0] == 'E' && password[1] == '\0')
	{
		printf("\n********ȡ���޸�����ɹ���������һ���棡********\n");
		return false;
	}
	if (strcmp(cur->Password, password))
	{
		printf("\n********��������޸�����ʧ�ܣ�������һ���棡********\n");
		return false;
	}
	bool same = false;
	while (!same)
	{
		char password1[20], password2[20];
		printf("\n����������������(������20���ַ��������ֺ�Сд��ĸ���ɣ�����'E'������һ������)��");
		Secretword(password1);
		if (password1[0] == 'E' && password1[1] == '\0')
		{
			printf("\n********ȡ���޸�����ɹ���������һ���棡********\n");
			return false;
		}
		printf("\nȷ�����룺");
		Secretword(password2);
		if (!strcmp(password1, password2))
		{
			strcpy(head->Password, password1);
			printf("\n********�޸�����ɹ���********\n");
			same = true;
		}
		else
			printf("\n********�����������벻һ�£����������룡********\n\n");
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
	printf("\n�Ƿ�ȷ��Ҫ�˳�ϵͳ������1ȷ�ϣ�����Ĭ��Ϊȡ���˳�(��֧����������)��");
	int m = 0;
	scanf_s("%d", &m);
	if (m == 1)
	{
		END = true;
		return true;
	}
	else
	{
		printf("\n********ȡ���˳�ϵͳ�ɹ���������һ��ҳ�棡********");
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
	}//�˳�ѭ��ʱpreָ����Ҫɾ���̵Ŀγ�
	Assistant* cur = Divide_Assistant(pre->assistant_name);//�����������
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
		}//ɾ����Ψһ��һ�����̣���ɾȥ�γ���
		else
		{
			char name[100];
			strcpy(name, cur->name);
			cur = cur->next;//��һ�����ָ��ƹ�ȥ
			while (cur)
			{
				strcat(name, ",");
				strcat(name, cur->name);
				cur = cur->next;
			}//���������ƴ�������ַ�����
			strcpy(pre->assistant_name, name);
			Write_Assistant(head);
		}
	}//ͷ�ڵ㵥������
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
		cur = cur->next;//��һ�����ָ��ƹ�ȥ
		while (cur)
		{
			strcat(name, ",");
			strcat(name, cur->name);
			cur = cur->next;
		}//���������ƴ�������ַ�����
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
	}//���ҿγ���
	if (cur != NULL)
	{
		strcat(cur->assistant_name, ",");
		strcat(cur->assistant_name, id);
		Write_Assistant(head);
	}//�γ��Ѿ�������
	else if (cur == NULL)
	{
		Assistant_Class* p = (Assistant_Class*)malloc(sizeof(Assistant_Class));
		strcpy(p->course_id, course_id);
		strcpy(p->assistant_name, id);
		if (strcmp(p->course_id, head->course_id) < 0)
		{
			p->next = head;
			head = p;
		}//����ͷ�ڵ㵥������
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
				printf("\n********ϵͳ��ʾ����ѡ��ı��Ϊ\"%s\"�Ŀγ̵�����\"%s\"���˿Σ�********\n", cur->course_id, cur->assistant_ID);
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
		printf("����ѧԺҪ��ÿ��ѧ������Ӧ��ѡ��4��רҵ�κ�2�ŷ�רҵ��\n");
		if (i < 4)
			printf("Ŀǰ��ѡרҵ��%d�ţ�����%d�ţ�\n", i, 4 - i);
		if (j < 2)
			printf("Ŀǰ��ѡ��רҵ��%d�ţ�����%d�ţ�\n", j, 2 - j);
		printf("ѡ����������꣬�뼰ʱѡ�Σ�\n");
	}
}