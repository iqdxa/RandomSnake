#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <time.h>
#include <windows.h>
#define N 12		//���������С������Χǽ

//ѯ���Ƿ��������
int IfStartGame()
{
	char judge;
	printf("����n����N�����������������������");
	scanf_s("%c", &judge,1);
	getchar();			//�ӿ���̨���ж�ȡ�ַ�
	if (judge == 'n' || judge == 'N')
	{
			return 0;	//������ѭ��
	}
	else
	{
			return 1;		//����ѭ��
	}
}

//��ӡͼ������
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

int Game_1()
{
	//������ֱ���
	int x = 1, y = 1;
	int i = 0, j = 0;
	int random = 0, count = 1;
	int start = 1;
	int judge = 0;	
	int squre[N][N];		//��������

	//��ʼ������
	for (i = 0; i <= N-1; i++)
	{
		for (j = 0; j <= N-1; j++)
		{
			squre[i][j] = 0;		//������λ�ö���0
			//�ñ߽�Ϊ-1
			squre[j][0] = -1;
			squre[0][j] = -1;
			squre[j][11] = -1;
			squre[11][j] = -1;
		}
	}
	squre[1][1] = 1;				//��һ��λ����1

	//���������
	srand((unsigned)time(NULL));
	//��������ʾͼ��
	system("cls");
	Display(x, y, squre);
	printf("��ʼ��Ϸ���㵱ǰ�ڵ�1�У���1��\n");

	do {
		if (squre[x][y - 1] != 0 && squre[x][y + 1] != 0 && squre[x + 1][y] != 0 && squre[x - 1][y] != 0)
		{
			//��Χ����������������������ٽ���ѭ��
			start = 0;
		}
		else
		{
			//��·������
			//0�ϣ�1�£�2��3��
			//����0-3�������
			random = rand() % 4;
			switch (random)
			{
			case 0: x -= 1; break;
			case 1: x += 1; break;
			case 2: y -= 1; break;
			case 3: y += 1; break;
			}

			//�ж��Ƿ��ڿ�����λ���Ƿ�ռ
			if (x > 10 || y > 10 || x < 1 || y < 1 || squre[x][y] != 0)
			{
				//�������������ָ�������
				switch (random)
				{
				case 0:x += 1; break;
				case 1:x -= 1; break;
				case 2:y += 1; break;
				case 3:y -= 1; break;
				}
				//���¿�ʼѭ��
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
			Display(x, y, squre);

			//�ж��ߵķ���
			switch (random)
			{
				//0�ϣ�1�£�2��3��
			case 0: printf("������\n"); break;
			case 1: printf("������\n"); break;
			case 2: printf("������\n"); break;
			case 3: printf("������\n"); break;
			}
			printf("��ǰ��%d��%d�У������ǣ�%d\n", x, y, count);
		}
		//Sleep(500);	//��ͣ���
	} while (start == 1);

	//ѭ������
	//��������ʾ����ͼ��
	system("cls");
	Display(x, y, squre);

	printf("��Ϸ����\n");
	printf("��%d�У�%d�н����������ǣ�%d\n", x, y, count);

	//ѯ���Ƿ�ʼ��Ϸ
	judge = IfStartGame();

	if (judge == 1)
	{
		//���judge=1���������Ϸ
		return 1;
	}
	else
	{
		//���judge=0����������ص��˵�
		return -1;
	}
}

int Choose(int n)
{
	int line = 0;
	switch (n)
	{
	case 1://�����һ����Ϸ
		//ѭ����Ϸ
		do {
			//�����һ����Ϸ
			//������1��������ڲ�ѭ����������-1�������ѭ��
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
	//����
	system("cls");
	printf("��ѡ��\n");
	printf("1.���̰����\n");
	printf("0.�˳�\n");
	judge=scanf_s("%d", &i);
	getchar();			//����������Ļس���
	if ((i == 1 || i == 0) && judge==1)
	{
		return i;
	}
	else
	{
		return -1;		//���벻��������������-1
	}
}

int main()
{
	int judge = -1;
	
	while (judge == -1)
	{
		//����˵����û��ڲ˵�����ѡ��
		judge = Menu();
		//����ĳ����Ϸ��������-1������ѭ��
		//��judgeΪ0���򷵻�0������ѭ��
		//��judgeΪ-1���򷵻�-1������ѭ��
		judge=Choose(judge);
	}
	system("pause");
	return 0;
}