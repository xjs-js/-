#include <stdio.h>
#include <string.h>
#define N 100			//	最多50名乘客


typedef struct Person
{
	char name[20];
	int curFloor;		// 当前楼层
	int toFloor;		// 目标楼层
} Person;


void input(Person p[], int n);					// 输入
void sort(Person p[], int n, int value);		// 对乘客排序
void run(Person p[], int n);					// 电梯运行，输出信息
int contain(char s1[], char s2[][10], int n);	// 判断函数


int main()
{
	int i;		// 循环变量		
	int floor, numPersons; // 电梯当前楼层、 乘客人数
	int up_1 = 0, up_2 = 0, down_1 = 0; // 初始化三类人的人数都为0
	Person p[N];		// 存储开始时乘客的信息
	Person up1[N];		// 电梯上面想上去的人 
	Person up2[N];		// 电梯下面想上去的人
	Person down[N];		// 想下去的人
	
	// 得到乘客人数、电梯楼层
	printf("请输入等电梯的人数: ");
	scanf("%d", &numPersons);
	printf("请输入当前的楼层: ");
	scanf("%d", &floor);
	input(p, numPersons);
	
	
	// 对乘客判断，归类到对应结构体数组
	for (i = 0; i < numPersons; i++)
	{
		if (p[i].curFloor > p[i].toFloor)
			down[down_1++] = p[i];
		if ((p[i].curFloor < p[i].toFloor) && (p[i].curFloor >= floor))
			up1[up_1++] = p[i];
		if ((p[i].curFloor < p[i].toFloor) && (p[i].curFloor < floor))
			up2[up_2++] = p[i];
	}

	// 对三类人排序
	sort(up1, up_1,1);
	sort(up2, up_2,1);
	sort(down, down_1,0);
	printf("\n");
	
	// 电梯运行，把三类人运送到目的地
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
			printf("\n依次输入 %d名乘客的姓名、当前楼层、目标楼层: \n", n);
		printf("> ");
		scanf("%s %d %d", p[i].name, &p[i].curFloor, &p[i].toFloor);
	}
}


/*
	s1: 一维数组，存放字符串
	s2: 二位数组，存放 n个字符串 
	如果 s2中包含 s1，返回 1
	默认返回 0
*/
int contain(char s1[], char s2[][10], int n)
{
	int i = 0;		// 循环变量
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
			printf("当前楼层为 %2d, %s进入\n", p[i].curFloor, p[i].name);
			strcpy(s[i], p[i].name);
			i++;
		}
		else
		{
			printf("当前楼层为 %2d, %s出去\n", p[i].toFloor, p[i].name);
			i++;
		}
	}
}

/*
1、将原结构体数组p复制，得到新的结构体数组p2
2、对p按当前楼层排序
3、对p2按目标楼层排序
4、对p和p2归并排序
5、如果 p存储的是向下的人，则逆置
*/
void sort(Person p[], int n, int value)
{
	int i = 0, j = 0, k = 0;		// 循环变量	
	int index;						// 下标
	Person temp[N];
	Person p2[N];
	Person personTemp;				// 结构体用于交换
	
	// 复制
	for (i = 0; i < n; i++)
		p2[i] = p[i];
	
	// 对 p2按目标楼层从小到大排序
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

	// 对 p1按当前楼层从小到大排序
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