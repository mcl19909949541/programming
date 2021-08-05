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
void gotoxy(int x, int y);//类似于清屏函数
void HideCursor();//清除光标的函数
/*记录开始时间*/void start_time()
{
	startTime = clock();
	enemy_time_1 = clock();
}//记录开始时间
/*记录现在时间*/void now_time()
{
	endTime = clock();
	enemy_time_2 = clock();
}
/*判定游戏结束后的胜负*/void timejudge()
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
/*判定游戏是否应该结束*/void judge()
{
	for (k = 0; k < enemy_number; k++)
		if (a[enemy_x[k]][enemy_y[k]] == 1 || a[player_x][player_y] == 2)
		{
		con = 0;
		timejudge();
		}
}
/*因为多个敌人可能重合在一个坐标上，故给重合部分一个扰动*/void never_coincide()
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
/*敌人对玩家的追逐*/void chase()
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
/*初始化数据*/void startup()
{
	printf("请输入地图宽，长\n");
	scanf("%d%d", &bottom, &right);
	printf("请输入敌人个数\n");
	scanf("%d", &enemy_number);
	printf("请输入敌人速度(1最大，4最小)\n");
	scanf("%d", &enemy_speed);
	if (enemy_speed>4)
		enemy_speed = 4;
	start_time();
	for (i = top; i<bottom; i++)
	{
		for (j = left; j<right; j++)
		{
			if (i == 0 || i == bottom - 1)
				a[i][j] = 3;//打印上下边框  3控制

			else
			{
				if (j == 0 || j == right - 1)
					a[i][j] = 4;//打印左右边框  4控制
			}
		}
	}
	for (k = 0; k<enemy_number; k++)
	{
		enemy_x[k] = rand() % (bottom - 1) + 1;
		enemy_y[k] = rand() % (right - 1) + 1;//随机敌人初始位置坐标

	}
	player_x = rand() % (bottom - 1) + 1;
	player_y = rand() % (right - 1) + 1;//随机初始位置坐标
	HideCursor();
	system("cls");
}
/*与控制有关的更新*/void updatewithinput()
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
/*打印游戏内容*/void show()
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
/*与控制无关的更新*/void updatewithoutinput()
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
		a[enemy_x[k]][enemy_y[k]] = 2;//确定敌人位置 用2控制

	a[player_x][player_y] = 1;//确定玩家位置 用1控制
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
void gotoxy(int x, int y)//类似于清屏函数
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void HideCursor()//清除光标的函数
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//隐藏输入符号
}
