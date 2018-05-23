#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

//全局变量
int position_x,position_y;  //飞机位置
int bullet_x,bullet_y;  //子弹位置
int enemy_x,enemy_y;  //敌机位置
int high,width;      //游戏画面尺寸
int score;                  
					//数据的初始化

void gotoxy(int x,int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle,pos);
}
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info={1,0};  //第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}

void startup()
{
	HideCursor();
	high = 20;
	width = 30;
	position_x = high/2;
	position_y = width/2;
	bullet_x = -1;
	bullet_y = position_y;
	enemy_x = 0;
	enemy_y = position_y;
	score = 0;
}
                      //显示画面
void show()
{
	gotoxy(0,0);
	int i,j;

	for(i=0;i<high;i++)
	{
		for(j=0;j<width;j++)
		{
			if((i==position_x)&&(j==position_y))      //输出飞机模型
				printf("  *  ");
			else if((i==position_x+1)&&(j==position_y))
				printf("*****");
			else if((i==position_x+2)&&(j==position_y))
				printf(" * * ");
			else if((i==enemy_x)&&(j==enemy_y))      //输出敌机模型
				printf("+");
			else if((i==bullet_x)&&(j==bullet_y))    //输出子弹模型
				printf("|");
			else
				printf(" ");
		}
		printf("\n");
	}

	printf("得分：%d\n",score);
	printf("按E键暂停\n");  
}

void updateWithoutInput()   //与用户输入无关的更新
{
	if(bullet_x>-1)
		bullet_x--;
	if((bullet_x == enemy_x)&&(bullet_y==enemy_y)) //子弹击中敌机
	{
		score++;   //分数+1
		enemy_x = -1;     //产生新的敌机
		enemy_y = rand()%width;
	}
	if(enemy_x>high)
	{
		enemy_x = -1;
		enemy_y = rand()%width;
	}
	static int speed = 0;    
	int gamespeed=30-score;  //控制飞机速度，每增加一分，速度加快
/*	if(speed<gamespeed)      //相当于一个睡眠函数
		speed++;
	if(speed == gamespeed)
	{
		enemy_x++;
		speed = 0;
	}*/
	
	
}

void updateWithInput()     //与用户输入有关的更新
{
	char input;
	if(kbhit())   //判断是否有输入
	{
		input = getch();
		if(input =='a')
			position_y--;  //位置左移
		if(input =='d')
			position_y++;  //位置右移
		if(input =='w')
			position_x--;  //位置上移
		if(input =='s')
			position_x++;  //位置下移
		if(input == ' ')
		{
			bullet_x = position_x-1;   //发射子弹的初始位置在飞机的正上方
			bullet_y = position_y+2;
		}
		if(input == 'e')   //使用暂停函数，实现暂停功能
			system("pause");
	}
}

int main()
{
	startup();   //数据的初始化
	while(1)    //游戏的循环执行
	{
		show();   //显示画面
		updateWithoutInput();  //与用户无关的更新
		updateWithInput();   //与用户有关的更新
	}
	return 0;
}
