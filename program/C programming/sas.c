#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LEN 15		/* 选手编号和选手代号最大数*/
#define N 50		/* 最大职业选手人数,*/

//功能函数申明
void menu ();
void  system_guide();
void  input();
void  correct ();
void  cut_off();
void  reflash();
void  save();
void  output();
void  forecast();
void assessment();
void valueassess();
void cooperate();


//全局变量
int n=0,m=0,start=1;


//结构体保存职业选手信息
struct player{
	char playerId[LEN];
	char playerName[LEN];
	int playerAge;
	char playerSex;
	float score[3];
}pla[N];


//0.指南函数
void menu ()
{
    	int num;
	printf(" \n\n                    \n\n");
	printf(" \n\n                    \n\n");
	printf(" \n\n                    \n\n");
	printf("  %%￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥%%\n");
	printf("        !!!!&&&&&&&&职业选手信息管理系统&&&&&&&&&!!!!  \n ");
	printf("  %%      +*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+* %%    \n");
	printf("  %%     *****************功能菜单**********************   %%   \n");
	printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
	printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+* %%   \n");
	printf("  %% 1.说明(使用前请仔细阅读）    2.添加职业选手信息         %%    \n");
	printf("  %%                                                      %%  \n");
	printf("  %% 3.修改职业选手信息           4.删除职业选手信息         %% \n");
	printf("  %%                                                      %%    \n");
	printf("  %% 5.清空职业选手信息           6.保存信息                 %%   \n");
	printf("  %%                                                    %%    \n");
	printf("  %% 7.输出信息                   8.预测职业选手综合信息     %%\n");
	printf("  %%                                                      %%     \n");
	printf("  %% 9.按序评价系统               10.价值评估系统            %%         \n");
    printf("  %%                                                      %%  \n");
	printf("  %%11.选手搭配系统               12.退出系统                %%    \n");
	printf("  %%*+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*  %% \n");
	printf("  %%￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥%% \ \n");
	printf("请选择菜单编号:");
	scanf("%d", &num);
	switch (num)
	{
	case 1:system_guide(); break;
	case 2:input(); break;
	case 3:correct(); break;
	case 4:cut_off(); break;
	case 5:reflash(); break;
	case 6:save(); break;
	case 7:output(); break;
	case 8:forecast(); break;
	case 9:assessment();break;
    case 10:valueassess();break;
	case 11:cooperate();break;
	case 12:
		start = 0;//定义为0后主函数直接退出
		printf("《《《《《《退出程序》》》》》》\n");
		break;
	default:printf("{{{{请在1-12之间选择}}}}\n");
     }

}

//1.说明函数
void  system_guide()
{     	printf("   ！\n");
     printf("  %%￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥%%\n");
    printf(" \n\n    《亲爱的用户，您好，欢迎使用最新开发的LOL职业选手综合管理系统：》\n\n");
	printf(" \n\n    《我们会依次介绍本程序的主要功能与使用提示》  \n\n");
	printf(" \n\n    《首先请按照程序顺序依次操作》                  \n\n");
    printf(" \n\n    《输入选手数据时请注意提示信息，请勿有不恰当输入》                 \n\n");
	printf(" \n\n    《输入后请及时按提示保存信息》                \n\n");
	printf(" \n\n    《我们特此推出本程序十分有效的功能，如下》              \n\n");
	printf(" \n\n    《预测职业选手综合信息 ，按序评价，价值评估，选手搭配》\n\n");
	printf(" \n\n    《相信会为各位教练提供帮助》             \n\n");
	printf(" \n\n    《此外，还有删除，显示，清空等专业功能，保证信息安全》             \n\n");//要让“教练”有好的体验一定要写充分
printf("  %%￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥%%\n");
  system("pause");
}

