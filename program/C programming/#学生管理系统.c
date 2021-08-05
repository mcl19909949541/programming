#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LEN 15		/* ѡ�ֱ�ź�ѡ�ִ�������ַ���,ʵ�������*/
#define N 50		/* ���ְҵѡ������,ʵ�������*/

int k = 1, n = 0, m = 0;/* n����ǰ��¼��ְҵѡ������*/

//��������
void readfile();
void seek();
void modify();
void insert();
void del();
void display();
void save();
void menu();

//�ṹ�屣��ְҵѡ����Ϣ
struct player{
	char playerId[LEN+1];
	char playerName[LEN+1];
	int playerAge;
	char playerSex;
	float score[3];
}pla[N];

//������
int main()
{
	while (k)
	{
		menu();
	}
	system("pause");
	return 0;
}
void menu()/* ����*/
{
	int num;
	printf(" \n\n                    \n\n");
	printf("  ******************************************************\n\n");
	printf("  *                ְҵѡ����Ϣ����ϵͳ                    *\n \n");
	printf("  ******************************************************\n\n");
	printf("*********************ϵͳ���ܲ˵�*************************       \n");
	printf("     ----------------------   ----------------------   \n");
	printf("     *********************************************     \n");
	printf("     * 0.ϵͳ������˵��  * *  1.ˢ��ְҵѡ����Ϣ   *     \n");
	printf("     *********************************************     \n");
	printf("     * 2.��ѯְҵѡ����Ϣ    * *  3.�޸�ְҵѡ����Ϣ   *     \n");
	printf("     *********************************************     \n");
	printf("     * 4.����ְҵѡ����Ϣ    * *  5.��ѡ�ֱ��ɾ����Ϣ *     \n");
	printf("     *********************************************     \n");
	printf("     * 6.��ʾ��ǰ��Ϣ    * *  7.���浱ǰְҵѡ����Ϣ*     \n");
	printf("     ********************** **********************     \n");
	printf("     * 8.�˳�ϵͳ        *                            \n");
	printf("     **********************                            \n");
	printf("     ----------------------   ----------------------                           \n");
	printf("��ѡ��˵����:");
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
		printf("�����˳�����!\n");
		break;
	default:printf("����0-8֮��ѡ��\n");
	}
}


//ϵͳ��������
void help()
{
	printf("   ��\n");
	printf("���ν���ϵͳ��,����ѡ������ְҵѡ����Ϣ;\n");
	printf("���ղ˵���ʾ�������ִ���;\n");
	printf("����ְҵѡ����Ϣ��,�мǱ���;\n");
	printf("лл����ʹ�ã�\n");
}

