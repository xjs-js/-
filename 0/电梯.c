#include <stdio.h>
#include <string.h>
#define N 100			//	���50���˿�


typedef struct Person
{
	char name[20];
	int curFloor;		// ��ǰ¥��
	int toFloor;		// Ŀ��¥��
} Person;


void input(Person p[], int n);					// ����
void sort(Person p[], int n, int value);		// �Գ˿�����
void run(Person p[], int n);					// �������У������Ϣ
int contain(char s1[], char s2[][10], int n);	// �жϺ���


int main()
{
	int i;		// ѭ������		
	int floor, numPersons; // ���ݵ�ǰ¥�㡢 �˿�����
	int up_1 = 0, up_2 = 0, down_1 = 0; // ��ʼ�������˵�������Ϊ0
	Person p[N];		// �洢��ʼʱ�˿͵���Ϣ
	Person up1[N];		// ������������ȥ���� 
	Person up2[N];		// ������������ȥ����
	Person down[N];		// ����ȥ����
	
	// �õ��˿�����������¥��
	printf("������ȵ��ݵ�����: ");
	scanf("%d", &numPersons);
	printf("�����뵱ǰ��¥��: ");
	scanf("%d", &floor);
	input(p, numPersons);
	
	
	// �Գ˿��жϣ����ൽ��Ӧ�ṹ������
	for (i = 0; i < numPersons; i++)
	{
		if (p[i].curFloor > p[i].toFloor)
			down[down_1++] = p[i];
		if ((p[i].curFloor < p[i].toFloor) && (p[i].curFloor >= floor))
			up1[up_1++] = p[i];
		if ((p[i].curFloor < p[i].toFloor) && (p[i].curFloor < floor))
			up2[up_2++] = p[i];
	}

	// ������������
	sort(up1, up_1,1);
	sort(up2, up_2,1);
	sort(down, down_1,0);
	printf("\n");
	
	// �������У������������͵�Ŀ�ĵ�
	run(up1, up_1);
	run(down, down_1);
	run(up2, up_2);
		
	return 0;
}


void input(Person p[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (i == 0)
			printf("\n�������� %d���˿͵���������ǰ¥�㡢Ŀ��¥��: \n", n);
		printf("> ");
		scanf("%s %d %d", p[i].name, &p[i].curFloor, &p[i].toFloor);
	}
}


/*
	s1: һά���飬����ַ���
	s2: ��λ���飬��� n���ַ��� 
	��� s2�а��� s1������ 1
	Ĭ�Ϸ��� 0
*/
int contain(char s1[], char s2[][10], int n)
{
	int i = 0;		// ѭ������
	int value = 0;
	for (i = 0; i < n; i++)
	{
		if (strcmp(s1, s2[i]) == 0)
			value = 1;
	}
	return value;
}


void run(Person p[], int n)
{
	int i=0;

	char s[N][10];
	while (i < 2*n)
	{
		if (! contain(p[i].name, s, i))
		{
			printf("��ǰ¥��Ϊ %2d, %s����\n", p[i].curFloor, p[i].name);
			strcpy(s[i], p[i].name);
			i++;
		}
		else
		{
			printf("��ǰ¥��Ϊ %2d, %s��ȥ\n", p[i].toFloor, p[i].name);
			i++;
		}
	}
}

/*
1����ԭ�ṹ������p���ƣ��õ��µĽṹ������p2
2����p����ǰ¥������
3����p2��Ŀ��¥������
4����p��p2�鲢����
5����� p�洢�������µ��ˣ�������
*/
void sort(Person p[], int n, int value)
{
	int i = 0, j = 0, k = 0;		// ѭ������	
	int index;						// �±�
	Person temp[N];
	Person p2[N];
	Person personTemp;				// �ṹ�����ڽ���
	
	// ����
	for (i = 0; i < n; i++)
		p2[i] = p[i];
	
	// �� p2��Ŀ��¥���С��������
	for (i = 0; i < n-1; i++)
	{
		index = i;
		for (j = i+1; j < n; j++ )
			if (p2[j].toFloor < p2[index].toFloor)
				index = j;
		if (index != i)
		{
			personTemp = p2[i];
			p2[i] = p2[index];
			p2[index] = personTemp;
		}
	}

	// �� p1����ǰ¥���С��������
	for (i = 0; i < n-1; i++)
	{
		index = i;
		for (j = i+1; j < n; j++ )
			if (p[j].curFloor < p[index].curFloor)
				index = j;
		if (index != i)
		{
			personTemp = p[i];
			p[i] = p[index];
			p[index] = personTemp;
		}
	}

	i = 0, j = 0;
	while (i < n && j < n)
	{
		if (p[i].curFloor < p2[j].toFloor)
			temp[k++] = p[i++];	
		else
			temp[k++] = p2[j++];
	}
	while (i < n)
		temp[k++] = p[i++];
	while (j < n)
		temp[k++] = p2[j++];
	
	if (value)
		for (i = 0; i < 2*n; i++)
			p[i] = temp[i];
	else
		for (i = 0, j = 2*n-1; i < 2*n ; i++,j--)
			p[i] = temp[j];

}