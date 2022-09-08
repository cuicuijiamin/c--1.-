#include<easyx.h>
#include<iostream>
#include<conio.h>
using namespace std;
const int TOTAL = 2;
int myMap[TOTAL][10][10] = {
	{
		1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,2,0,3,4,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,

	 },
	{
		1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,2,0,3,0,0,0,0,1,
		1,0,0,0,0,0,4,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,3,4,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,

	 }
};

int level = 0;//第一关为下标为0的myMap的地图
int mapArr[10][10];//地图数组
IMAGE img[5];

struct Pos { int x; int y; }pos;

//
void initMapArray()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			mapArr[i][j] = myMap[level][i][j];
		}
	}
}
//
void initIma()
{
	loadimage(&img[0], "Release\\1.jpg", 50, 50);//1:墙
	loadimage(&img[1], "Release\\2.jpg", 50, 50);//2:人
	loadimage(&img[2], "Release\\3.jpg", 50, 50);//3.箱子
	loadimage(&img[3], "Release\\4.jpg", 50, 50);//4.目的地  6.人在目的地上
	loadimage(&img[4], "Release\\7.jpg", 50, 50);//7.箱子在目的地上
	//5表示人在目的地上
}
//
void drawIma()
{
	BeginBatchDraw();
	for (int i = 0; i < 10; ++i)//一行一行遍历
	{
		for (int j = 0; j < 10; ++j)
		{
			switch (mapArr[i][j])
			{
			case 1:putimage(j * 50, i * 50, &img[0]);
				break;
			case 2:case 6:putimage(j * 50, i * 50, &img[1]);
				break;
			case 3:putimage(j * 50, i * 50, &img[2]);
				break;
			case 4:putimage(j * 50, i * 50, &img[3]);
				break;
			case 7:putimage(j * 50, i * 50, &img[4]);
				break;
			}

		}
	}
	EndBatchDraw();
}

//
void findPlayer()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (mapArr[i][j] == 2|| mapArr[i][j] == 6)
			{
				pos.x = i;
				pos.y = j;
			}
		}
	}
}
//
void _playerMove(int dx, int dy)
{
	int x = pos.x + dx;
	int y = pos.y + dy;//后一位置
	int flag = 0;
	if (mapArr[x][y] == 1)//墙  
	{
		MessageBox(NULL, _T("非法移动"), _T("提示"), NULL);
	}
	else 
	{
		if (mapArr[x][y] == 0 || mapArr[x][y] == 4)//空地/目的地
		{
			mapArr[x][y] += 2;//空地/目的地   ========人
			mapArr[pos.x][pos.y] -= 2;//人的位置==========空地
			flag = 1;
		}
		else//箱子/箱子在目的地上
		{
			if (mapArr[x + dx][y + dy] == 1 || mapArr[x + dx][y + dy] == 3 || mapArr[x + dx][y + dy] == 7)//箱子的后一位  墙
			{
				MessageBox(NULL, _T("非法移动"), _T("提示"), NULL);
			}
			else//空地/目的地
			{
				mapArr[pos.x][pos.y] -= 2;//人的位置==========空地
				mapArr[x][y] -= 1;//箱子(在目的地)的位置==========人(在目的地)
				mapArr[x + dx][y + dy] += 3;//空地==========箱子
				flag = 1;
			}
		}
		if (flag)
		{
			pos.x += dx;
			pos.y += dy;
		}
	}
}
void playerMove()
{
	char ch = _getch();
	int dx = 0, dy = 0;
	if (ch == 'a' || ch == 'A')
	{
		dx = 0;
		dy = -1;
	}
	if (ch == 'w' || ch == 'W')
	{
		dx = -1;
		dy = 0;
	}
	if (ch == 's' || ch == 'S')
	{
		dy = 0;
		dx = 1;
	}
	if (ch == 'd' || ch == 'D')
	{
		dx = 0;
		dy = 1;
	}
	_playerMove(dx, dy);
	
}

bool endGame()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (mapArr[i][j] == 3)
			{
				return false;
			}
		}
	}
	return true;
}
int main()
{
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, _T("推箱子"));
	initgraph(500, 500);
	initMapArray();
	initIma();
	findPlayer();//开局记录玩家位置
	while (1)
	{
		cleardevice();
		drawIma();
		if (endGame())
		{
			//参数1标识将被创建的消息框的拥有窗口
			if (MessageBox(GetHWnd(), _T("WIN"), _T("提示"), MB_YESNO) == IDYES)
			{
				level++;
				if (level == TOTAL)
				{
					MessageBox(GetHWnd(), _T("您已全部通关！！"), _T("提示"), NULL);
					exit(0);
				}
				initMapArray();
				findPlayer();//开局记录玩家位置
				continue;
			}
			else
			{
				exit(0);
			}
		}
		playerMove();

	}
	return 0;
}


