#include<stdio.h>//标准输入输出库
#include<stdlib.h>//C语言函数库
#include<string.h>//字符函数库

#define LEN 15		/* 选手编号和选手代号最大数*/
#define N 50		/* 最大职业选手人数,*/

//功能函数申明
void  menu ();
void  system_guide();
void  input();
void  correct ();
void  cut_off();
void  reflash();
void  save();
void  output();
void  forecast();
void  assessment();
void  valueassess();
void  cooperate();
void  check();
void  agreement();
void  money();
void  competition();
void  exchangepla();
void  investorassess();
void  investindi();
void  investgroup();


//全局变量
int n = 0, m = 0, start = 1, id, allow;


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
	printf("  %%￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥%%         \n");
	printf("          !!!!&&&&&&&&职业选手信息管理系统&&&&&&&&&!!!!              \n");
	printf("  %%      +*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*         %%   \n");
	printf("  %%     *****************功能菜单**********************        %%   \n");
	printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*     %%   \n");
	printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*     %%   \n");
	printf("  %% 1.说明(使用前请仔细阅读）    2.添加职业选手信息            %%   \n");
	printf("  %%                                                            %%   \n");
	printf("  %% 3.修改职业选手信息           4.删除职业选手信息            %%   \n");
	printf("  %%                                                            %%   \n");
	printf("  %% 5.清空职业选手信息           6.保存信息                    %%   \n");
	printf("  %%                                                            %%   \n");
	printf("  %% 7.输出信息                   8.预测职业选手综合信息        %%   \n");
	printf("  %%                                                            %%   \n");
	printf("  %% 9.按序评价系统               10.价值评估系统               %%   \n");
    printf("  %%                                                            %%   \n");
	printf("  %% 11.选手搭配系统              12.教练专属比赛情况查看系统   %%   \n");
	printf("  %%                                                            %%   \n");
	printf("  %% 13.教练专属选手交易参考系统  14.投资人专属价值预估系统     %%   \n");
	printf("  %%                                                            %%   \n");
	printf("  %% 15.投资人专属评估系统        16.投资人专属组合投资系统     %%   \n");
	printf("  %%                                                            %%   \n");
	printf("  %% 17.投资人专属个人投资系统                                  %%   \n");
	printf("  %%                                                            %%   \n");
	printf("  %% 18.退出系统+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+**%%   \n");
	printf("  %%￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥%%   \n");
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
	case 12:competition();break;
	case 13:exchangepla();break;
	case 14:investorassess();break;
    case 15:money();break;
    case 16:investgroup();break;
    case 17:investindi();break;
	case 18:
		start = 0;//定义为0后主函数直接退出
		printf("《《《《《《退出程序》》》》》》\n");
		break;
	default:printf("{{{{请在1-18之间选择}}}}\n");
     }

}

//1.说明函数
void  system_guide()
{     if(id==0){	printf("   ！\n");
     printf("  %%￥￥￥￥￥￥￥教练须知￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥%%\n");
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
}
else if(id==1){
    printf("  %%￥￥￥￥￥￥￥投资人须知￥￥￥￥￥￥￥￥￥￥￥￥%%\n");
    printf(" \n\n    《亲爱的投资人，您好，欢迎使用最新开发的LOL职业选手综合管理系统：》\n\n");
	printf(" \n\n    《我们会依次介绍本程序的主要功能与使用提示》  \n\n");
	printf(" \n\n    《首先请按照程序顺序依次操作》                  \n\n");
    printf(" \n\n    《输入选手数据时请注意提示信息，请勿有不恰当输入》                 \n\n");
	printf(" \n\n    《输入后请及时按提示保存信息》                \n\n");
	printf(" \n\n    《我们特此推出本程序十分有效的功能，如下》              \n\n");
	printf(" \n\n    《预测职业选手综合信息 ，按序评价，价值评估，选手搭配》\n\n");
	printf(" \n\n    《相信会为各位投资人提供帮助》             \n\n");
	printf(" \n\n    《此外，还有删除，显示，清空等专业功能，保证信息安全》             \n\n");//要让“投资人”有好的体验一定要写充分
	printf(" \n\n    《此外，还有专属的投资人函数功能，能让你对投资队伍更加了解，提升您对队伍的信息！！！         \n\n");
printf("  %%￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥%%\n");
}
  system("pause");
}

