#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LEN 15		/* ѡ�ֱ�ź�ѡ�ִ��������*/
#define N 50		/* ���ְҵѡ������,*/

//���ܺ�������
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


//ȫ�ֱ���
int n=0,m=0,start=1;


//�ṹ�屣��ְҵѡ����Ϣ
struct player{
	char playerId[LEN];
	char playerName[LEN];
	int playerAge;
	char playerSex;
	float score[3];
}pla[N];


//0.ָ�Ϻ���
void menu ()
{
    	int num;
	printf(" \n\n                    \n\n");
	printf(" \n\n                    \n\n");
	printf(" \n\n                    \n\n");
	printf("  %%������������������������������������������������������%%\n");
	printf("        !!!!&&&&&&&&ְҵѡ����Ϣ����ϵͳ&&&&&&&&&!!!!  \n ");
	printf("  %%      +*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+* %%    \n");
	printf("  %%     *****************���ܲ˵�**********************   %%   \n");
	printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
	printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+* %%   \n");
	printf("  %% 1.˵��(ʹ��ǰ����ϸ�Ķ���    2.����ְҵѡ����Ϣ         %%    \n");
	printf("  %%                                                      %%  \n");
	printf("  %% 3.�޸�ְҵѡ����Ϣ           4.ɾ��ְҵѡ����Ϣ         %% \n");
	printf("  %%                                                      %%    \n");
	printf("  %% 5.���ְҵѡ����Ϣ           6.������Ϣ                 %%   \n");
	printf("  %%                                                    %%    \n");
	printf("  %% 7.�����Ϣ                   8.Ԥ��ְҵѡ���ۺ���Ϣ     %%\n");
	printf("  %%                                                      %%     \n");
	printf("  %% 9.��������ϵͳ               10.��ֵ����ϵͳ            %%         \n");
    printf("  %%                                                      %%  \n");
	printf("  %%11.ѡ�ִ���ϵͳ               12.�˳�ϵͳ                %%    \n");
	printf("  %%*+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*  %% \n");
	printf("  %%������������������������������������������������������%% \ \n");
	printf("��ѡ��˵����:");
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
		start = 0;//����Ϊ0��������ֱ���˳�
		printf("�������������˳����򡷡���������\n");
		break;
	default:printf("{{{{����1-12֮��ѡ��}}}}\n");
     }

}

//1.˵������
void  system_guide()
{     	printf("   ��\n");
     printf("  %%������������������������������������������������������%%\n");
    printf(" \n\n    ���װ����û������ã���ӭʹ�����¿�����LOLְҵѡ���ۺϹ���ϵͳ����\n\n");
	printf(" \n\n    �����ǻ����ν��ܱ��������Ҫ������ʹ����ʾ��  \n\n");
	printf(" \n\n    �������밴�ճ���˳�����β�����                  \n\n");
    printf(" \n\n    ������ѡ������ʱ��ע����ʾ��Ϣ�������в�ǡ�����롷                 \n\n");
	printf(" \n\n    ��������뼰ʱ����ʾ������Ϣ��                \n\n");
	printf(" \n\n    �������ش��Ƴ�������ʮ����Ч�Ĺ��ܣ����¡�              \n\n");
	printf(" \n\n    ��Ԥ��ְҵѡ���ۺ���Ϣ ���������ۣ���ֵ������ѡ�ִ��䡷\n\n");
	printf(" \n\n    �����Ż�Ϊ��λ�����ṩ������             \n\n");
	printf(" \n\n    �����⣬����ɾ������ʾ����յ�רҵ���ܣ���֤��Ϣ��ȫ��             \n\n");//Ҫ�á��������кõ�����һ��Ҫд���
printf("  %%������������������������������������������������������%%\n");
  system("pause");
}

