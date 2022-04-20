#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <time.h>
#include <windows.h>

int squre[11][11];		//��������

//ѯ���Ƿ��������
char IfStartGame()
{
	char ch;
	printf("����N/n���������س���������");
	scanf_s("%c", &ch, 1);
	if (ch == 'n' || ch == 'N')
	{
		return 0;	//������ѭ��
	}
	else
	{
		system("cls");	//����
		return 1;		//����ѭ��
	}
}

//��ӡͼ������
Display(int x, int y)
{
	int i = 0, j = 0;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (i == x && j == y)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);//��ʾ��ɫ����
				printf("%d\t", squre[i][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);// �ָ�Ĭ�ϵ�������ɫ
			}
			else if (squre[i][j] != 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);//��ʾ��ɫ����
				printf("%d\t", squre[i][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);// �ָ�Ĭ�ϵ�������ɫ
			}
			else
			{
				printf("%d\t", squre[i][j]);
			}
		}
		printf("\n\n");	//ÿ���N���ͻ��� 
	}
	printf("\n");	//�����ɾͻ���
}

int Menu()
{
	int i;
	printf("��ѡ��\n");
	printf("1.��ʼ��Ϸ\n");
	printf("0.�˳�\n");
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
	//������ֱ���
	int x = 0, y = 0;
	int i = 0, j = 0;
	int random, count = 1;
	bool start = 1;

	//��ʼ������
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			squre[i][j] = 0;		//������λ�ö���0
		}
	}
	squre[0][0] = 1;				//��һ��λ����1

	//���������
	srand((unsigned)time(NULL));
	//��ʾ��ʼͼ��
	Display(x, y);

	printf("��ʼ��Ϸ���㵱ǰ�ڵ�1�У���1��\n");

	while (start)
	{
		if (x == 0 && y != 0 && squre[x][y - 1] != 0 && squre[x][y + 1] != 0 && squre[x + 1][y] != 0)
		{
			//��Χ����������������������ٽ���ѭ��
			start = 0;
		}

		if (y == 0 && x != 0 && squre[x - 1][y] != 0 && squre[x][y + 1] != 0 && squre[x + 1][y] != 0)
		{
			//��Χ����������������������ٽ���ѭ��
			start = 0;
		}

		if (x != 0 && y != 0 && squre[x][y - 1] != 0 && squre[x][y + 1] != 0 && squre[x - 1][y] != 0 && squre[x + 1][y] != 0)	//�ж��Ƿ���·����
		{
			//��Χ����������������������ٽ���ѭ��
			start = 0;
		}
		else
		{
			//��·������
			//0�ϣ�1�£�2��3��
			random = rand() % 4;		//����0-3�������

			switch (random)
			{
			case 0: x -= 1; break;
			case 1: x += 1; break;
			case 2: y -= 1; break;
			case 3: y += 1; break;
			}

			//�ж��Ƿ��ڿ�����λ���Ƿ�ռ
			if (x > 9 || y > 9 || x < 0 || y < 0 || squre[x][y] != 0)
			{
				//�������������ָ�������
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
				//�������������
				count++;
				squre[x][y] = count;
			}

			//��������ʾͼ��
			system("cls");
			Display(x, y);

			switch (random)
			{
				//0�ϣ�1�£�2��3��
			case 0: printf("������\n"); break;
			case 1: printf("������\n"); break;
			case 2: printf("������\n"); break;
			case 3: printf("������\n"); break;
			}
			printf("��ǰ��%d��%d�У������ǣ�%d\n", x + 1, y + 1, count);
		}
		//Sleep(500);	//��ͣ���


	//ѭ������
	//��������ʾ����ͼ��
		system("cls");
		Display(x, y);

		printf("��Ϸ����\n");
		printf("��%d�У�%d�н����������ǣ�%d\n", x + 1, y + 1, count);

		//ѯ���Ƿ�ʼ��Ϸ
		start = IfStartGame();
		if (start == 1)
		{
			//���start=1���������Ϸ
			Game();
		}
	}
}

int main()
{
	int judge=-1;
	//�˵�
	while (judge == -1)
	{
		judge = Menu();
	}
	if (judge == 1)
	{
		//������Ϸ
		Game();
	}
	
	system("pause");
	return 0;
}
