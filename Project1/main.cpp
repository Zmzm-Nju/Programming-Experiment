#include"Struct.h"//此头文件中包含C语言库函数与定义的结构体
#include"Common.h"//此头文件中包含管理员和学生共同需要的函数
#include"Admin.h"//此头文件中包含管理员操作相关函数
#include"Student.h"//此头文件中包含学生操作相关函数

//全局变量END用于判断是否退出系统
bool END = false;
int main()
{
	printf("********欢迎使用新生选课系统！********\n");
	while (!END)
	{
		Title_All();
		int k = 0;
		scanf("%d", &k);
		while (k > 4 || k <= 0)
		{
			printf("\n此输入无效！请输入有效的功能编号(1-4以内数字,请勿输入数字以外符号)：");
			scanf("%d", &k);
		}//循环获得有效输入，此时k必为1-4之间某一数字
		if (k == 1)//学生注册
			Student_Register();
		else if (k == 2)//学生登陆
		{
			char Stu_ID[20];//该学生的ID，登陆时输入获得
			if (Login_In_Student(Stu_ID))
			{
				bool end = false;
				while (!end)
				{
					Title_Student();
					int m = 0;
					scanf_s("%d", &m);
					while (m > 10 || m <= 0)
					{
						printf("\n此输入无效！请输入有效的功能编号：");
						scanf_s("%d", &m);
					}//循环获得有效输入,传入Admin中的k必为1-10之间的数
					end = Student(m, Stu_ID);//用m来控制学生操作，end控制登录的退出
				}
			}
		}
		else if (k == 3)//管理员登陆
		{
			if (Login_In_Admin())
			{
				bool end = false;
				while (!end)
				{
					Title_Admin();
					int m = 0;
					scanf_s("%d", &m);
					while (m > 10 || m <= 0)
					{
						printf("\n此输入无效！请输入有效的功能编号：");
						scanf_s("%d", &m);
					}//循环获得有效输入,传入Admin中的k必为1-10之间的数
					end = Admin(m);//用m来控制管理员操作，end控制登录的退出
				}
			}
		}
		else if (k == 4)
		{
			printf("\n是否确定要退出系统？输入1确认，否则默认为取消退出(仅支持输入数字)：");
			int m = 0;
			scanf_s("%d", &m);
			if (m == 1)
				END = true;
			else
				printf("\n********取消退出系统成功！返回上一级页面！********\n");
		}
	}
	printf("\n\n");
	Title_Gap();
	printf("\n********退出系统成功！感谢您的使用！********\n");
	return 0;
}

