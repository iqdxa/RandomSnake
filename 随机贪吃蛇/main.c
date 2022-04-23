#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <time.h>
#include <windows.h>
#define N 12		//定义区域大小，包含围墙

//询问是否继续函数
int IfStartGame()
{
	char judge;
	printf("输入n或者N结束，按其他任意键继续：");
	scanf_s("%c", &judge,1);
	getchar();			//从控制台流中读取字符
	if (judge == 'n' || judge == 'N')
	{
			return 0;	//不进入循环
	}
	else
	{
			return 1;		//进入循环
	}
}

//打印图案函数
Display(int x, int y, int squre[N][N])
{
	int i = 0, j = 0;
	for (i = 0; i <= N-1; i++)
	{
		for (j = 0; j <= N-1; j++)
		{
			if (squre[i][j] == -1)
			{
				printf("||\t");
			}
			else if (i == x && j == y)
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

int Game_1()
{
	//定义各种变量
	int x = 1, y = 1;
	int i = 0, j = 0;
	int random = 0, count = 1;
	int start = 1;
	int judge = 0;	
	int squre[N][N];		//定义数组

	//初始化数组
	for (i = 0; i <= N-1; i++)
	{
		for (j = 0; j <= N-1; j++)
		{
			squre[i][j] = 0;		//让所有位置都是0
			//让边界为-1
			squre[j][0] = -1;
			squre[0][j] = -1;
			squre[j][11] = -1;
			squre[11][j] = -1;
		}
	}
	squre[1][1] = 1;				//第一个位置是1

	//随机数种子
	srand((unsigned)time(NULL));
	//清屏并显示图案
	system("cls");
	Display(x, y, squre);
	printf("开始游戏，你当前在第1行，第1列\n");

	do {
		if (squre[x][y - 1] != 0 && squre[x][y + 1] != 0 && squre[x + 1][y] != 0 && squre[x - 1][y] != 0)
		{
			//周围均无满足条件的情况，不再进入循环
			start = 0;
		}
		else
		{
			//有路，继续
			//0上，1下，2左，3右
			//产生0-3的随机数
			random = rand() % 4;
			switch (random)
			{
			case 0: x -= 1; break;
			case 1: x += 1; break;
			case 2: y -= 1; break;
			case 3: y += 1; break;
			}

			//判断是否在框内且位置是否被占
			if (x > 10 || y > 10 || x < 1 || y < 1 || squre[x][y] != 0)
			{
				//不符合条件，恢复并重来
				switch (random)
				{
				case 0:x += 1; break;
				case 1:x -= 1; break;
				case 2:y += 1; break;
				case 3:y -= 1; break;
				}
				//重新开始循环
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
			Display(x, y, squre);

			//判断走的方向
			switch (random)
			{
				//0上，1下，2左，3右
			case 0: printf("向上走\n"); break;
			case 1: printf("向下走\n"); break;
			case 2: printf("向左走\n"); break;
			case 3: printf("向右走\n"); break;
			}
			printf("当前在%d行%d列，数字是：%d\n", x, y, count);
		}
		//Sleep(500);	//暂停输出
	} while (start == 1);

	//循环结束
	//清屏并显示最终图案
	system("cls");
	Display(x, y, squre);

	printf("游戏结束\n");
	printf("在%d行，%d列结束，数字是：%d\n", x, y, count);

	//询问是否开始游戏
	judge = IfStartGame();

	if (judge == 1)
	{
		//如果judge=1，则继续游戏
		return 1;
	}
	else
	{
		//如果judge=0，则结束，回到菜单
		return -1;
	}
}

int Choose(int n)
{
	int line = 0;
	switch (n)
	{
	case 1://进入第一个游戏
		//循环游戏
		do {
			//进入第一个游戏
			//若返回1，则继续内层循环，若返回-1，则结束循环
			n = Game_1();
		} while (n == 1);
		break;
	case 0:break;
	default:break;
	}
	return n;
}

int Menu()
{
	int i,judge;
	//清屏
	system("cls");
	printf("请选择：\n");
	printf("1.随机贪吃蛇\n");
	printf("0.退出\n");
	judge=scanf_s("%d", &i);
	getchar();			//清除缓冲区的回车键
	if ((i == 1 || i == 0) && judge==1)
	{
		return i;
	}
	else
	{
		return -1;		//输入不符合条件，返回-1
	}
}

int main()
{
	int judge = -1;
	
	while (judge == -1)
	{
		//进入菜单，用户在菜单进行选择
		judge = Menu();
		//进入某个游戏，并返回-1，继续循环
		//若judge为0，则返回0，结束循环
		//若judge为-1，则返回-1，继续循环
		judge=Choose(judge);
	}
	system("pause");
	return 0;
}