//2.添加函数
void input()
{
    if(id==1)
{
    if(allow==0)
        {printf("%您未完成认证，无权使用此功能");
    system("pause");
    return ;}
}
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
    if(id==1)
{
    if(allow==0)
        {printf("%您未完成认证，无权使用此功能");
    system("pause");
    return ;}
}
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
 if(id==1)
{
    if(allow==0)
        {printf("%您未完成认证，无权使用此功能");
    system("pause");
    return ;}
}
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
     if(id==1)
{
    if(allow==0)
        {printf("%您未完成认证，无权使用此功能");
    system("pause");
    return ;}
}
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
     if(id==1)
{
    if(allow==0)
        {printf("%您未完成认证，无权使用此功能");
    system("pause");
    return ;}
}
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
     if(id==1)
{
    if(allow==0)
        {printf("%您未完成认证，无权使用此功能");
    system("pause");
    return ;}
}
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
//10.配合函数
void cooperate()
{
    float sumKDA, varKDA, sumweidcao, varweicao, sumyunying, varyunying;
    float operatepercent;//方差和,方差和越大，配合度越低
    for(int t = 0; t < m; t++){
        sumKDA = sumKDA + pla[t].score[0];
    }
    sumKDA = sumKDA / m;
    for(int t = 0; t < m; t++){
        varKDA = varKDA + (pla[t].score[0] - sumKDA) * (pla[t].score[0] - sumKDA);
    }
    varKDA = varKDA / m;
    for(int t = 0; t < m; t++){
        sumweidcao = sumweidcao + pla[t].score[1];
    }
    sumweidcao = sumweidcao / m;
    for(int t = 0; t < m; t++){
        varweicao = varweicao + (pla[t].score[1] - sumweidcao) * (pla[t].score[1] - sumweidcao);
    }
    varweicao = varweicao / m;
    for(int t = 0; t < m; t++){
        sumyunying = sumyunying + pla[t].score[2];
    }
    sumyunying = sumyunying / m;
    for(int t = 0; t < m; t++){
        varyunying = varyunying + (pla[t].score[2] - sumyunying) * (pla[t].score[2] - sumyunying);
    }
    varyunying = varyunying / m;
    operatepercent = varKDA + varweicao + varyunying;
    printf("所有选手配合程度:%f", operatepercent);
    system("pause");
}
//11.评估价值函数
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
        if(valuescore <= 7)
            printf("经过系统查核，此位选手的综合评价为：较低\n");
        else if(valuescore <= 14)
            printf("经过系统查核，此位选手的综合评价为：良好\n");
        else
            printf("经过系统查核，此位选手的综合评价为：优秀\n");
    }
    system("pause");
}