//2.添加函数
void input()
{
 int i = n, j, flag;
	printf("<<<<<请输入待增加的职业选手数>>>>>\n");
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
						printf("!!!!!!  !!!!该选手编号已存在!!!!!!!  !!!!!!!\n");
						flag = 1;
						break;
					}
				}
			}
			printf("  %%￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥%%\n");
			printf("请输入第%d 个职业选手的选手代号:\n", i+1);
			scanf("%s", pla[i].playerName);
			printf("请输入第%d 个职业选手的年龄:\n", i+1);
			scanf("%d", &pla[i].playerAge);
			printf("请输入第%d 个职业选手的性别(男为1，女请输入0）:\n", i+1);
			scanf(" %c", &pla[i].playerSex);
			printf("请输入第%d 个职业选手的生涯平均KDA(0-20)\n",i+1);
			scanf("%f", &pla[i].score[0]);
			printf("请输入第%d 个职业选手微操评分(0-500):\n", i+1);
			scanf("%f", &pla[i].score[1]);
			printf("请输入第%d 个职业选手的运营评分(0-500):\n", i+1);
			printf("  %%￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥%%\n");
			scanf("%f", &pla[i].score[2]);
			if (flag==0){
				i++;
			}
		} while (i<n + m);
	}
		n += m;
		printf("职业选手信息增加完毕！！！\n");
		system("pause");

}

