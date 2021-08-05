#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LEN 15		/* 选手编号和选手代号最大字符数,实际请更改*/
#define N 50		/* 最大职业选手人数,实际请更改*/

int k = 1, n = 0, m = 0;/* n代表当前记录的职业选手人数*/

//函数声明
void readfile();
void seek();
void modify();
void insert();
void del();
void display();
void save();
void menu();

//结构体保存职业选手信息
struct player{
	char playerId[LEN+1];
	char playerName[LEN+1];
	int playerAge;
	char playerSex;
	float score[3];
}pla[N];

//主函数
int main()
{
	while (k)
	{
		menu();
	}
	system("pause");
	return 0;
}
void menu()/* 界面*/
{
	int num;
	printf(" \n\n                    \n\n");
	printf("  ******************************************************\n\n");
	printf("  *                职业选手信息管理系统                    *\n \n");
	printf("  ******************************************************\n\n");
	printf("*********************系统功能菜单*************************       \n");
	printf("     ----------------------   ----------------------   \n");
	printf("     *********************************************     \n");
	printf("     * 0.系统帮助及说明  * *  1.刷新职业选手信息   *     \n");
	printf("     *********************************************     \n");
	printf("     * 2.查询职业选手信息    * *  3.修改职业选手信息   *     \n");
	printf("     *********************************************     \n");
	printf("     * 4.增加职业选手信息    * *  5.按选手编号删除信息 *     \n");
	printf("     *********************************************     \n");
	printf("     * 6.显示当前信息    * *  7.保存当前职业选手信息*     \n");
	printf("     ********************** **********************     \n");
	printf("     * 8.退出系统        *                            \n");
	printf("     **********************                            \n");
	printf("     ----------------------   ----------------------                           \n");
	printf("请选择菜单编号:");
	scanf("%d", &num);
	switch (num)
	{
	case 0:help(); break;
	case 1:flush(); break;
	case 2:seek(); break;
	case 3:modify(); break;
	case 4:insert(); break;
	case 5:del(); break;
	case 6:display(); break;
	case 7:save(); break;
	case 8:
		k = 0;
		printf("即将退出程序!\n");
		break;
	default:printf("请在0-8之间选择\n");
	}
}


//系统帮助函数
void help()
{
	printf("   ！\n");
	printf("初次进入系统后,请先选择增加职业选手信息;\n");
	printf("按照菜单提示键入数字代号;\n");
	printf("增加职业选手信息后,切记保存;\n");
	printf("谢谢您的使用！\n");
}

//刷新文件
int flush(){
	char filename[LEN + 1];
	int i = 0;
	printf("请输入要刷新职业选手信息的文件名：\n");
	scanf("%s", filename);
	int j = 0;
	FILE * fp;
	if ((fp = fopen(filename, "r")) == NULL) return 0;
	//从文件读取信息
	while (fscanf(fp, "%s %s %s %d %d %d %d ", &pla[j].playerId, &pla[j].playerName, &pla[j].playerAge, &pla[j].playerSex, &pla[j].score[0], &pla[j].score[1], &pla[j].score[2]) == 7) {
		j++;
	}
	n = j;
	printf("刷新成功!!!");
	return n;
}

//查找职业选手信息
void seek() /*查找*/
{
	int i, item, flag;
	char s1[21]; /* 以选手代号和选手编号最长长度+1为准*/
	printf("------------------\n");
	printf("-----1.按选手编号查询-----\n");
	printf("-----2.按选手代号查询-----\n");
	printf("-----3.退出本菜单-----\n");
	printf("------------------\n");
	while (1)
	{
		printf("请选择子菜单编号:");
		scanf("%d", &item);
		flag = 0;
		switch (item)
		{
		case 1:
			printf("请输入要查询的职业选手的选手编号:\n");
			scanf("%s", s1);
			for (i = 0; i<n; i++)
			if (strcmp(s1,pla[i].playerId) == 0)
			{
				flag = 1;
				printf("职业选手选手编号\职业选手选手代号\t年龄\t性别\APM\微操评分\运营评分\n");
				printf("--------------------------------------------------------------------\n");
				printf("%s\t%s\t%d\t%6\t%.1f\t%.1f\t%.1f\n", pla[i].playerId,pla[i].playerName,pla[i].playerAge,pla[i].playerSex,pla[i].score[0],pla[i].score[1],pla[i].score[2]);
			}
			if (0 == flag)
				printf("该选手编号不存在！\n"); break;
		case 2:
			printf("请输入要查询的职业选手的选手代号:\n");
			scanf("%s", s1);
			for (i = 0; i<n; i++)
			if (strcmp(pla[i].playerName, s1) == 0)
			{
				flag = 1;
				printf("职业选手选手编号\职业选手选手代号\t年龄\t性别\tAPM\微操评分\运营评分\n");
				printf("--------------------------------------------------------------------\n");
				printf("%s\t%s\t%d\t%c\t%.1f\t%.1f\t%.1f\n", pla[i].playerId, pla[i].playerName, pla[i].playerAge, pla[i].playerSex, pla[i].score[0], pla[i].score[1], pla[i].score[2]);
			}
			if (0 == flag)
				printf("该选手代号不存在！\n"); break;
		case 3:return;
		default:printf("请在1-3之间选择\n");
		}
	}
}

