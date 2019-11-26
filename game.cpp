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
	white,
	gray
};

char tempMap[14][56]; // �� �ӽ������� �迭  
char map[8][14][56] = { // �� �߰��� ù ���� ũ�� �����ϼ���
	// ���� ���ڴ� �� �迭ũ�⿡ ���߾� 56��
	{
	{"000000000000000000000000000000000000000000000"}, //1
	{"0000000000000000000000H0000000000000000000000"}, //2
	{"000000000000000000000000000000000000000000000"}, //3
	{"000000000000000000000000000000000000000000000"}, //4
	{"000000000000000000111111111000000000000000000"}, //5
	{"0000000000000000001000000T1000000000000000000"}, //6
	{"000000000000000000100000001000000000000000000"}, //7
	{"0000000000000000001000s0001000000000000000000"}, //8
	{"000000000000000000100000001000000000000000000"}, //9
	{"0000000000000000001q0000001000000000000000000"}, //10
	{"000000000000000000111111111000000000000000000"}, //11
	{"000000000000000000000000000000000000000000000"}, //12
	{"000000000000000000000000000000000000000000000"}, //13
	{"000000000000000000000000000000000000000000000"}, //14
	},
	// ��1
	{
	{"000000000000000000000000000000000000000000000"}, // ���� ���̿� ���߾� 14��   
	{"000000000000000000000000000000000000000000000"},
	{"000000000000000000000000000000000000000000000"}, // 0 : �� ���� 
	{"000000000000000000000000000000000000000000000"}, // 1 : �� 
	{"000000000000000000000000000000000000000000000"}, // k : ����
	{"000000000000000000000000000000000000000000000"}, // l : ��� �� 
	{"000000001111111111111111111111111111100000000"}, // q : Ż�ⱸ 
	{"0000000010000cqc00000000000000000000100000000"}, // T : ��������
	{"0000000010000ccc00000000000000000000100000000"}, // c : ����
	{"0000000010000000000000s0000000000000100000000"},
	{"000000001000000000000000000000000000100000000"},
	{"000000001000000000000000000000000ccc100000000"},
	{"000000001T00000000000000000000000ccc100000000"},
	{"000000001111111111111111111111111111100000000"}
	},
	//��2 
	{
	{"000000000000000000000000000000000000000000000"},
	{"000000000000000000000000000000000000000000000"},
	{"111111111111111111111111111111111111111111111"},
	{"000000000000000000000000000000000000000000000"},
	{"000000000000000000000000000000000000000000000"},
	{"000000000000000000000000000000000000000000000"},
	{"000000001111111111111111111111111111100000000"},
	{"00000000100010000010000001000000000T100000000"},
	{"00000000100k100000l00000010000000000100000000"},
	{"000000001q0010000k100000010000000000100000000"},
	{"0000000010001000001000k0010000000000100000000"},
	{"000000001000100000100000010000000000100000000"},
	{"000000001s00l000001000000l0000000000100000000"},
	{"000000001111111111111111111111111111100000000"}
	},
	//��3 
	{
	{"000000000000000000000000000000000000000000000"},
	{"000000000000000000000000000000000000000000000"},
	{"111111111111111111111111111111111111111111111"},
	{"000000000000000000000000000000000000000000000"},
	{"000000000000000000000000000000000000000000000"},
	{"000000000000000000000000000000000000000000000"},
	{"000000001111111111111111111111111111100000000"},
	{"00000000100100c00000000100000000000T100000000"},
	{"000000001011011010001111000cc00cc000100000000"},
	{"0000000010c101s010c010010cc00cc00cc0100000000"},
	{"0000000011000111101111010cc00000cc00100000000"},
	{"00000000100100001000000100cc000cc000100000000"},
	{"00000000100100000010ccc00000cc000000100000000"},
	{"000000001111111111111111111111111111100000000"}
	},
	{ //�� 4
	{"111111111111111111111111111111111111111111111"},
	{"1000000000000000000000k0000000000000000000001"},
	{"100000000000000000000000000000000000000000001"},
	{"100000000000000000000000000000000000000000001"},
	{"111110000000000000000000000000000000000000001"},
	{"100010000000000000000000000000000000000000001"},
	{"1T00l0000000000000000000000000000000000000001"},
	{"100010000000000000000000000000000000000000001"},
	{"111110000000000000000000000000000000000000001"},
	{"100000000000000000000000000000000000000000001"},
	{"100000000000000000000000000000000000000000001"},
	{"100000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000s1"},
	{"111111111111111111111111111111111111111111111"}
	},//��5
	{
	{"000000000000000000000000000000000000000000000"},
	{"000000000000011111111111000000000000000000000"},
	{"000000000000111111111111100000000000000000000"},
	{"000000000001111111111111110000000000000000000"},
	{"000000000001111111111111110000000000000000000"},
	{"000000000001100001110000110000000000000000T00"},
	{"0000s0000001100001110000110000000000000000000"},
	{"000000000001100011111000110000000000000000000"},
	{"000000000001111111011111110000000000000000000"},
	{"000000000001111110001111110000000000000000000"},
	{"000000000000111110101111100000000000000000000"},
	{"000000000000011111111111000000000000000000000"},
	{"000000000000011011011011000000000000000000000"},
	{"000000000000011011011011000000000000000000000"},
	},//��6
	{
	{"111111111111111111111111111111111111111111111"},
	{"1000000000000000000000k0000000000000000000001"},
	{"1000bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb0001"},
	{"1000bccccccccccccccccccccccccccccccccccccccb0001"},
	{"1000bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb0001"},
	{"1qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq1"},
	{"1T00b00000000b00000000b000000000b000000000001"},
	{"10000000b00000000b000000000b000000000b000q001"},
	{"1qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq1"},
	{"1000bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb0001"},
	{"1000bccccccccccccccccccccccccccccccccccccccb0001"},
	{"1000bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb0001"},
	{"100000000000000000000000000000000000000000001"},
	{"111111111111111111111111111111111111111111111"}
	},
	{ //�� 7
	{"111111111111111111111111111111111111111111111"},
	{"100000000000000001000000000011000000001000001"},
	{"100000001000001000001000000000010000000000001"},
	{"100001000001000000000000100000000000010000001"},
	{"100000001000000000100000000000000000000000001"},
	{"100100000000100000000001000000010000000000001"},
	{"1T0010001000000010001000000000000000000100001"},
	{"100100100001000000000000001000001000000000001"},
	{"100000000000001000000100000100000000000000001"},
	{"100010000010000000100000100000001000010000001"},
	{"110000100000001000000100000000000000000000001"},
	{"100000000001000000100000001000000001000000001"},
	{"1001000001000001000000010000100000001000000s1"},
	{"111111111111111111111111111111111111111111111"}
	}
};
int k = 0;

