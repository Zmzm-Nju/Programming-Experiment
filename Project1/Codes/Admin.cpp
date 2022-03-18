#include"Admin.h"
#include"Common.h"
//����Ϊ����Ա����������

int  Login_In_Admin()
{
	printf("\n\n");
	Title_Gap();
	printf("���������Ĺ���Ա�˺�(����'E'������һ��ҳ�棩��");
	char account[20];
	scanf("%s", account);
	while (strcmp("Admin", account))
	{
		if (account[0] == 'E' && account[1] == '\0')
		{
			printf("\n********ȡ������Ա��½�ɹ���������һ���棡********\n");
			return 0;
		}
		printf("\n�˺Ŵ������������������˺�(����'E'������һ��ҳ��)��");
		scanf("%s", account);
	}
	printf("\n��������������(����3���������)��");
	char password[20];
	for (int i = 0; i < 3; i++)
	{
		Secretword(password);
		if (!strcmp("admin", password))
		{
			printf("\n********��½�ɹ�����ӭʹ��ѡ�ι���ϵͳ��********\n");
			Title_Gap();
			return 1;
		}
		else if (i != 2)
			printf("\n��������������(����%d���������)��", 2 - i);
		else
			printf("\n********����Ա��½ʧ�ܣ�������һ��ҳ�棡********\n");
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
bool Set_Up_Current_Course()
{
	FILE* file = fopen("current_course.txt", "r");
	if (file == NULL)
	{
		Course* Head_Course = Read_Course("defaultcourse.txt");
		if (Head_Course == NULL)
			printf("\n********��Դ�ļ�(defaultcourse.txt)�����ڣ������Ƿ����********\n");
		if (Head_Course != NULL)
		{
			Write_Course(Head_Course, "current_course.txt");
			printf("\n********�γ���Ϣ¼��ɹ���********\n");
		}
	}
	else
	{
		printf("\n********�γ���Ϣ��¼�룬�����ظ�¼��!********\n");
		fclose(file);
	}
	return false;
}
bool Add_Course()
{
	Course* head = Read_Course("current_course.txt");
	if (head == NULL)
		printf("\n********��δ����γ̣��޷��鿴�γ���Ϣ��********\n");
	else if (head != NULL)
	{
		printf("\n������������Ҫ��ӵĿγ���Ϣ��\n");
		Course* p = (Course*)malloc(sizeof(Course));
		printf("1.�γ�����(����'E'������һ������)��");
		char Name[30];
		scanf("%s", Name);
		if (Name[0] == 'E' && Name[1] == '\0')
		{
			printf("\n********ȡ����ӿγ̳ɹ���������һ���棡********\n");
			return false;
		}
		strcpy(p->course_name, Name);
		printf("2.�ڿν�ʦ��");
		scanf("%s", p->teacher_name);
		printf("3.����������");
		scanf("%d", &p->all);
		printf("4.��ѡ������");
		scanf("%d", &p->now);
		char category[30];
		printf("5.�γ����");
		scanf("%s", category);
		if (!strcmp("רҵ��", category))
			p->category = 1;
		else p->category = 0;
		//printf("%s\t%s\t%d\t%d\t%d\n",p->course_name, p->teacher_name, p->all, p->now, p->category);
		Course* cur = head;
		while (cur != NULL)//������������Ƿ�����ͬ�γ�
		{
			if (!strcmp(p->course_name, cur->course_name) && !strcmp(p->teacher_name, cur->teacher_name))
			{
				printf("\n********���д˿γ̣����ʧ�ܣ�********\n");
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
		printf("\n********��ӳɹ���********\n");
		Print_Current_Course();
	}
	return false;
}
bool Modify_Course()
{
	Course* head = Read_Course("current_course.txt");
	if (head == NULL)
		printf("\n********��δ����γ̣��޷��޸Ŀγ���Ϣ��********\n");
	else if (head != NULL)
	{
		printf("\n��������Ҫ�޸���Ϣ�γ̵�ID(����'E'������һ������)��");
		char Back[4];
		scanf("%s", Back);
		if (Back[0] == 'E' && Back[1] == '\0')
		{
			printf("\n********ȡ���޸Ŀγ���Ϣ�ɹ���������һ���棡********\n");
			return false;
		}
		bool find = false;
		Course* b = head;
		while (b)
		{
			if (!strcmp(b->course_id, Back))
			{
				find = true; break;
			}//����ҵ��ÿγ̣��˳�ʱb�պ�ָ��ÿγ̶�Ӧ�ڵ�
			b = b->next;
		}
		if (!find)
			printf("\n********�޴˿γ̣��޸Ŀγ���Ϣʧ�ܣ�********\n");
		else
		{
			printf("\n��ѡ����Ҫ�޸ĵľ�����Ϣ��(1.�ον�ʦ  2.��������)");
			int n = 0;
			scanf("%d", &n);
			while (n > 2 || n <= 0)
			{
				printf("\n��������Ч����������Ч�Ĺ��ܱ��(1-2��������,�������������������)��");
				scanf_s("%d", &n);
			}//ѭ�������Ч���룬��ʱn��Ϊ1-2֮��ĳһ����
			if (n == 1)
			{
				printf("\n�����޸�Ϊ��");
				char teacher[30];
				scanf("%s", teacher);
				if (!strcmp(teacher, b->teacher_name))
					printf("\n********�޸�ʧ��!�ο���ʦ�Ѿ�Ϊ����ʦ��********\n");
				else
				{
					strcpy(b->teacher_name, teacher);
					Write_Course(head, "current_course.txt");
					printf("\n********�޸ĳɹ���********\n");
					Print_Current_Course();
				}
			}
			if (n == 2)
			{
				printf("\n�����޸�Ϊ��");
				int k = 0;
				scanf_s("%d", &k);
				if (k < b->now)
					printf("\n********�޸�ʧ��!�޸ĺ���������С����ѡ������********\n");
				else
				{
					b->all = k;
					Write_Course(head, "current_course.txt");
					printf("\n********�޸ĳɹ���********\n");
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
		printf("\n********��δ����γ̣��޷�ɾ���γ̣�********\n");
	else if (head != NULL)
	{
		printf("\n��������Ҫɾ���γ̵�ID(����'E'������һ������)��");
		char ID[10];
		scanf("%s", ID);
		if (ID[0] == 'E' && ID[1] == '\0')
		{
			printf("\n********ȡ��ɾ���γ̳ɹ���������һ���棡********\n");
			return false;
		}
		if (!strcmp(ID, head->course_id))//ͷ�ڵ㵥�����������
		{
			if (head->now != 0)
				printf("\n********����ѧ��ѡ��˿γ̣�ɾ���γ�ʧ�ܣ�********\n");
			else 
			{
				Course* cur = head;
				Write_Course(head->next, "current_course.txt");
				printf("\n********ɾ���ɹ���********\n");
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
				}//����ҵ��ÿγ̣��˳�ʱcur�պ�ָ��ÿγ̶�Ӧ�ڵ�
				pre = cur;
				cur = cur->next;
			}
			if (!find)
				printf("\n********�޴˿γ̣�ɾ���γ�ʧ�ܣ�********\n");
			else
			{
				if (cur->now != 0)
					printf("\n********����ѧ��ѡ��˿γ̣�ɾ���γ�ʧ�ܣ�********\n");
				else
				{
					pre->next = cur->next;
					free(cur);
					Write_Course(head, "current_course.txt");
					printf("\n********ɾ���γ̳ɹ���********\n");
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
		printf("\n********��δ����γ̣��޷��鿴�γ̣�********\n");
	else if (head != NULL)
	{
		printf("\n��������Ҫ�鿴�Ŀγ̵�ID(����'E'������һ������)��");
		char ID[4];
		scanf("%s", ID);
		if (ID[0] == 'E' && ID[1] == '\0')
		{
			printf("\n********ȡ���鿴�γ���Ϣ�ɹ���������һ���棡********\n");
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
				}//����ҵ��ÿγ̣��˳�ʱcur�պ�ָ��ÿγ̶�Ӧ�ڵ�
				cur = cur->next;
			}
			if (!find)
			{
				printf("\n�޴˿γ̣��鿴�γ�ʧ�ܣ�����������γ�ID:");
				scanf("%s", ID);
			}
			else if (find)
			{
				printf("\n");
				Title_Gap();
				printf(" %s\t%s\t%s\t%d\t%d\t", cur->course_id, cur->course_name, cur->teacher_name, cur->all, cur->now);
				if (cur->category)
					printf(" רҵ��\n");
				else printf(" ��רҵ��\n");
				Title_Gap();
				printf("\n��ϣ�����������������:1.�鿴ѡ��ѧ������  2.�鿴�γ̱�����������\n");
				printf("�����������ţ�");
				int a = 0;
				scanf_s("%d", &a);
				if (a == 1)
				{
					Account* m = Read_Account();//��ȡ�����˻�
					if (m == NULL)
					{
						FILE* fp = fopen("student.txt", "w+");
						fclose(fp);
						printf("\n********�鿴ʧ�ܣ�����ѧ��ѡ�Σ�********\n");
					}//����NULL���½�һ���ļ�
					int k = 0;
					Title_Gap();
					printf("ѡ��ÿγ̵�ѧ���У�\n");
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
						}//����һ��������
						m = m->next;
					}
					printf("\n");
					printf("ѡ����ſε�ͬѧ����%d��,�������λ���%d�ˡ�\n", cur->now, cur->all-cur->now);
					Title_Gap();
				}
				else if (a == 2)
				{
					Assistant_Class* head = Read_Assistant_Class();
					if (head == NULL)
					{
						FILE* fp = fopen("assistant.txt", "w+");
						fclose(fp);
						printf("\n********�鿴ʧ�ܣ��ÿγ��������̣�********\n");
					}//����NULL���½�һ���ļ�
					else
					{
						Assistant_Class* b = head;
						while (b)
						{
							if (!strcmp(b->course_id, ID))
							{
								printf("\n���ſε������У�%s\n", b->assistant_name);
								break;
							}//����ҵ��ÿγ̣��˳�ʱb�պ�ָ��ÿγ̶�Ӧ�ڵ�
							b = b->next;
						}
						if (b == NULL)//�����Ҳû�ҵ����ſ�
							printf("\n********�鿴ʧ�ܣ��ÿγ��������̣�********\n");
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
	printf("\n��������Ҫ���������ѧ����ID(����'E'������һ��):");
	char ID[20];
	scanf("%s", ID);
	if (ID[0] == 'E' && ID[1] == '\0')
	{
		printf("\n********ȡ������ѧ������ɹ���������һ���棡********\n");
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
			}//����ҵ���ѧ�����˳�ʱcur�պ�ָ���ѧ����Ӧ�ڵ�
			cur = cur->next;
		}
		if (!find)
		{
			printf("\n�޴�ѧ�����޷�����ѧ�����룡����������ѧ��ID(����'E'������һ��):");
			scanf("%s", ID);
			if (ID[0] == 'E' && ID[1] == '\0')
			{
				printf("\n********ȡ������ѧ������ɹ���������һ���棡********\n");
				return false;
			}
		}
		else if (find)
		{
			printf("\n�Ƿ�ȷ��Ҫ���ø�ѧ�����룿����1ȷ�ϣ�����Ĭ��Ϊȡ����������һ��ҳ��(��֧����������)��");
			int m = 0;
			scanf_s("%d", &m);
			if (m == 1)
			{
				strcpy(cur->Password, "NJUCS2020");
				printf("\n********����ѧ������ɹ���********\n");
			}
			else
				printf("\n********ȡ������ѧ������ɹ���������һ��ҳ�棡********\n");
		}
	}
	Write_Account(head);
	return false;
}
bool Exit_System_Admin()
{
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
		printf("\n********ȡ���˳�ϵͳ�ɹ���������һ��ҳ�棡********\n");
		return false;
	}
}
void Str_Plus(char* str1, char* str2)
{
	str1[3] = '\0';
	//���ǽ�λ���������Ȼֻ����λ����ֱ�ӷ��������
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