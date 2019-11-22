#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// Ű���� ��  
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 // ����(�����̽���)  

enum {
	black,
	blue,
	green,
	cyan,
	red,
	purple,
	brown,
	lightgray,
	darkgray,
	lightblue,
	lightgreen,
	lightcyan,
	lightred,
	lightpurple,
	yellow,
	white
};

char tempMap[14][56]; // �� �ӽ������� �迭  
char map[14][56] = { // �����  
	// ���� ���ڴ� �� �迭ũ�⿡ ���߾� 56��  
	{"000000000000000000000000000000000000000000000"}, // ���� ���̿� ���߾� 14��   
	{"000000000000000000000000000000000000000000000"},
	{"000000000000000000000000000000000000000000000"}, // 0 : �� ���� 
	{"000000000000000000000000000000000000000000000"}, // 1 : �� 
	{"000000000000000000000000000000000000000000000"}, // k : ���� 
	{"000000000000000000000000000000000000000000000"}, // l : ��� �� 
	{"000000001111111111111111111111111111100000000"}, // q : Ż�ⱸ  
	{"000000001q0000000000000000000000000q100000000"},
	{"000000001000000000000000000000000000100000000"},
	{"0000000010000000000000s0000000000000100000000"},
	{"000000001000000000000000000000000000100000000"},
	{"000000001000000000000000000000000000100000000"},
	{"000000001q0000000000000000000000000q100000000"},
	{"000000001111111111111111111111111111100000000"}
};


int keyControl(void);
void titleDraw(void);
int menuDraw(void);

void infoDraw(void);

void init();
void gotoxy(int, int);
void setColor(int, int);
void drawMap(void);
void move(int _x, int _y);
void gLoop(void);
void drawUI(void);

int pX, pY;
int pKey = 0;
int playing = 1;

int main(void)
{
	int menuCode;
	int playing = 1;


	init();
	while (1)
	{
		titleDraw();
		menuCode = menuDraw();

		if (menuCode == 0)
		{
			gLoop();
		}
		else if (menuCode == 1)
		{
			infoDraw();
		}
		else if (menuCode == 2)
		{
			break;
		}
		menuCode = 5;
		system("cls");
	}

	gotoxy(17, 16);
	printf("������ ����Ǿ����ϴ�!!!");
	_getch();

	return 0;
}

void init(void)
{
	system("mode con cols=91 lines=20 | title Escape Game");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������ 
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0; // false �Ǵ� 0 : ����� 
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

	pKey = 0;
	playing = 1;

}

// Ŀ�� ��ġ �̵��Լ�  
void gotoxy(int x, int y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������ 
	COORD pos;
	pos.X = 2*x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

// ù��°: �ؽ�Ʈ, �ι�°: ���  
void setColor(int forground, int background)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������ 
	int code = forground + background * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}


int keyControl(void) {
	char temp = _getch();

	if (temp == 'w' || temp == 'W')
	{
		return UP;
	}
	else if (temp == 'a' || temp == 'A')
	{
		return LEFT;
	}
	else if (temp == 's' || temp == 'S')
	{
		return DOWN;
	}
	else if (temp == 'd' || temp == 'D')
	{
		return RIGHT;
	}
	else if (temp == ' ')
	{ // �����̽���(����)�� ���� ��ư  
		return SUBMIT;
	}
}

void titleDraw(void) {

	printf("\n\n\n\n"); // ������ 4ĭ ����  
	printf("                     ######     ##    #      ##  #######    ####  ###  \n");
	printf("                    #          # ##    #    ##   #         ########### \n");
	printf("                     #####    #   ##    #  ##    ######     #########  \n");
	printf("                         ##  ########    ###     #           ######    \n");
	printf("                    ######  #       ##    #      #######       ##      \n");
}