int keyControl(void);
void titleDraw(void);
int menuDraw(void);

void infoDraw(void);
void ClearDraw(void);
void EndDraw(void);

void init();
void gotoxy(int, int);
void setColor(int, int);
void drawMap(void);
void move(int _x, int _y);
void gLoop(char* A);
void drawUI(void);


int pX, pY;
int pKey = 0, pCoin = 0;
int playing = 1;

int main(void)
{
	int menuCode;
	int playing = 1;

	init();
	while (1)
	{
		pKey = 0;
		pCoin = 0;
		k = 0;
		titleDraw();
		menuCode = menuDraw();

		if (menuCode == 0)
		{
			gLoop(*map[k]);
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
	system("mode con cols=91 lines=20 | title Save the Heart");

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
	pos.X = 2 * x;
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
	printf("                     #####      ##    #      ##  #######    ###  ####  \n");
	printf("                    #          # ##    #    ##   #         ########### \n");
	printf("                     #####    #   ##    #  ##    ######     #########  \n");
	printf("                         ##  ########    ###     #           ######    \n");
	printf("                    ######  #       ##    #      #######       ##      \n");
}
void ClearDraw(void) {

	printf("\n\n\n\n"); // ������ 4ĭ ����  
	printf("                ######   ####       ########     ##      ########     ##   \n");
	printf("              ##          ##        ##          # ##     ##     ##    ##   \n");
	printf("              ##          ##        #######    #   ##    ########     ##   \n");
	printf("              ##          ##        ##        ########   ##    ##          \n");
	printf("                ######   #########  ######## #       ##  ##     ##    ##   \n");
	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}

void EndDraw(void) {

	printf("\n\n\n\n"); // ������ 4ĭ ����  
	printf("           ########  ##    ##  ########      ########  ###    ##  ######    \n");
	printf("              ##     ##    ##  ##            ##        ####   ##  ##    ##  \n");
	printf("              ##     ########  #######       #######   ## ### ##  ##    ##  \n");
	printf("              ##     ##    ##  ##            ##        ##  #####  ##    ##  \n");
	printf("              ##     ##    ##  ########      ########  ##     ##  #######   \n");
	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}

int menuDraw(void) {
	int x = 20;
	int y = 12;
	gotoxy(x - 2, y - 2);
	printf("�ѤѤѤѤѤѤѤ�");
	gotoxy(x - 3, y - 1);
	printf("��                ��");
	gotoxy(x - 3, y); // -2 �� ������ > �� ����ؾ��ϱ� ������  
	printf("��  > ���ӽ���    ��");
	gotoxy(x - 3, y + 1);
	printf("��    ��������    ��");
	gotoxy(x - 3, y + 2);
	printf("��      ����      ��");
	gotoxy(x - 3, y + 3);
	printf("��                ��");
	gotoxy(x - 2, y + 4);
	printf("�ѤѤѤѤѤѤѤ�");

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
			else if (temp == 'c')
			{
				setColor(yellow, black);
				printf("��");
			}
			else if (temp == 'k')
			{
				setColor(yellow, black);
				printf("��");
			}
			else if (temp == 'l')
			{
				setColor(brown, black);
				printf("��");
			}
			else if (temp == 'T')
			{
				setColor(lightgreen, black);
				printf("��");
			}
			else if (temp == 'b')
			{
				setColor(gray, black);
				printf("��");
			}
			else if (temp == 'H')
			{
				setColor(white, black);
				printf("Ʃ�丮��");
			}
			else if (temp == 'e')
			{
				setColor(blue, black);
				printf("��");
			}
		}
		printf("\n");
	}
	setColor(white, black);
}