//2.���Ӻ���
void input()
{
 int i = n, j, flag;
	printf("<<<<<����������ӵ�ְҵѡ����>>>>>\n");
	scanf("%d", &m);
	if (m > 0){
		do
		{
			flag = 1;
			while (flag)
			{
				flag = 0;
				printf("�������%dλְҵѡ�ֵ�ѡ�ֱ��:\n", i + 1);
				scanf("%s", pla[i].playerId);
				for (j = 0; j < i; j++){
					if (strcmp(pla[i].playerId, pla[j].playerId) == 0){
						printf("!!!!!!  !!!!��ѡ�ֱ���Ѵ���!!!!!!!  !!!!!!!\n");
						flag = 1;
						break;
					}
				}
			}
			printf("  %%������������������������������������������������������%%\n");
			printf("�������%d ��ְҵѡ�ֵ�ѡ�ִ���:\n", i+1);
			scanf("%s", pla[i].playerName);
			printf("�������%d ��ְҵѡ�ֵ�����:\n", i+1);
			scanf("%d", &pla[i].playerAge);
			printf("�������%d ��ְҵѡ�ֵ��Ա�(��Ϊ1��Ů������0��:\n", i+1);
			scanf(" %c", &pla[i].playerSex);
			printf("�������%d ��ְҵѡ�ֵ�����ƽ��KDA(0-20)\n",i+1);
			scanf("%f", &pla[i].score[0]);
			printf("�������%d ��ְҵѡ��΢������(0-500):\n", i+1);
			scanf("%f", &pla[i].score[1]);
			printf("�������%d ��ְҵѡ�ֵ���Ӫ����(0-500):\n", i+1);
			printf("  %%������������������������������������������������������%%\n");
			scanf("%f", &pla[i].score[2]);
			if (flag==0){
				i++;
			}
		} while (i<n + m);
	}
		n += m;
		printf("ְҵѡ����Ϣ������ϣ�����\n");
		system("pause");

}

//3.�޸ĺ���
void correct ()
{
   int i, item, num = -1;
	char sex1, s1[LEN], s2[LEN]; /* ��ѡ�ִ��ź�ѡ�ֱ�������Ϊ׼*/
	float score1;
	printf("������ҪҪ�޸ĵ�ְҵѡ�ֵ�ѡ�ֱ��:\n");
	scanf("%s", s1);
	for (i = 0; i < n; i++){
		if (strcmp(pla[i].playerId, s1) == 0){/*�Ƚ��ַ����Ƿ����*/
			num = i;
			printf("  %%������������������������������������������������������%%\n");
			printf("------------------\n");
			printf("1.�޸�ѡ�ִ���\n");
			printf("2.�޸�����\n");
			printf("3.�޸��Ա�\n");
			printf("4.�޸�KPA\n");
			printf("5.�޸�΢������\n");
			printf("6.�޸���Ӫ����\n");
			printf("7.�˳����˵�\n");
			printf("------------------\n");
			printf("  %%������������������������������������������������������%%\n");
			while (1)
			{
				printf("��ѡ���Ӳ˵����:");
				scanf("%d", &item);
				switch (item)
				{
				case 1:
					printf("�������µ�ѡ�ִ���:\n");
					scanf("%s", s2);
					strcpy(pla[num].playerName, s2);
					break;
				case 2:
					printf("�������µ�����:\n");
					scanf("%d", pla[num].playerAge);
					break;
				case 3:
					printf("�������µ��Ա�:\n");
					scanf("%s", &sex1);
					pla[i].playerSex = sex1;
					break;
				case 4:
					printf("�������µ�APM:\n");
					scanf("%f", &score1);
					pla[num].score[0] = score1;
					break;
				case 5:
					printf("�������µ�΢������:\n");
					scanf("%f", &score1);
					pla[num].score[1] = score1;
					break;
				case 6:
					printf("�������µ���Ӫ����:\n");
					scanf("%f", &score1);
					pla[num].score[2] = score1;
					break;
				case 7:	return;
				default:printf("����1-7֮��ѡ��\n");
				}
			}
			printf("�޸���ϣ��뼰ʱ���棡\n");
		}
		else{
			printf("û�и�ְҵѡ��ѡ�ֱ��!!!");
		}
	}
}

