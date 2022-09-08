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

int level = 0;//��һ��Ϊ�±�Ϊ0��myMap�ĵ�ͼ
int mapArr[10][10];//��ͼ����
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
	loadimage(&img[0], "Release\\1.jpg", 50, 50);//1:ǽ
	loadimage(&img[1], "Release\\2.jpg", 50, 50);//2:��
	loadimage(&img[2], "Release\\3.jpg", 50, 50);//3.����
	loadimage(&img[3], "Release\\4.jpg", 50, 50);//4.Ŀ�ĵ�  6.����Ŀ�ĵ���
	loadimage(&img[4], "Release\\7.jpg", 50, 50);//7.������Ŀ�ĵ���
	//5��ʾ����Ŀ�ĵ���
}
//
void drawIma()
{
	BeginBatchDraw();
	for (int i = 0; i < 10; ++i)//һ��һ�б���
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
	int y = pos.y + dy;//��һλ��
	int flag = 0;
	if (mapArr[x][y] == 1)//ǽ  
	{
		MessageBox(NULL, _T("�Ƿ��ƶ�"), _T("��ʾ"), NULL);
	}
	else 
	{
		if (mapArr[x][y] == 0 || mapArr[x][y] == 4)//�յ�/Ŀ�ĵ�
		{
			mapArr[x][y] += 2;//�յ�/Ŀ�ĵ�   ========��
			mapArr[pos.x][pos.y] -= 2;//�˵�λ��==========�յ�
			flag = 1;
		}
		else//����/������Ŀ�ĵ���
		{
			if (mapArr[x + dx][y + dy] == 1 || mapArr[x + dx][y + dy] == 3 || mapArr[x + dx][y + dy] == 7)//���ӵĺ�һλ  ǽ
			{
				MessageBox(NULL, _T("�Ƿ��ƶ�"), _T("��ʾ"), NULL);
			}
			else//�յ�/Ŀ�ĵ�
			{
				mapArr[pos.x][pos.y] -= 2;//�˵�λ��==========�յ�
				mapArr[x][y] -= 1;//����(��Ŀ�ĵ�)��λ��==========��(��Ŀ�ĵ�)
				mapArr[x + dx][y + dy] += 3;//�յ�==========����
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
	SetWindowText(hwnd, _T("������"));
	initgraph(500, 500);
	initMapArray();
	initIma();
	findPlayer();//���ּ�¼���λ��
	while (1)
	{
		cleardevice();
		drawIma();
		if (endGame())
		{
			//����1��ʶ������������Ϣ���ӵ�д���
			if (MessageBox(GetHWnd(), _T("WIN"), _T("��ʾ"), MB_YESNO) == IDYES)
			{
				level++;
				if (level == TOTAL)
				{
					MessageBox(GetHWnd(), _T("����ȫ��ͨ�أ���"), _T("��ʾ"), NULL);
					exit(0);
				}
				initMapArray();
				findPlayer();//���ּ�¼���λ��
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