//ˢ���ļ�
int flush(){
	char filename[LEN + 1];
	int i = 0;
	printf("������Ҫˢ��ְҵѡ����Ϣ���ļ�����\n");
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

//����ְҵѡ����Ϣ
void seek() /*����*/
{
	int i, item, flag;
	char s1[21]; /* ��ѡ�ִ��ź�ѡ�ֱ�������+1Ϊ׼*/
	printf("------------------\n");
	printf("-----1.��ѡ�ֱ�Ų�ѯ-----\n");
	printf("-----2.��ѡ�ִ��Ų�ѯ-----\n");
	printf("-----3.�˳����˵�-----\n");
	printf("------------------\n");
	while (1)
	{
		printf("��ѡ���Ӳ˵����:");
		scanf("%d", &item);
		flag = 0;
		switch (item)
		{
		case 1:
			printf("������Ҫ��ѯ��ְҵѡ�ֵ�ѡ�ֱ��:\n");
			scanf("%s", s1);
			for (i = 0; i<n; i++)
			if (strcmp(s1,pla[i].playerId) == 0)
			{
				flag = 1;
				printf("ְҵѡ��ѡ�ֱ��\ְҵѡ��ѡ�ִ���\t����\t�Ա�\APM\΢������\��Ӫ����\n");
				printf("--------------------------------------------------------------------\n");
				printf("%s\t%s\t%d\t%6\t%.1f\t%.1f\t%.1f\n", pla[i].playerId,pla[i].playerName,pla[i].playerAge,pla[i].playerSex,pla[i].score[0],pla[i].score[1],pla[i].score[2]);
			}
			if (0 == flag)
				printf("��ѡ�ֱ�Ų����ڣ�\n"); break;
		case 2:
			printf("������Ҫ��ѯ��ְҵѡ�ֵ�ѡ�ִ���:\n");
			scanf("%s", s1);
			for (i = 0; i<n; i++)
			if (strcmp(pla[i].playerName, s1) == 0)
			{
				flag = 1;
				printf("ְҵѡ��ѡ�ֱ��\ְҵѡ��ѡ�ִ���\t����\t�Ա�\tAPM\΢������\��Ӫ����\n");
				printf("--------------------------------------------------------------------\n");
				printf("%s\t%s\t%d\t%c\t%.1f\t%.1f\t%.1f\n", pla[i].playerId, pla[i].playerName, pla[i].playerAge, pla[i].playerSex, pla[i].score[0], pla[i].score[1], pla[i].score[2]);
			}
			if (0 == flag)
				printf("��ѡ�ִ��Ų����ڣ�\n"); break;
		case 3:return;
		default:printf("����1-3֮��ѡ��\n");
		}
	}
}

//�޸�ְҵѡ����Ϣ
void modify() /*�޸���Ϣ*/
{
	int i, item, num = -1;
	char sex1, s1[LEN + 1], s2[LEN + 1]; /* ��ѡ�ִ��ź�ѡ�ֱ�������+1Ϊ׼*/
	float score1;
	printf("������ҪҪ�޸ĵ�ְҵѡ�ֵ�ѡ�ֱ��:\n");
	scanf("%s", s1);
	for (i = 0; i < n; i++){
		if (strcmp(pla[i].playerId, s1) == 0){/*�Ƚ��ַ����Ƿ����*/
			num = i;
			printf("------------------\n");
			printf("1.�޸�ѡ�ִ���\n");
			printf("2.�޸�����\n");
			printf("3.�޸��Ա�\n");
			printf("4.�޸�APM\n");
			printf("5.�޸ĸߵ���ѧ�ɼ�\n");
			printf("6.�޸Ĵ�ѧӢ��ɼ�\n");
			printf("7.�˳����˵�\n");
			printf("------------------\n");
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
					printf("�������µĸߵ���ѧ�ɼ�:\n");
					scanf("%f", &score1);
					pla[num].score[1] = score1;
					break;
				case 6:
					printf("�������µĴ�ѧӢ��ɼ�:\n");
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



//���ְҵѡ����Ϣ����
void insert() /*���뺯��*/
{
	int i = n, j, flag;
	printf("����������ӵ�ְҵѡ����:\n");
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
						printf("��ѡ�ֱ���Ѵ��ڣ����������룡\n");
						flag = 1;
						break;
					}
				}
			}
			printf("�������%d ��ְҵѡ�ֵ�ѡ�ִ���:\n", i+1);
			scanf("%s", pla[i].playerName);
			printf("�������%d ��ְҵѡ�ֵ�����:\n", i+1);
			scanf("%d", &pla[i].playerAge);
			printf("�������%d ��ְҵѡ�ֵ��Ա�:\n", i+1);
			scanf(" %c", &pla[i].playerSex);
			printf("�������%d ��ְҵѡ�ֵ�APM\n",i+1);
			scanf("%f", &pla[i].score[0]);
			printf("�������%d ��ְҵѡ�ֵĸߵ���ѧ�ɼ�:\n", i+1);
			scanf("%f", &pla[i].score[1]);
			printf("�������%d ��ְҵѡ�ֵĴ�ѧӢ��ɼ�:\n", i+1);
			scanf("%f", &pla[i].score[2]);
			if (0 == flag){
				i++;
			}
		} while (i<n + m);
	}
		n += m;
		printf("ְҵѡ����Ϣ������ϣ�����\n");
		system("pause");
}

//ɾ��ְҵѡ����Ϣ����
void del()
{
	int i, j, flag = 0;
	char s1[LEN + 1];
	printf("������Ҫɾ��ְҵѡ�ֵ�ѡ�ֱ��:\n");
	scanf("%s", s1);
	for (i = 0; i < n; i++){
		if (strcpy(pla[i].playerId, s1) == 0){
			flag = 1;
			//Ҫɾ��ְҵѡ�ֺ����ְҵѡ����ǰ��һλ
			for (j = i; j < n - 1; j++){
				pla[j] = pla[j + 1];
			}
		}
	}
		//����ʧ��
		if (0 == flag){
			printf("��ѡ�ֱ�Ų�����!!!\n");
		}
		if (1 == flag){
			printf("ɾ���ɹ�������");
			//ɾ���ɹ���ְҵѡ��������1
			n--;
		}
		system("pause");
}
void save(){
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

//��ʾȫ��������Ϣ
void display()
{
	int i;
	printf("����%dλְҵѡ�ֵ���Ϣ:\n", n);
	if (0 != n)
	{
		printf("ְҵѡ��ѡ�ֱ�� \ְҵѡ��ѡ�ִ��� \t����   \t�Ա�   \tAPM\΢������ \��Ӫ����\n");
		printf("--------------------------------------------------------------------\n");
		for (i = 0; i<n; i++)
		{
			printf("%s \t%s \t%d   \t%c   \t%.1f\t%.1f \t%.1f\n", pla[i].playerId, pla[i].playerName, pla[i].playerAge, pla[i].playerSex, pla[i].score[0],pla[i].score[1],pla[i].score[2]);
		}
	}
	system("pause");
}

