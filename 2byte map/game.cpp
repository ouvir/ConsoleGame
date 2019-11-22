// �� ���α׷� �ҽ� �ڵ�� C�� ���� �ְܼ��� ������ ���� ����Ʈ(https://codevkr.tistory.com/15?category=699626)��
// ������Ʈ�� �����Ͽ����ϴ�.

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
	{"1111111111111111111111111111111111111111111111111111111"}, // ���� ���̿� ���߾� 14��   
	{"1000000010000000000000000000000000000000000000000000001"},
	{"1000000010000000000000000000000000000000000000000000001"}, // 0 : �� ���� 
	{"1000100010000000000000000000000000000000000000000000001"}, // 1 : �� 
	{"1000100010000000000000000000000000000000000000000000001"}, // k : ���� 
	{"1000100010000000000000000000000000000000000000000000001"}, // l : ��� �� 
	{"1000100011111100000000000000000000000000000000000000001"}, // q : Ż�ⱸ  
	{"1000100000000100000000000000000000000000000000000000001"},
	{"1000100010000100000000000000000000000000000000000000001"},
	{"1000100010000100000000000000000000000000000000001111111"},
	{"1000100010000100000000000000000000000000000000001000001"},
	{"10s010001111111111111111111111111111111111111111100q001"},
	{"1000100000000000000000000000000000000000000000000000001"},
	{"1111111111111111111111111111111111111111111111111111111"}
};


int keyControl();
void titleDraw();
int menuDraw();

void infoDraw();

void init();
void gotoxy(int, int);
void setColor(int, int);
int maplistDraw(void);

void drawMap(void);

int main(void)
{
	int menuCode;
	init();

	while(1)
	{
		titleDraw();
		menuCode = menuDraw();

		if (menuCode == 0)
		{
			int n = maplistDraw();
			if (n == 0)
			{
				drawMap();
				Sleep(1000);
			}
			else if (n == 1)
			{
				drawMap();
				Sleep(1000);
			}
		}
		else if (menuCode == 1)
		{

			infoDraw();
		}
		else if(menuCode== 2)
		{
			break;
		}
		system("cls");
	}

	return 0;
}

void init() {
	system("mode con cols=56 lines=20 | title Escape Game");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������ 
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0; // false �Ǵ� 0 : ����� 
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

// Ŀ�� ��ġ �̵��Լ�  
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������ 
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

// ù��°: �ؽ�Ʈ, �ι�°: ���  
void setColor(int forground, int background) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������ 
	int code = forground + background * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}




int keyControl() {
	char temp = _getch();

	if (temp == 'w' || temp == 'W') {
		return UP;
	}
	else if (temp == 'a' || temp == 'A') {
		return LEFT;
	}
	else if (temp == 's' || temp == 'S') {
		return DOWN;
	}
	else if (temp == 'd' || temp == 'D') {
		return RIGHT;
	}
	else if (temp == ' ') { // �����̽���(����)�� ���� ��ư  
		return SUBMIT;
	}
}

void titleDraw() {
	printf("\n\n\n\n"); // ������ 4ĭ ����  
	printf("        #####    ###    ###    #    ####   ##### \n");
	printf("        #       #      #      # #   #   #  #     \n");
	printf("        ####    ####   #     #####  ####   ####  \n");
	printf("        #           #  #     #   #  #      #     \n");
	printf("        #####   ####    ###  #   #  #      ##### \n");
}

int menuDraw() {
	int x = 24;
	int y = 12;
	gotoxy(x - 2, y); // -2 �� ������ > �� ����ؾ��ϱ� ������  
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
				gotoxy(x - 2, y); // x-2 �ϴ� ������ ">"�� ��ĭ ������ ����ϱ�����  
				printf(" "); // ���� ��ġ�� �����  
				gotoxy(x - 2, --y); // ���� �̵��� ��ġ�� �̵��Ͽ�  
				printf(">"); // �ٽ� �׸���  
			}
			break;
		}

		case DOWN: { // �Էµ� Ű�� ���� DOWN�ΰ�� (s) 
			if (y < 14) { // �ִ� 14  
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
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

void infoDraw() {
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

int maplistDraw(void)
{
	int x = 24,y = 6, temp;
	system("cls");
	printf("\n\n");
	printf("                     [�� ����]\n\n");
	gotoxy(x - 2, y);
	printf("> ����");
	gotoxy(x, y + 1);
	printf("�����");
	gotoxy(x, y + 2);
	printf("�ڷ�");
	while (1)
	{
		int n = keyControl();
		switch(n)
		{
			case UP:
				if (y > 6)
				{
					gotoxy(x - 2, y);
					printf(" ");
					gotoxy(x - 2, --y);
					printf(">");

				}
				break;
			case DOWN:
				if (y < 8)
				{
					gotoxy(x - 2, y);
					printf(" ");
					gotoxy(x - 2, ++y);
					printf(">");

				}
				break;
			case SUBMIT:
				return y - 6;
		}
	}

}

void drawMap()
{
	char temp;
	system("cls");
	int h, w;
	for (h = 0; h < 14; h++)
	{
		for (w = 0; w < 56; w++)
		{
			temp = map[h][w];
			if (temp == '0')
			{
				setColor(black, black);
				printf(" ");
			}
			else if (temp == '1')
			{
				setColor(white, white);
				printf("#");
			}
			else if (temp == 's')
			{
				setColor(cyan, black);
				printf("@");
			}
			else if (temp == 'q')
			{
				setColor(lightgreen, black);
				printf("O");
			}
		}
		printf("\n");
	}
	setColor(white, black);
	Sleep(3000);
}

