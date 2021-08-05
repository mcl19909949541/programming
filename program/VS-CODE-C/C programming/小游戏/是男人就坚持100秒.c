#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
int a[100][100];
int enemy_x[50];int enemy_y[50];
int enemy_number;
int i, j, k;
int top = 0, bottom, right, left = 0;
int player_x, player_y;
int con = 1;
float startTime, endTime;
int enemy_time_1, enemy_time_2;
int enemy_speed;
void gotoxy(int x, int y);//��������������
void HideCursor();//������ĺ���
/*��¼��ʼʱ��*/void start_time()
{
	startTime = clock();
	enemy_time_1 = clock();
}//��¼��ʼʱ��
/*��¼����ʱ��*/void now_time()
{
	endTime = clock();
	enemy_time_2 = clock();
}
/*�ж���Ϸ�������ʤ��*/void timejudge()
{
	if ((endTime - startTime) / 1000.0 <= 100)
	{
		printf("You lose!!!\n");
		for (int s = 0; s<3; s++)
			system("pause");
	}
	else
	{
		system("cls");
		printf("You win!!!\n");
		for (int w = 0; w<5; w++)
			system("pause");
	}
}
/*�ж���Ϸ�Ƿ�Ӧ�ý���*/void judge()
{
	for (k = 0; k < enemy_number; k++)
		if (a[enemy_x[k]][enemy_y[k]] == 1 || a[player_x][player_y] == 2)
		{
		con = 0;
		timejudge();
		}
}
/*��Ϊ������˿����غ���һ�������ϣ��ʸ��غϲ���һ���Ŷ�*/void never_coincide()
{
	int a, b;
	for (a = 0; a<enemy_number; a++)
		for (b = 0; b<enemy_number; b++)
			if (a != b)
				if (enemy_x[a] == enemy_x[b] && enemy_y[a] == enemy_y[b])
				{
		enemy_x[a] += rand() % 2 - 1;
		enemy_y[a] += rand() % 2 - 1;
				}
}
/*���˶���ҵ�׷��*/void chase()
{
	for (k = 0; k < enemy_number; k++)
	{
		if (enemy_x[k]>player_x)
			enemy_x[k]--;
		else if (enemy_x[k]<player_x)
			enemy_x[k]++;
		if (enemy_y[k]>player_y)
			enemy_y[k]--;
		else if (enemy_y[k]<player_y)
			enemy_y[k]++;
	}
}
/*��ʼ������*/void startup()
{
	printf("�������ͼ����\n");
	scanf("%d%d", &bottom, &right);
	printf("��������˸���\n");
	scanf("%d", &enemy_number);
	printf("����������ٶ�(1���4��С)\n");
	scanf("%d", &enemy_speed);
	if (enemy_speed>4)
		enemy_speed = 4;
	start_time();
	for (i = top; i<bottom; i++)
	{
		for (j = left; j<right; j++)
		{
			if (i == 0 || i == bottom - 1)
				a[i][j] = 3;//��ӡ���±߿�  3����

			else
			{
				if (j == 0 || j == right - 1)
					a[i][j] = 4;//��ӡ���ұ߿�  4����
			}
		}
	}
	for (k = 0; k<enemy_number; k++)
	{
		enemy_x[k] = rand() % (bottom - 1) + 1;
		enemy_y[k] = rand() % (right - 1) + 1;//������˳�ʼλ������

	}
	player_x = rand() % (bottom - 1) + 1;
	player_y = rand() % (right - 1) + 1;//�����ʼλ������
	HideCursor();
	system("cls");
}
/*������йصĸ���*/void updatewithinput()
{
	if (kbhit())
	{
		if ((GetAsyncKeyState(0x41) & 0x8000) ? 1 : 0)//a
			player_y -= 2;
		else	if ((GetAsyncKeyState(0x44) & 0x8000) ? 1 : 0)//d
			player_y += 2;
		if ((GetAsyncKeyState(0x57) & 0x8000) ? 1 : 0)//w
			player_x -= 2;
		else if ((GetAsyncKeyState(0x53) & 0x8000) ? 1 : 0)//s
			player_x += 2;
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	if (player_y <= left + 1)
		player_y = left + 1;
	else if (player_y >= right - 2)
		player_y = right - 2;
	if (player_x <= top)
		player_x = top + 1;
	else if (player_x >= bottom - 2)
		player_x = bottom - 2;

	fflush(stdin);
}
/*��ӡ��Ϸ����*/void show()
{
	gotoxy(0, 0);
	for (i = 0; i<bottom; i++)
	{
		for (j = 0; j<right; j++)
		{
			if (a[i][j] == 0)
				printf(" ");
			else if (a[i][j] == 1)
				printf("@");
			else if (a[i][j] == 2)
				printf("#");
			else if (a[i][j] == 3)
				printf("-");
			else if (a[i][j] == 4)
				printf("|");

		}
		printf("\n");
	}
	now_time();
	printf("\n");
	printf("%.3f s\n", (endTime - startTime) / 1000.0);
}
/*������޹صĸ���*/void updatewithoutinput()
{
	for (i = top + 1; i<bottom - 1; i++)
	{
		for (j = left + 1; j<right - 1; j++)
		{
			a[i][j] = 0;
		}
	}
	for (k = 0; k<enemy_number; k++)
	{
		if (enemy_y[k] <= left + 1)
			enemy_y[k] = left + 1;
		if (enemy_y[k] >= right - 2)
			enemy_y[k] = right - 2;
		if (enemy_x[k] <= top)
			enemy_x[k] = top + 1;
		if (enemy_x[k] >= bottom - 2)
			enemy_x[k] = bottom - 2;
	}
	for (k = 0; k<enemy_number; k++)
		a[enemy_x[k]][enemy_y[k]] = 2;//ȷ������λ�� ��2����

	a[player_x][player_y] = 1;//ȷ�����λ�� ��1����
	if (((enemy_time_2 - enemy_time_1) % enemy_speed) == 0)
		chase();
	judge();
	never_coincide();
}
int main()
{
	startup();
	while (con)
	{
		show();
		updatewithoutinput();
		updatewithinput();
	}
}
void gotoxy(int x, int y)//��������������
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void HideCursor()//������ĺ���
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//�����������
}