void check()
{
   char userName[5];/*用户名*/
   char userPWD[5];/*密码*/
   int i,sum;
   system("color f3");
   printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
   printf(" *+*+*+*+*+*+*+ LOL职业选手管理系统登录界面*+*+*+*+*+*+*+\n");
   printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
   for(i = 1; i < 4; i++)
   {
      /*用户名和密码均为abcde;*/
        printf("*+*+*+*+*+*+*+教练和投资人密码分别为abcde or ABCDE*+*+*+*+*+*+*+\n\n");
         printf(" *+*+*+*+*+*+*+教练通行码为12345*+*+*+*+*+*+*+\n");
        printf("\n *+*+*+*+*+*+*+请输入您的用户名（NPU01）:*+*+*+*+*+*+*+");
        gets(userName);
        printf("\n       请输入您的密码:");
        gets(userPWD);

        if ((strcmp(userPWD,"ABCDE")==0) || (strcmp(userPWD,"abcde")==0))/*验证用户名和密码*/
        {
            if((strcmp(userPWD,"abcde")==0)){id=0;}
           else id=1;
          printf("您的id为%d\n\n",id);
          if(id==1)
            printf("您的身份为尊贵的投资人");
            else printf("您的身份为教练");


            printf("\n                      *用户名和密码正确，显示主菜单*");
            system("pause");
            return;
        }
        else
        {
            if (i < 3)
            {
                printf("密码错误，提示用户重新输入");
                printf("密码错误，请重新输入!");
            }
            else
            {
                printf("连续3次输错密码，退出系统。");
                printf("您已连续3次将密码输错，系统将退出!");
                exit(1);
            }
        }
   }
}
void agreement()
{   int cc;
printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*\n");
printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*\n");
    printf("因为您的身份为投资人\n");
    printf("需要对您进行教练信息录入资格验证\n");
    printf("请输入教练通行码进行验证\n");
    printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*\n");
    printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*\n");
    scanf("%d",&cc);
    if(cc==12345) allow=1;
    else allow=0;
    printf("您的投资人通用令牌为%d\n",allow);
    if(allow==1)
        printf("认证成功！！！");
    else printf("认证失败\n");

    system("pause");
}
//12.投资人专用评估函数
void money()
{    printf("此为投资人专用系统\n");
if(id==0) system("pause");
   struct player  *p;
   p=&pla[0];
   int i,sum;
	printf("共有%d位职业选手的信息:\n", n);
	if (0 != n)
	{  printf("  %%   *+*+*+*+*+*+*+*+*------------+*+*+*+*+*\n");
		printf("可从每位选手中获得的利益\n");
		printf("  %%   *+-------------------------+*+*+*+*+*\n");
		for (i = 0; i<n; i++,p++)
		{    sum= (p->score[0]+ p->score[1]+ p->score[2])/3;
			if(0<=sum&&sum<500) printf("%d\n",(sum*1.25+10000));
            else  if(500<sum&&sum<=1000)printf("%d\n",(sum*1.5+10000));
			else  if(1000<sum&&sum<=1500) printf("%d\n",(sum*2+10000));
			else printf("PRICELESS\n");
		}

}
system("pause");
}
//13,教练专属比赛查看系统
void competition()
{
    printf("此功能为教练专用\n");
    if (id == 1){
    printf("对不起，投资人无法查看该功能，请退出！！！\n");
         system("pause");
    }
    struct compla
    {
        int name;
        float kda;
        int s;
        float m;
    }com[n];
    int i;
    for(i = 0; i < n; i++)
    {
        com[i].kda = pla[i].score[0];
        com[i].name = i + 1;
        if (pla[i].score[0] >= 8 && pla[i].score[1] >= 450 &&pla[i].score[2] >= 400)
            com[i].s = 1;
        else if (pla[i].score[0] >= 6 && (pla[i].score[1] + pla[i].score[2]) >= 700)
            com[i].s = 0;
        else
            com[i].s = -1;
        com[i].m = pla[i].playerAge + pla[i].score[0] + pla[i].score[1] *0.02 + pla[i].score[2] *0.03;
    }
    printf("序号          |近十场kda         |近十场综合得分            |近十场称号获得\n");
    for(i = 0; i < n; i++)
    {
        printf("%d             |%.1f              |%.6f                 |", com[i].name, com[i].kda, com[i].m);
        if(com[i].s == 1)
            printf("MVP\n");
        else if(com[i].s == 0)
            printf("FMVP\n");
        else
            printf("成绩欠佳\n");
    }
    system("pause");
}
//14.教练专属队员交易系统
void exchangepla()
{
    printf("此系统为教练专属\n");
    if(id == 1){
        printf("对不起，投资人无法查看该功能，请退出！！！\n");
        return;
    }
    struct
    {
        float score;
        int num;
    }a[n];
    int i, j, k;
    for(i = 0; i < n; i++)
    {
        a[i].score = pla[i].score[0] + pla[i].score[1] * 0.01 + pla[i].score[2] *0.05 - pla[i].playerAge *0.4;
        a[i].num = i + 1;
    }
    for(j = 0; j < n - 1; j++)
    {
        for(i = 0; i < n - 1 - j; i++)
        {
            if(a[i].score < a[i + 1].score)
            {
                k = a[i].score, a[i].score = a[i + 1].score, a[i + 1].score = k;
                k = a[i].num, a[i].num = a[i + 1].num, a[i + 1].num = k;
            }
        }
    }
    printf("系统根据近十场选手的综合得分，进行降序排序得如下结果，供教练参考交易\n");
    for(i = 0; i < n; i++)
    {
        printf("第%d号：选手编号为%d  综合得分为%.6f\n", i + 1, a[i].num, a[i].score);
    }
    printf("亲爱的教练，您有如下战队可以进行交易：\n");
    printf("1号战队：IG战队     可以进行交易的选手为------the shy\n");
    printf("2号战队：RNG战队    可以进行交易的选手为------UZI\n");
    printf("3号战队：SN战队     可以进行交易的选手为------bin\n");
    printf("以上仅供参考，具体交易待您确定后，请前往添加和删除函数进行具体操作\n");
    system("pause");
}
//15.投资人专属价值预估系统
void investorassess()
{
    printf("此系统为投资人专属\n");
    if(id == 0)
    {
        printf("对不起，教练无法查看该功能，请退出！！！\n");
        return;
    }
    int i;
    float VA[n];
    printf("系统结合输入的选手信息，经建模预测，得到如下结果：\n");
    for(i = 0; i < n; i++)
    {
        VA[i] = pla[i].score[0] + pla[i].score[1] * 0.01 + pla[i].score[2] *0.05 - pla[i].playerAge *0.4;
    }
    for(i = 0; i < n; i++)
    {
        printf("选手代号：%s        年龄：%d         场均kda：%.1f        场均评分：%.6f       综合价值：%.4f     \n", pla[i].playerName,
               pla[i].playerAge, pla[i].score[0], pla[i].score[1]+pla[i].score[2], VA[i]);
        printf("年龄价值评估： ");
        if (pla[i].playerAge <= 18)
            printf("this player is gifted\n");
        else if (pla[i].playerAge <= 22)
            printf("this player is mature\n");
        else
            printf("this player is steady\n");
    }
    system("pause");
}
//17.投资人个人投资系统
void investindi()
{
    printf("此系统为投资人专属\n");
    if(id == 0)
    {
        printf("对不起，教练无法查看该功能，请退出！！！\n");
        return;
    }
    int num,judge;
    double investment;
    printf("请选择您希望投资的选手的编号   \n");
    scanf("%d",&num);
    investment=((30-pla[num-1].playerAge*10)+pla[num-1].score[0]*10+pla[num-1].score[1]+pla[num-1].score[2])*20;//计算投资的金额
    if(investment>10000){
      printf("该选手的价值较高，请问是否要投资？(1为投资，0为不投资)\n");
      scanf("%d",&judge);
      switch(judge){
      case 1:printf("好的，您已经向%d号选手投资%lf元",num,investment);
      case 0:printf("好的，您已取消投资");
      }
    }
    else printf("该选手价值较低，不建议投资");
    system("pause");
}
//18.投资人组合投资系统
void investgroup()
{
     printf("此系统为投资人专属\n");
    if(id == 0)
    {
        printf("对不起，教练无法查看该功能，请退出！！！\n");
        return;
    }
    int judge;
    double investment=0;
    for(int i = 0;i<n;i++){
        investment+=((30-pla[i].playerAge*10)+pla[i].score[0]*10+pla[i].score[1]+pla[i].score[2])*20;
    }
    float sumKDA, varKDA, sumweidcao, varweicao, sumyunying, varyunying;
    float operatepercent;//方差和,方差和越大，配合度越低
    for(int t = 0; t < m; t++){
        sumKDA = sumKDA + pla[t].score[0];
    }
    sumKDA = sumKDA / m;
    for(int t = 0; t < m; t++){
        varKDA = varKDA + (pla[t].score[0] - sumKDA) * (pla[t].score[0] - sumKDA);
    }
    varKDA = varKDA / m;
    for(int t = 0; t < m; t++){
        sumweidcao = sumweidcao + pla[t].score[1];
    }
    sumweidcao = sumweidcao / m;
    for(int t = 0; t < m; t++){
        varweicao = varweicao + (pla[t].score[1] - sumweidcao) * (pla[t].score[1] - sumweidcao);
    }
    varweicao = varweicao / m;
    for(int t = 0; t < m; t++){
        sumyunying = sumyunying + pla[t].score[2];
    }
    sumyunying = sumyunying / m;
    for(int t = 0; t < m; t++){
        varyunying = varyunying + (pla[t].score[2] - sumyunying) * (pla[t].score[2] - sumyunying);
    }
    varyunying = varyunying / m;
    operatepercent = varKDA + varweicao + varyunying;
    printf("团队的配合程度为%f(该数越小，配合程度越高)，是否要投资？(1为投资，0为不投资)",operatepercent);
    scanf("%d",&judge);
    switch(judge){
    case 1:printf("好的，您已向团队投资%lf元",investment);
    case 0:printf("好的，您已取消投资");
    }
    system("pause");
}
//主函数
int main()
{   check();
if(id==1) agreement();
	while (start)
	{
		menu();
	}
	system("pause");
	return 0;

}