//3.修改函数
void correct ()
{
   int i, item, num = -1;
	char sex1, s1[LEN], s2[LEN]; /* 以选手代号和选手编号最长长度为准*/
	float score1;
	printf("请输入要要修改的职业选手的选手编号:\n");
	scanf("%s", s1);
	for (i = 0; i < n; i++){
		if (strcmp(pla[i].playerId, s1) == 0){/*比较字符串是否相等*/
			num = i;
			printf("  %%￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥%%\n");
			printf("------------------\n");
			printf("1.修改选手代号\n");
			printf("2.修改年龄\n");
			printf("3.修改性别\n");
			printf("4.修改KPA\n");
			printf("5.修改微操评分\n");
			printf("6.修改运营评分\n");
			printf("7.退出本菜单\n");
			printf("------------------\n");
			printf("  %%￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥%%\n");
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
					printf("请输入新的微操评分:\n");
					scanf("%f", &score1);
					pla[num].score[1] = score1;
					break;
				case 6:
					printf("请输入新的运营评分:\n");
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

//4.删除函数
void  cut_off()
{
  int i, j, flag = 0;
	char s1[LEN];
	printf("  %%￥￥￥￥￥￥￥￥￥￥￥￥￥%%\n");
	printf("请输入要删除职业选手的选手编号:\n");
	printf("  %%￥￥￥￥￥￥￥￥￥￥￥￥%%\n");
	scanf("%s", s1);
	for (i = 0; i < n; i++){
		if (strcpy(pla[i].playerId, s1) == 0){
			flag = 1;
			//要删除职业选手后面的职业选手往前移一位
			for (j = i; j <=n ; j++){
				pla[j] = pla[j + 1];
			}
		}
	}
		//查找失败
		if (flag==0){
			printf("该选手编号不存在!!!\n");
		}
		if (1 == flag){
			printf("删除成功！！！");
			//删除成功，职业选手人数减1
			n--;
		}
		system("pause");
}

//5.清空函数
void  reflash()
{
char filename[LEN];
	int i = 0;
	printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
	printf("请输入要刷新职业选手信息的文件名：\n");
    printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
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

//6.保存函数
void  save()
{
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

//7.输出函数
void  output()
{
int i;
	printf("共有%d位职业选手的信息:\n", n);
	if (0 != n)
	{   printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
		printf("职业选手选手编号 \职业选手选手代号 \t年龄   \t性别   \tAPM\微操评分 \运营评分\n");
	    printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
		for (i = 0; i<n; i++)
		{
			printf("%s \t%s \t%d   \t%c   \t%.1f\t%.1f \t%.1f\n", pla[i].playerId, pla[i].playerName, pla[i].playerAge, pla[i].playerSex, pla[i].score[0],pla[i].score[1],pla[i].score[2]);
		}
	}
	system("pause");
}
//8.预测函数
void  forecast()
{
int i,sum;
	printf("共有%d位职业选手的信息:\n", n);
	if (0 != n)
	{  printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
		printf("职业选手综合等级\n");
		printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
		for (i = 0; i<n; i++)
		{    sum= (pla[i].score[0]+ pla[i].score[1]+ pla[i].score[2])/3;
			if(0<=sum&&sum<500) printf("SUCK\n");
			if(500<sum&&sum<=1000) printf("MODIOCRE\n");
			if(1000<sum&&sum<=1500) printf("INCREDIBLE\n");
		}
	}
	system("pause");
}
//9.精准数据排序
void assessment()
{   int i,j,k;
     struct player example;
printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
printf("有以下%d个LOL职业选手按KDA-> 微操水平-> 运营水平 由强到弱依次排序\n",&n);
printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
     for(i=0;i<n-1;i++)
       for(j=0;j<n-1-i;j++)
       {
           if(pla[i].score[0]<pla[i].score[0])
           {
               example=pla[i];
               pla[i]=pla[i+1];
               pla[i+1]=example;
           }
           else if(pla[i].score[0]==pla[i].score[0]&&pla[i].score[1]<pla[i].score[1])
           {
               example=pla[i];
               pla[i]=pla[i+1];
               pla[i+1]=example;
           }
           else if(pla[i].score[0]==pla[i].score[0]&&pla[i].score[1]==pla[i].score[1]&&pla[i].score[2]<pla[i].score[2])
           {
               example=pla[i];
               pla[i]=pla[i+1];
               pla[i+1]=example;
           }


       }
        for (i = 0; i<n; i++)
		{
			printf("%s \t%s \t%d   \t%c   \t%.1f\t%.1f \t%.1f\n", pla[i].playerId, pla[i].playerName, pla[i].playerAge, pla[i].playerSex, pla[i].score[0],pla[i].score[1],pla[i].score[2]);
		}


    system("pause");
}
void cooperate()
{
    int sumage,varage,sumsex,varsex,sumKDA,varKDA,sumweidcao,varweicao,sumyunying,varyunying;
    int operatepercent;//方差和
    printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
printf("由计算输出以下选手间配合程度\n");
printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
    for(int t=0;t<m;t++){
        sumage=sumage+pla[t].playerAge;//求和
    }
    sumage=sumage/m;//平均值
    for(int t=0;t<m;t++){
        varage=varage+(pla[t].playerAge-sumage)*(pla[t].playerAge-sumage);//平方和
    }
    varage=varage/m;//方差

    for(int t=0;t<m;t++){
        sumsex=sumsex+pla[t].playerSex;
    }
    sumsex=sumsex/m;
    for(int t=0;t<m;t++){
        varsex=varsex+(pla[t].playerSex-sumsex)*(pla[t].playerSex-sumsex);
    }
    varsex=varsex/m;

    for(int t=0;t<m;t++){
        sumKDA=sumKDA+pla[t].score[0];
    }
    sumKDA=sumKDA/m;
    for(int t=0;t<m;t++){
        varKDA=varKDA+(pla[t].score[0]-sumKDA)*(pla[t].score[0]-sumKDA);
    }
    varKDA=varKDA/m;

    for(int t=0;t<m;t++){
        sumweidcao=sumweidcao+pla[t].score[1];
    }
    sumweidcao=sumweidcao/m;
    for(int t=0;t<m;t++){
        varweicao=varweicao+(pla[t].score[1]-sumweidcao)*(pla[t].score[1]-sumweidcao);
    }
    varweicao=varweicao/m;

    for(int t=0;t<m;t++){
        sumyunying=sumyunying+pla[t].score[2];
    }
    sumyunying=sumyunying/m;
    for(int t=0;t<m;t++){
        varyunying=varyunying+(pla[t].score[2]-sumyunying)*(pla[t].score[2]-sumyunying);
    }
    varyunying=varyunying/m;

    operatepercent=varage+varKDA+varsex+varweicao+varyunying;
    printf("所有选手配合程度:%d",operatepercent);
    system("pause");
}
void valueassess()
{
    double valuescore = 0, a[100] = {0}, b[100] = {0};
    int i;
    for(i = 0; i < n; i++)
    {
        if(pla[i].playerAge <= 18) a[i] = 3;
            else if(pla[i].playerAge <= 21) a[i] = 2;
            else a[i] = 1;
        if(pla[i].playerSex == '1') b[i] = 1;
            else b[i] = 0;
        int aver = 0;
        aver = (pla[i].score[1] * 0.6 + pla[i].score[2] * 0.4) / 100;
        valuescore = a[i] + b[i] + pla[i].score[0] + aver;
        printf("第%d号选手的综合价值评估分数为:%lf\n", i + 1, valuescore);
    }
    system("pause");
}
//主函数
int main()
{
	while (start)
	{
		menu();
	}
	system("pause");
	return 0;

}