void gLoop(char* A)
{
	int mKey;
	memcpy(tempMap, A, sizeof(tempMap));
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
	else if (mapObject == 'c')
	{
		pCoin += 1;
		tempMap[pY + _y][pX + _x] = '0';
		gotoxy(pX, pY);
		printf("  ");
		gotoxy(pX + _x, pY + _y);
		setColor(cyan, black);
		printf("��");
		pX += _x;
		pY += _y;


	}
	else if (mapObject == 'k')
	{
		pKey += 1;
		tempMap[pY + _y][pX + _x] = '0';
		gotoxy(pX, pY);
		printf("  ");
		gotoxy(pX + _x, pY + _y);
		setColor(cyan, black);
		printf("��");
		pX += _x;
		pY += _y;
	}
	else if (mapObject == 'l')
	{
		if (pKey > 0)
		{
			pKey--;
			tempMap[pY + _y][pX + _x] = '0';
			setColor(white, black);
			gotoxy(pX + _x, pY + _y);
			printf("  ");
		}

	}
	else if (mapObject == 'q')
	{
		system("cls");
		EndDraw();
		system("cls");
		playing = 0;
	}
	/*
	if (mapObject == '0' || mapObject == 'e')
	{	gotoxy(pX, pY);
		printf("  ");
		tempMap[pY + _y][pX + _x] = '0';
		setColor(cyan, black);
		pY++;
		if (pY ==12) {
			pY = 0;
		}
		system("cls");
		ClearDraw();
		system("cls");
		memcpy(tempMap, *map[k], sizeof(tempMap));
		drawMap();
	}
	*/
	else if (mapObject == 'T')
	{
		system("cls");
		ClearDraw();
		system("cls");
		k++;
		memcpy(tempMap, *map[k], sizeof(tempMap));
		drawMap();
	}
	else if (mapObject == 'b')
	{
		system("cls");
		EndDraw();
		system("cls");
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
	gotoxy(34, 18);
	printf("����: %d��", pCoin);

	setColor(white, black);
}
