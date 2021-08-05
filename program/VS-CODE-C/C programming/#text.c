#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>//windows���ͷ�ļ�
#include <time.h>
#include <conio.h>//����̨�������ͷ�ļ�

#ifndef __cplusplus

typedef char bool;
#define false 0
#define true  1

#endif

//������ƶ�������̨��(x,y)����㴦
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



#define SNAKESIZE 100//�ߵ�����������
#define MAPWIDTH 78//����
#define MAPHEIGHT 24//�߶�

//ʳ�������
struct {
	int x;
	int y;
}food;

//�ߵ��������
struct {
	int speed;//���ƶ����ٶ�
	int len;//�ߵĳ���
	int x[SNAKESIZE];//���������ÿһ��С������x������
	int y[SNAKESIZE];//���������ÿһ��С������y������

}snake;

//������Ϸ�߿�
void drawMap();
//�������ʳ��
void createFood();
//��������
void keyDown();
//�ߵ�״̬
bool snakeStatus();
//�ӿ���̨�ƶ����
void gotoxy(int x, int y);

int key = 72;//��ʾ���ƶ��ķ���72Ϊ���¡�����������������

//�����ж����Ƿ�Ե���ʳ���һ������Ҫ���漰���Ƿ���������ƶ���Ч���Լ�����������Ч��
int changeFlag = 0;

int sorce = 0;//��¼��ҵĵ÷�

int i;
void drawMap()
{
	//��ӡ���±߿�
	for (i = 0; i <= MAPWIDTH; i += 2)//i+=2����Ϊ����ռ�õ�������λ��
	{
		//������ƶ����ε�(i,0)����ӡ�ϱ߿�
		gotoxy(i, 0);
		printf("��");
		//������ƶ����ε�(i,MAPHEIGHT)����ӡ�±߿�
		gotoxy(i, MAPHEIGHT);
		printf("��");
	}

	//��ӡ���ұ߿�
	for (i = 1; i < MAPHEIGHT; i++)
	{
		//������ƶ����ε�(0,i)����ӡ��߿�
		gotoxy(0, i);
		printf("��");
		//������ƶ����ε�(MAPWIDTH, i)����ӡ��߿�
		gotoxy(MAPWIDTH, i);
		printf("��");
	}

	//������ɳ���ʳ��
	while (1)
	{
		srand((unsigned int)time(NULL));
		food.x = rand() % (MAPWIDTH - 4) + 2;
		food.y = rand() % (MAPHEIGHT - 2) + 1;
		//���ɵ�ʳ����������ż����ͳ���ʱ��ͷ�����������żһ�£���Ϊһ���ַ�ռ�����ֽ�λ�ã�����һ��
		//�ᵼ�³�ʳ���ʱ��ֻ�Ե�һ��
		if (food.x % 2 == 0)
			break;
	}
	//������Ƶ�ʳ������괦��ӡʳ��
	gotoxy(food.x, food.y);
	printf("*");

	//��ʼ���ߵ�����
	snake.len = 3;
	snake.speed = 200;

	//����Ļ�м�������ͷ
	snake.x[0] = MAPWIDTH / 2 + 1;//x����Ϊż��
	snake.y[0] = MAPHEIGHT / 2;
	//��ӡ��ͷ
	gotoxy(snake.x[0], snake.y[0]);
	printf("��");

	//���ɳ��Ե�����
	for (i = 1; i < snake.len; i++)
	{
		//�����Ĵ�ӡ�������겻�䣬������Ϊ��һ������������ֵ+2
		snake.x[i] = snake.x[i - 1] + 2;
		snake.y[i] = snake.y[i - 1];
		gotoxy(snake.x[i], snake.y[i]);
		printf("��");
	}
	//��ӡ�������󽫹���Ƶ���Ļ���Ϸ�����������������һֱ��˸
	gotoxy(MAPWIDTH - 2, 0);
	return;
}

