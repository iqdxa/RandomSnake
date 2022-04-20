#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <time.h>
#include <windows.h>

int squre[11][11];		//定义数组

//询问是否继续函数
char IfStartGame()
{
	char ch;
	printf("输入N/n结束，按回车键继续：");
	scanf_s("%c", &ch, 1);
	if (ch == 'n' || ch == 'N')
	{
		return 0;	//不进入循环
	}
	else
	{
		system("cls");	//清屏
		return 1;		//进入循环
	}
}

//打印图案函数
Display(int x, int y)
{
	int i = 0, j = 0;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (i == x && j == y)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);//显示红色字体
				printf("%d\t", squre[i][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);// 恢复默认的字体颜色
			}
			else if (squre[i][j] != 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);//显示黄色字体
				printf("%d\t", squre[i][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);// 恢复默认的字体颜色
			}
			else
			{
				printf("%d\t", squre[i][j]);
			}
		}
		printf("\n\n");	//每输出N个就换行 
	}
	printf("\n");	//输出完成就换行
}

int Menu()
{
	int i;
	printf("请选择：\n");
	printf("1.开始游戏\n");
	printf("0.退出\n");
	scanf_s("%d", &i);
	if (i == 1 || i == 0)
	{
		system("cls");
		return i;
	}
	else
	{
		return -1;
	}
}

void Game()
{
	//定义各种变量
	int x = 0, y = 0;
	int i = 0, j = 0;
	int random, count = 1;
	bool start = 1;

	//初始化数组
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			squre[i][j] = 0;		//让所有位置都是0
		}
	}
	squre[0][0] = 1;				//第一个位置是1

	//随机数种子
	srand((unsigned)time(NULL));
	//显示初始图案
	Display(x, y);

	printf("开始游戏，你当前在第1行，第1列\n");

	while (start)
	{
		if (x == 0 && y != 0 && squre[x][y - 1] != 0 && squre[x][y + 1] != 0 && squre[x + 1][y] != 0)
		{
			//周围均无满足条件的情况，不再进入循环
			start = 0;
		}

		if (y == 0 && x != 0 && squre[x - 1][y] != 0 && squre[x][y + 1] != 0 && squre[x + 1][y] != 0)
		{
			//周围均无满足条件的情况，不再进入循环
			start = 0;
		}

		if (x != 0 && y != 0 && squre[x][y - 1] != 0 && squre[x][y + 1] != 0 && squre[x - 1][y] != 0 && squre[x + 1][y] != 0)	//判断是否有路可走
		{
			//周围均无满足条件的情况，不再进入循环
			start = 0;
		}
		else
		{
			//有路，继续
			//0上，1下，2左，3右
			random = rand() % 4;		//产生0-3的随机数

			switch (random)
			{
			case 0: x -= 1; break;
			case 1: x += 1; break;
			case 2: y -= 1; break;
			case 3: y += 1; break;
			}

			//判断是否在框内且位置是否被占
			if (x > 9 || y > 9 || x < 0 || y < 0 || squre[x][y] != 0)
			{
				//不符合条件，恢复并重来
				switch (random)
				{
				case 0:x += 1; break;
				case 1:x -= 1; break;
				case 2:y += 1; break;
				case 3:y -= 1; break;
				}
				continue;
			}
			else
			{
				//符合情况，继续
				count++;
				squre[x][y] = count;
			}

			//清屏并显示图案
			system("cls");
			Display(x, y);

			switch (random)
			{
				//0上，1下，2左，3右
			case 0: printf("向上走\n"); break;
			case 1: printf("向下走\n"); break;
			case 2: printf("向左走\n"); break;
			case 3: printf("向右走\n"); break;
			}
			printf("当前在%d行%d列，数字是：%d\n", x + 1, y + 1, count);
		}
		//Sleep(500);	//暂停输出


	//循环结束
	//清屏并显示最终图案
		system("cls");
		Display(x, y);

		printf("游戏结束\n");
		printf("在%d行，%d列结束，数字是：%d\n", x + 1, y + 1, count);

		//询问是否开始游戏
		start = IfStartGame();
		if (start == 1)
		{
			//如果start=1，则继续游戏
			Game();
		}
	}
}

int main()
{
	int judge=-1;
	//菜单
	while (judge == -1)
	{
		judge = Menu();
	}
	if (judge == 1)
	{
		//进入游戏
		Game();
	}
	
	system("pause");
	return 0;
}