//修改职业选手信息
void modify() /*修改信息*/
{
	int i, item, num = -1;
	char sex1, s1[LEN + 1], s2[LEN + 1]; /* 以选手代号和选手编号最长长度+1为准*/
	float score1;
	printf("请输入要要修改的职业选手的选手编号:\n");
	scanf("%s", s1);
	for (i = 0; i < n; i++){
		if (strcmp(pla[i].playerId, s1) == 0){/*比较字符串是否相等*/
			num = i;
			printf("------------------\n");
			printf("1.修改选手代号\n");
			printf("2.修改年龄\n");
			printf("3.修改性别\n");
			printf("4.修改APM\n");
			printf("5.修改高等数学成绩\n");
			printf("6.修改大学英语成绩\n");
			printf("7.退出本菜单\n");
			printf("------------------\n");
			while (1)
			{
				printf("请选择子菜单编号:");
				scanf("%d", &item);
				switch (item)
				{
				case 1:
					printf("请输入新的选手代号:\n");
					scanf("%s", s2);
					strcpy(pla[num].playerName, s2);
					break;
				case 2:
					printf("请输入新的年龄:\n");
					scanf("%d", pla[num].playerAge);
					break;
				case 3:
					printf("请输入新的性别:\n");
					scanf("%s", &sex1);
					pla[i].playerSex = sex1;
					break;
				case 4:
					printf("请输入新的APM:\n");
					scanf("%f", &score1);
					pla[num].score[0] = score1;
					break;
				case 5:
					printf("请输入新的高等数学成绩:\n");
					scanf("%f", &score1);
					pla[num].score[1] = score1;
					break;
				case 6:
					printf("请输入新的大学英语成绩:\n");
					scanf("%f", &score1);
					pla[num].score[2] = score1;
					break;
				case 7:	return;
				default:printf("请在1-7之间选择\n");
				}
			}
			printf("修改完毕！请及时保存！\n");
		}
		else{
			printf("没有该职业选手选手编号!!!");
		}
	}
}



//添加职业选手信息函数
void insert() /*插入函数*/
{
	int i = n, j, flag;
	printf("请输入待增加的职业选手数:\n");
	scanf("%d", &m);
	if (m > 0){
		do
		{
			flag = 1;
			while (flag)
			{
				flag = 0;
				printf("请输入第%d位职业选手的选手编号:\n", i + 1);
				scanf("%s", pla[i].playerId);
				for (j = 0; j < i; j++){
					if (strcmp(pla[i].playerId, pla[j].playerId) == 0){
						printf("该选手编号已存在，请重新输入！\n");
						flag = 1;
						break;
					}
				}
			}
			printf("请输入第%d 个职业选手的选手代号:\n", i+1);
			scanf("%s", pla[i].playerName);
			printf("请输入第%d 个职业选手的年龄:\n", i+1);
			scanf("%d", &pla[i].playerAge);
			printf("请输入第%d 个职业选手的性别:\n", i+1);
			scanf(" %c", &pla[i].playerSex);
			printf("请输入第%d 个职业选手的APM\n",i+1);
			scanf("%f", &pla[i].score[0]);
			printf("请输入第%d 个职业选手的高等数学成绩:\n", i+1);
			scanf("%f", &pla[i].score[1]);
			printf("请输入第%d 个职业选手的大学英语成绩:\n", i+1);
			scanf("%f", &pla[i].score[2]);
			if (0 == flag){
				i++;
			}
		} while (i<n + m);
	}
		n += m;
		printf("职业选手信息增加完毕！！！\n");
		system("pause");
}

//删除职业选手信息函数
void del()
{
	int i, j, flag = 0;
	char s1[LEN + 1];
	printf("请输入要删除职业选手的选手编号:\n");
	scanf("%s", s1);
	for (i = 0; i < n; i++){
		if (strcpy(pla[i].playerId, s1) == 0){
			flag = 1;
			//要删除职业选手后面的职业选手往前移一位
			for (j = i; j < n - 1; j++){
				pla[j] = pla[j + 1];
			}
		}
	}
		//查找失败
		if (0 == flag){
			printf("该选手编号不存在!!!\n");
		}
		if (1 == flag){
			printf("删除成功！！！");
			//删除成功，职业选手人数减1
			n--;
		}
		system("pause");
}
void save(){
	int i;
	FILE *fp;
	char filename[LEN + 1];
	printf("请输入要保存的文件名：\n");
	scanf("%s", filename);
	fp = fopen(filename, "w");
	for (i = 0; i < n; i++){
		fprintf(fp, "%s%s%d%c%.lf%.lf%.lf\n", pla[i].playerId, pla[i].playerName, pla[i].playerAge, pla[i].playerSex,
			pla[i].score[0], pla[i].score[1], pla[i].score[2]);
	}
	printf("保存成功！！！\n");
	fclose(fp);
	system("pause");
}

//显示全部数据信息
void display()
{
	int i;
	printf("共有%d位职业选手的信息:\n", n);
	if (0 != n)
	{
		printf("职业选手选手编号 \职业选手选手代号 \t年龄   \t性别   \tAPM\微操评分 \运营评分\n");
		printf("--------------------------------------------------------------------\n");
		for (i = 0; i<n; i++)
		{
			printf("%s \t%s \t%d   \t%c   \t%.1f\t%.1f \t%.1f\n", pla[i].playerId, pla[i].playerName, pla[i].playerAge, pla[i].playerSex, pla[i].score[0],pla[i].score[1],pla[i].score[2]);
		}
	}
	system("pause");
}