void keyDown()
{
	int pre_key = key;//��¼ǰһ�������ķ���
	if (_kbhit())//����û������˼����е�ĳ����
	{
		fflush(stdin);//��ջ��������ַ�

		//getch()��ȡ�������ʱ�򣬻᷵�����Σ���һ�ε��÷���0����224���ڶ��ε��÷��صĲ���ʵ��ֵ
		key = _getch();//��һ�ε��÷��صĲ���ʵ��ֵ
		key = _getch();//�ڶ��ε��÷���ʵ��ֵ
	}

	/*
	*���ƶ�ʱ���Ȳ�ȥ��β��һ��
	*changeFlagΪ0������ʱû�гԵ�ʳ����ÿ��һ����Ҫ��������β���Դ�Ӫ��һ���ƶ���Ч��
	*Ϊ1�����Ե���ʳ��Ͳ���Ҫ������β���Դ�Ӫ��һ������������Ч��
	*/
	if (changeFlag == 0)
	{
		gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
		printf("  ");//����β������ո񼴲�ȥ��β
	}

	//���ߵ�ÿһ��������ǰ�ƶ�һ�ڣ���ͷ���⣩
	for (i = snake.len - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}

	//�ߵ�ǰ�ƶ��ķ����ܺ�ǰһ�εķ����෴�������������ߵ�ʱ����ֱ�Ӱ��Ҽ�������
	//�����ǰ�ƶ������ǰһ�η����෴�Ļ����ѵ�ǰ�ƶ��ķ����Ϊǰһ�εķ���
	if (pre_key == 72 && key == 80)
		key = 72;
	if (pre_key == 80 && key == 72)
		key = 80;
	if (pre_key == 75 && key == 77)
		key = 75;
	if (pre_key == 77 && key == 75)
		key = 77;

	/**
	*����̨����������������
	*��������72
	*��������80
	*��������75
	*��������77
	*/

	//�ж���ͷӦ�����ĸ������ƶ�
	switch (key)
	{
	case 75:
		snake.x[0] -= 2;//����
		break;
	case 77:
		snake.x[0] += 2;//����
		break;
	case 72:
		snake.y[0]--;//����
		break;
	case 80:
		snake.y[0]++;//����
		break;
	}
	//��ӡ����ͷ
	gotoxy(snake.x[0], snake.y[0]);
	printf("��");
	gotoxy(MAPWIDTH - 2, 0);
	//����Ŀǰû�гԵ�ʳ�changFlagֵΪ0
	changeFlag = 0;
	return;
}

void createFood()
{
	if (snake.x[0] == food.x && snake.y[0] == food.y)//��ͷ����ʳ��
	{
		//��ͷ����ʳ�ＴΪҪ�Ե����ʳ���ˣ������Ҫ�ٴ�����һ��ʳ��
		while (1)
		{
			int flag = 1;
			srand((unsigned int)time(NULL));
			food.x = rand() % (MAPWIDTH - 4) + 2;
			food.y = rand() % (MAPHEIGHT - 2) + 1;

			//������ɵ�ʳ�ﲻ�����ߵ�������
			for (i = 0; i < snake.len; i++)
			{
				if (snake.x[i] == food.x && snake.y[i] == food.y)
				{
					flag = 0;
					break;
				}
			}
			//������ɵ�ʳ�ﲻ�ܺ�����Ϊ������Ҳ������������������������
			if (flag && food.x % 2 == 0)
				break;
		}

		//����ʳ��
		gotoxy(food.x, food.y);
		printf("*");

		snake.len++;//�Ե�ʳ��������ȼ�1
		sorce += 10;//ÿ��ʳ���10��
		snake.speed -= 5;//���ųԵ�ʳ��Խ��Խ�࣬�ٶȻ�Խ��Խ��
		changeFlag = 1;//����Ҫ����Ϊ�Ե���ʳ��Ͳ����ٲ�����β����һ�ڣ��Դ������������������Ч��
	}
	return;
}

bool snakeStatus()
{
	//��ͷ�������±߽磬��Ϸ����
	if (snake.y[0] == 0 || snake.y[0] == MAPHEIGHT)
		return false;
	//��ͷ�������ұ߽磬��Ϸ����
	if (snake.x[0] == 0 || snake.x[0] == MAPWIDTH)
		return false;
	//��ͷ������������Ϸ����
	for (i = 1; i < snake.len; i++)
	{
		if (snake.x[i] == snake.x[0] && snake.y[i] == snake.y[0])
			return FALSE;
	}
	return true;
}

int main()
{
    drawMap();
	while (1)
	{
		keyDown();
		if (!snakeStatus())
			break;
		createFood();
		Sleep(snake.speed);
	}

	gotoxy(MAPWIDTH / 2, MAPHEIGHT / 2);
	printf("Game Over!\n");
	gotoxy(MAPWIDTH / 2, MAPHEIGHT / 2 + 1);
	printf("������Ϸ�÷�Ϊ��%d\n", sorce);
	Sleep(5000);
	return 0;
}