int menuDraw(void) {
	int x = 20;
	int y = 12;
	gotoxy(x - 1, y); // -2 �� ������ > �� ����ؾ��ϱ� ������  
	printf("> ���ӽ���");
	gotoxy(x, y + 1);
	printf("��������");
	gotoxy(x, y + 2);
	printf("  ����  ");
	while (1) { // ���ѹݺ�  
		int n = keyControl(); // Ű���� �̺�Ʈ�� Ű������ �޾ƿ���  
		switch (n) {
		case UP: { // �Էµ� Ű�� ���� UP�ΰ�� (w) 
			if (y > 12) { // y�� 12~14������ �̵�  
				gotoxy(x - 1, y); // x-2 �ϴ� ������ ">"�� ��ĭ ������ ����ϱ�����  
				printf(" "); // ���� ��ġ�� �����  
				gotoxy(x - 1, --y); // ���� �̵��� ��ġ�� �̵��Ͽ�  
				printf(">"); // �ٽ� �׸���  
			}
			break;
		}

		case DOWN: { // �Էµ� Ű�� ���� DOWN�ΰ�� (s) 
			if (y < 14) { // �ִ� 14  
				gotoxy(x - 1, y);
				printf(" ");
				gotoxy(x - 1, ++y);
				printf(">");
			}
			break;
		}

		case SUBMIT: {
			return y - 12; // �����̽���(����)�Ǿ��� ��� y-12
			// y ���� ��ġ�� 12�����Ƿ� y-12 �� �ϸ� 0, 1, 2 �� ���ڸ� ���� �� �ִ�. 
		}
		}
	}
}

void infoDraw(void)
{
	system("cls"); // ȭ�� ��� �����  
	printf("\n\n");
	printf("                        [ ���۹� ]\n\n");
	printf("                    �̵�: W, A, S, D\n");
	printf("                    ����: �����̽���\n\n\n\n\n\n\n");
	printf("               ������: codevkr.tistory.com\n\n");
	printf("      �����̽��ٸ� ������ ����ȭ������ �̵��մϴ�.");

	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}
void drawMap(void)
{
	char temp;
	system("cls");
	int h, w;
	for (h = 0; h < 14; h++)
	{
		for (w = 0; w < 56; w++)
		{
			temp = tempMap[h][w];
			if (temp == '0')
			{
				setColor(white, black);
				printf("  ");
			}
			else if (temp == '1')
			{
				setColor(white, black);
				printf("��");
			}
			else if (temp == 's')
			{
				//�÷��̾� X,Y ��ġ ����
				pX = w;
				pY = h;
				setColor(cyan, black);
				printf("��");
			}
			else if (temp == 'q')
			{
				setColor(lightgreen, black);
				printf("��");
			}
			else if (temp == 'k')
			{
				setColor(yellow, black);
				printf("*");
			}
			else if (temp == 'l')
			{
				setColor(brown, black);
				printf("+");
			}
		}
		printf("\n");
	}
	setColor(white, black);
}

void gLoop(void)
{
	int mKey;
	memcpy(tempMap, map, sizeof(tempMap));
	drawMap();
	while (playing)
	{
		drawUI();
		mKey = keyControl();
		switch (mKey)
		{
		case UP:
			move(0, -1);
			break;
		case DOWN:
			move(0, 1);
			break;
		case RIGHT:
			move(1, 0);
			break;
		case LEFT:
			move(-1, 0);
			break;
		case SUBMIT:
			playing = 0;
		}

	}
	playing = 1;
}

void move(int _x, int _y)
{
	char mapObject = tempMap[pY + _y][pX + _x];
	setColor(white, black);

	if (mapObject == '0' || mapObject == 's')
	{
		gotoxy(pX, pY);
		printf("  ");

		setColor(cyan, black);
		gotoxy(pX + _x, pY + _y);
		printf("��");
		pX += _x;
		pY += _y;
	}
	//	else if (mapObject == '1')
	//	{
			// �ƹ��ϵ� ���� ����
	//	}
	else if (mapObject == 'k')
	{
		pKey += 1;
		tempMap[pY + _y][pX + _x] = '0';
		gotoxy(pX + _x, pY + _y);
		printf(" ");

	}
	else if (mapObject == 'l')
	{
		if (pKey > 0)
		{
			pKey--;
			tempMap[pY + _y][pX + _x] = '0';
			setColor(white, black);
			gotoxy(pX + _x, pY + _y);
			printf(" ");
		}

	}
	else if (mapObject == 'q')
	{
		playing = 0;
	}
}

void drawUI(void)
{
	setColor(white, black);
	gotoxy(0, 14);
	printf("##########################################################################################");

	gotoxy(3, 16);
	printf("�÷��̾� ��ġ:(%02d,%02d)", pX, pY);

	setColor(yellow, black);
	gotoxy(34, 16);
	printf("����: %d��", pKey);

	setColor(white, black);
}