//4.ɾ������
void  cut_off()
{
  int i, j, flag = 0;
	char s1[LEN];
	printf("  %%��������������������������%%\n");
	printf("������Ҫɾ��ְҵѡ�ֵ�ѡ�ֱ��:\n");
	printf("  %%������������������������%%\n");
	scanf("%s", s1);
	for (i = 0; i < n; i++){
		if (strcpy(pla[i].playerId, s1) == 0){
			flag = 1;
			//Ҫɾ��ְҵѡ�ֺ����ְҵѡ����ǰ��һλ
			for (j = i; j <=n ; j++){
				pla[j] = pla[j + 1];
			}
		}
	}
		//����ʧ��
		if (flag==0){
			printf("��ѡ�ֱ�Ų�����!!!\n");
		}
		if (1 == flag){
			printf("ɾ���ɹ�������");
			//ɾ���ɹ���ְҵѡ��������1
			n--;
		}
		system("pause");
}

//5.��պ���
void  reflash()
{
char filename[LEN];
	int i = 0;
	printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
	printf("������Ҫˢ��ְҵѡ����Ϣ���ļ�����\n");
    printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
	scanf("%s", filename);
	int j = 0;
	FILE * fp;
	if ((fp = fopen(filename, "r")) == NULL) return 0;
	//���ļ���ȡ��Ϣ
	while (fscanf(fp, "%s %s %s %d %d %d %d ", &pla[j].playerId, &pla[j].playerName, &pla[j].playerAge, &pla[j].playerSex, &pla[j].score[0], &pla[j].score[1], &pla[j].score[2]) == 7) {
		j++;
	}
	n = j;
	printf("ˢ�³ɹ�!!!");
	return n;
}

//6.���溯��
void  save()
{
int i;
	FILE *fp;
	char filename[LEN + 1];
	printf("������Ҫ������ļ�����\n");
	scanf("%s", filename);
	fp = fopen(filename, "w");
	for (i = 0; i < n; i++){
		fprintf(fp, "%s%s%d%c%.lf%.lf%.lf\n", pla[i].playerId, pla[i].playerName, pla[i].playerAge, pla[i].playerSex,
			pla[i].score[0], pla[i].score[1], pla[i].score[2]);
	}
	printf("����ɹ�������\n");
	fclose(fp);
	system("pause");
}

//7.�������
void  output()
{
int i;
	printf("����%dλְҵѡ�ֵ���Ϣ:\n", n);
	if (0 != n)
	{   printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
		printf("ְҵѡ��ѡ�ֱ�� \ְҵѡ��ѡ�ִ��� \t����   \t�Ա�   \tAPM\΢������ \��Ӫ����\n");
	    printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
		for (i = 0; i<n; i++)
		{
			printf("%s \t%s \t%d   \t%c   \t%.1f\t%.1f \t%.1f\n", pla[i].playerId, pla[i].playerName, pla[i].playerAge, pla[i].playerSex, pla[i].score[0],pla[i].score[1],pla[i].score[2]);
		}
	}
	system("pause");
}
//8.Ԥ�⺯��
void  forecast()
{
int i,sum;
	printf("����%dλְҵѡ�ֵ���Ϣ:\n", n);
	if (0 != n)
	{  printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
		printf("ְҵѡ���ۺϵȼ�\n");
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
//9.��׼��������
void assessment()
{   int i,j,k;
     struct player example;
printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
printf("������%d��LOLְҵѡ�ְ�KDA-> ΢��ˮƽ-> ��Ӫˮƽ ��ǿ������������\n",&n);
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
    int operatepercent;//�����
    printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
printf("�ɼ����������ѡ�ּ���ϳ̶�\n");
printf("  %%   *+*+*+*+*+*+*+*+*+*+*+*+*+*++*+*+*+*+*+*+*+*+*+*+*+*\n");
    for(int t=0;t<m;t++){
        sumage=sumage+pla[t].playerAge;//���
    }
    sumage=sumage/m;//ƽ��ֵ
    for(int t=0;t<m;t++){
        varage=varage+(pla[t].playerAge-sumage)*(pla[t].playerAge-sumage);//ƽ����
    }
    varage=varage/m;//����

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
    printf("����ѡ����ϳ̶�:%d",operatepercent);
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
        printf("��%d��ѡ�ֵ��ۺϼ�ֵ��������Ϊ:%lf\n", i + 1, valuescore);
    }
    system("pause");
}
//������
int main()
{
	while (start)
	{
		menu();
	}
	system("pause");
	return 0;

}

