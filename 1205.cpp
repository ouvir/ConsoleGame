#
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// 키보드 값  
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 // 선택(스페이스바)  

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

char tempMap[14][56]; // 맵 임시저장할 배열  
char map[20][14][56] = { // 쉬운맵  
	// 가로 숫자는 위 배열크기에 맞추어 56개
	// 맵1
	{
	{"000000000000000000000000000000000000000000000"}, //1
	{"000000000000000000000000000000000000000000000"}, //2
	{"00000000000000000TH"}, //3
	{"000000000000000000000000000000000000000000000"}, //4
	{"000000000000000000111111111000000000000000000"}, //5
	{"0000000000000000001000000T1000000000000000000"}, //6
	{"000000000000000000100000001000000000000000000"}, //7
	{"000000000000000000100000001000000000000000000"}, //8
	{"000000000000000000100000001000000000000000000"}, //9
	{"000000000000000000100000001000000000000000000"}, //10
	{"000000000000000000100000001000000000000000000"}, //11
	{"0000000000000000001s0000001000000000000000000"}, //12
	{"000000000000000000111111111000000000000000000"}, //13
	{"000000000000000000000000000000000000000000000"}, //14
	},
	{
	{"000000000000000000000000000000000000000000000"}, //1
	{"000000000000000000000000000000000000000000000"}, //2
	{"00000000cH"}, //3
	{"000000000000000000000000000000000000000000000"}, //4
	{"000000000000000000111111111000000000000000000"}, //5
	{"0000000000000000001000000T1000000000000000000"}, //6
	{"000000000000000000100000001000000000000000000"}, //7
	{"0000000000000000001000c0001000000000000000000"}, //8
	{"000000000000000000100ccc001000000000000000000"}, //9
	{"0000000000000000001000c0001000000000000000000"}, //10
	{"000000000000000000100000001000000000000000000"}, //11
	{"0000000000000000001s0000001000000000000000000"}, //12
	{"000000000000000000111111111000000000000000000"}, //13
	{"000000000000000000000000000000000000000000000"}, //14
	},
	{
	{"000000000000000000000000000000000000000000000"}, //1
	{"0000000000dH"}, //2
	{"000000000000J"}, //3
	{"000000000000000000000000000000000000000000000"}, //4
	{"000000000000000000111111111000000000000000000"}, //5
	{"0000000000000000001000000T1000000000000000000"}, //6
	{"000000000000000000100000001000000000000000000"}, //7
	{"000000000000000000100000001000000000000000000"}, //8
	{"0000000000000000001d0000001000000000000000000"}, //9
	{"000000000000000000100000001000000000000000000"}, //10
	{"000000000000000000100000001000000000000000000"}, //11
	{"0000000000000000001s00d0001000000000000000000"}, //12
	{"000000000000000000111111111000000000000000000"}, //13
	{"000000000000000000000000000000000000000000000"}, //14
	},
	{
	{"000000000000000000000000000000000000000000000"}, //1
	{"000000000kH"}, //2
	{"00000000000000DJ"}, //3
	{"000000000000000000000000000000000000000000000"}, //4
	{"000000000000000000111111111000000000000000000"}, //5
	{"0000000000000000001Dl0001T1000000000000000000"}, //6
	{"0000000000000000001l0000011000000000000000000"}, //7
	{"000000000000000000100000001000000000000000000"}, //8
	{"0000000000000000001k0000001000000000000000000"}, //9
	{"000000000000000000100000001000000000000000000"}, //10
	{"000000000000000000100000001000000000000000000"}, //11
	{"0000000000000000001s00000d1000000000000000000"}, //12
	{"000000000000000000111111111000000000000000000"}, //13
	{"000000000000000000000000000000000000000000000"}, //14
	},
	{
	{"000000000000000000000000000000000000000000000"}, // 세로 길이에 맞추어 14줄   
	{"000000000000000000000000000000000000000000000"},
	{"000000000000000000000000000000000000000000000"}, // 0 : 빈 공간 
	{"000000000000000000000000000000000000000000000"}, // 1 : 벽 
	{"000000000000000000000000000000000000000000000"}, // k : 열쇠
	{"000000000000000000000000000000000000000000000"}, // l : 잠긴 문 
	{"000000001111111111111111111111111111100000000"}, // q : 탈출구 
	{"00000000100000ccc0000000000000000000100000000"}, // T : 다음으로
	{"00000000100000ccc000000000d000000000100000000"}, // c : 코인
	{"0000000010000000000000s0000000000000100000000"}, // D : 곡괭이
	{"000000001000000000000000000000000000100000000"},
	{"000000001000000000d000000000ccc00000100000000"},
	{"000000001T000000000000000000ccc00000100000000"},
	{"000000001111111111111111111111111111100000000"}
	},//맵2 
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
	{"000000001d0010000k100000010000000000100000000"},
	{"0000000010001000001000k0010000000000100000000"},
	{"000000001000100000100000010000000000100000000"},
	{"000000001s00l000001000000l0000000000100000000"},
	{"000000001111111111111111111111111111100000000"}
	},//맵3 
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
	{ //맵 4
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
	},//맵5
	{
	{"000000000000000001111111111100000000000000000"},
	{"000000000000000011111111111110000000000000000"},
	{"000000000000000111111111111111000000000000000"},
	{"000000000000000111111111111111000000000000000"},
	{"0000DD000000000111111111111111000000000000000"},
	{"00000000000000011D000111000011000000000000q00"},
	{"0000s0000000000110D0011100T011000000000000000"},
	{"0000000000000001100D1111100011000000000000000"},
	{"0000000000000001111111c1111111000000000000000"},
	{"000000000000000111111cDc111111000000000000000"},
	{"00000d000000000011111D1D111110000000000000000"},
	{"000000000000000001111111111100000000000000000"},
	{"000000000000000001101101101100000000000000000"},
	{"000000000000000001101101101100000000000000000"},
	},
	{ //맵 7
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
	},
	{
{ "111111111111111111111111111111111111111111111" }, // 세로 길이에 맞추어 14줄   
{ "100000100000100000100000100000100000100000s01" },
{ "100100000100000100000100000100000100000100001" }, // 0 : 빈 공간 
{ "100000100000100000100000100000100000100000101" }, // 1 : 벽 
{ "100100000100000100000100000100000100000100001" }, // k : 열쇠 
{ "100000100000100000100000100000100000100000101" }, // l : 잠긴 문 
{ "100100000100000100000100000100000100000100001" }, // q : 탈출구  
{ "1T0000100000100000100000100000100000100000101" },
{ "100100000100000100000100000100000100000100001" },
{ "100000100000100000100000100000100000100000101" },
{ "100100000100000100000100000100000100000100001" },
{ "100000100000100000100000100000100000100000101" },
{ "100100000100000100000100000100000100000100001" },
{ "111111111111111111111111111111111111111111111" }
	},
{
{ "111111111111111111111111111111111111111111111" }, // 세로 길이에 맞추어 14줄   
{ "1s010000k000000000001001000000100000100000nn1" },
{ "100100000000000000001001000000100000100000nn1" }, // 0 : 빈 공간 
{ "100100010001000001111001001111100100100100111" }, // 1 : 벽 
{ "10010001000010000100000000100l000100100100111" }, // k : 열쇠 
{ "10010001000110001000000000100l000100100100111" }, // l : 잠긴 문 
{ "100100010000000100000001001001100100100100111" }, // q : 탈출구  
{ "100100010000001000000001000001100100100100111" },
{ "100100010000010000011ll1000001100100100100001" },
{ "100100001000100000110001001001100100100100001" },
{ "100100010001000001100001001001100100100111ll1" },
{ "100100000000000011000001001000100100000001001" },
{ "10000000000000011100000100100010k1000000010T1" },
{ "111111111111111111111111111111111111111111111" }
},
{
{ "111111111111111111111111111111111111111111111" }, // 세로 길이에 맞추어 14줄   
{ "1s010000k000000000001001000000100000100000nn1" },
{ "100100000000000000001001000000100000100000nn1" }, // 0 : 빈 공간 
{ "100100010001000001111001001111100100100100111" }, // 1 : 벽 
{ "10010001000010000100000000100l000100100100111" }, // k : 열쇠 
{ "10010001000110001000000000100l000100100100111" }, // l : 잠긴 문 
{ "100100010000000100000001001001100100100100111" }, // q : 탈출구  
{ "100100010000001000000001000001100100100100111" },
{ "100100010000010000011ll1000001100100100100001" },
{ "100100001000100000110001001001100100100100001" },
{ "100100010001000001100001001001100100100111ll1" },
{ "100100000000000011000001001000100100000001001" },
{ "10000000000000011100000100100010k1000000010T1" },
{ "111111111111111111111111111111111111111111111" }
},
{
{"111111111111111111111111111111111111111111111"},
{"100000000000000000000000000000000000000000001"},
{"100000001110001111000000011000001111001000001"},
{"100111000110000000001100111000000000000000001"},
{"100000000001100000110000000000010000111001001"},
{"100111001000010000000011110001110001110001001"},
{"100111000100000011000000000000100001110001001"},
{"100100000110011100000000110000011000000000001"},
{"100100000110000000000001001100000000000010001"},
{"100000111100000011111000000011100011000010001"},
{"100100000000000000000000000001000000000000001"},
{"100100111100011111001111001111000111110000001"},
{"1q00000000000000000000000000000000000000000s1"},
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
int pKey = 0, pCoin = 0, pLife = 3;
int pPx = 0, score = 0;
int playing = 1;

int main(void)
{
	int menuCode;
	int playing = 1;

	init();
	while (1)
	{	
		pPx = 0;
		pKey = 0;
		pCoin = 0;
		pLife = 3;
		k = 0;
		score = 0;
		
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
	printf("게임이 종료되었습니다!!!");
	_getch();

	return 0;
}

void init(void)
{
	system("mode con cols=91 lines=20 | title Save the Heart");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기 
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0; // false 또는 0 : 숨기기 
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

	pKey = 0;
	playing = 1;

}

// 커서 위치 이동함수  
void gotoxy(int x, int y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기 
	COORD pos;
	pos.X = 2 * x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

// 첫번째: 텍스트, 두번째: 배경  
void setColor(int forground, int background)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기 
	int code = forground + background * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}


int keyControl(void) {
	int temp;
	temp = _getch();
	if (temp == 224)
	{
		temp = _getch();
		switch (temp)
		{
		case 72:
			return UP;
			break;
		case 75:
			return LEFT;
			break;
		case 77:
			return RIGHT;
			break;
		case 80:
			return DOWN;
			break;
		default:
			break;
		}
	}
	else
	{
		if (temp == 119 || temp == 87)
		{
			return UP;
		}
		else if (temp == 97 || temp == 65)
		{
			return LEFT;
		}
		else if (temp == 115 || temp == 83)
		{
			return DOWN;
		}
		else if (temp == 100 || temp == 68)
		{
			return RIGHT;
		}
		else if (temp == ' ')
		{ // 스페이스바(공백)이 선택 버튼  
			return SUBMIT;
		}
	}
}

void titleDraw(void) {

	printf("\n\n\n\n"); // 맨위에 4칸 개행  
	printf("                     #####      ##    #      ##  #######    ###  ####  \n");
	printf("                    #          # ##    #    ##   #         ########### \n");
	printf("                     #####    #   ##    #  ##    ######     #########  \n");
	printf("                         ##  ########    ###     #           ######    \n");
	printf("                    ######  #       ##    #      #######       ##      \n");
}
void ClearDraw(void) {

	printf("\n\n\n\n"); // 맨위에 4칸 개행  
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

	printf("\n\n\n\n"); // 맨위에 4칸 개행  
	printf("           ########  ##    ##  ########      ########  ###    ##  ######    \n");
	printf("              ##     ##    ##  ##            ##        ####   ##  ##    ##  \n");
	printf("              ##     ########  #######       #######   ## ### ##  ##    ##  \n");
	printf("              ##     ##    ##  ##            ##        ##  #####  ##    ##  \n");
	printf("              ##     ##    ##  ########      ########  ##     ##  #######   \n\n\n\n\n");
	printf("                                        Score: %d \n\n", score);
	printf("                                        Stage: %d", k); 
	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}

void DieDraw(void) {

	printf("\n\n\n\n"); // 맨위에 4칸 개행  
	printf("                     ##    ##      ######      ##    #######    ######    \n");
	printf("                     ##    ##      ##    ##          ##         ##    ##  \n");
	printf("                     ##    ##      ##    ##    ##    #######    ##    ##  \n");
	printf("                     ##    ##      ##    ##    ##    ##         ##    ##  \n");
	printf("                      ######       #######     ##    #######    #######   \n\n\n\n\n");
	printf("                                          Life: %d", pLife);
	score -= 1000;
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
	printf("ㅡㅡㅡㅡㅡㅡㅡㅡ");
	gotoxy(x - 3, y - 1);
	printf("ㅣ                ㅣ");
	gotoxy(x - 3, y); // -2 한 이유는 > 를 출력해야하기 때문에  
	printf("ㅣ  > 게임시작    ㅣ");
	gotoxy(x - 3, y + 1);
	printf("ㅣ    게임정보    ㅣ");
	gotoxy(x - 3, y + 2);
	printf("ㅣ      종료      ㅣ");
	gotoxy(x - 3, y + 3);
	printf("ㅣ                ㅣ");
	gotoxy(x - 2, y + 4);
	printf("ㅡㅡㅡㅡㅡㅡㅡㅡ");

	while (1) { // 무한반복  
		int n = keyControl(); // 키보드 이벤트를 키값으로 받아오기  
		switch (n) {
		case UP: { // 입력된 키의 값이 UP인경우 (w) 
			if (y > 12) { // y는 12~14까지만 이동  
				gotoxy(x - 1, y); // x-2 하는 이유는 ">"를 두칸 이전에 출력하기위해  
				printf(" "); // 원래 위치를 지우고  
				gotoxy(x - 1, --y); // 새로 이동한 위치로 이동하여  
				printf(">"); // 다시 그리기  
			}
			break;
		}

		case DOWN: { // 입력된 키의 값이 DOWN인경우 (s) 
			if (y < 14) { // 최대 14  
				gotoxy(x - 1, y);
				printf(" ");
				gotoxy(x - 1, ++y);
				printf(">");
			}
			break;
		}

		case SUBMIT: {
			return y - 12; // 스페이스바(선택)되었을 경우 y-12
			// y 시작 위치가 12였으므로 y-12 를 하면 0, 1, 2 세 숫자를 받을 수 있다. 
		}
		}
	}
}

void infoDraw(void)
{
	system("cls"); // 화면 모두 지우기  
	printf("\n\n");
	printf("                                      <기본 조작법>\n\n");
	printf("                              W, A, S, D 혹은 방향키로 이동\n\n");
	printf("                          스페이스바로 선택 혹은 메인메뉴로 이동\n\n\n\n\n\n");
	printf("                              개발자: 권규현, 김경훈, 김상민\n");
	printf("               ");

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
				printf("▤");
			}
			else if (temp == 's')
			{
				//플레이어 X,Y 위치 저장
				pX = w;
				pY = h;
				setColor(red, black);
				printf("♥");
			}
			else if (temp == 'q')
			{
				setColor(lightgreen, black);
				printf("▣");
			}
			else if (temp == 'c')
			{
				setColor(yellow, black);
				printf("⊙");
			}
			else if (temp == 'k')
			{
				setColor(yellow, black);
				printf("§");
			}
			else if (temp == 'l')
			{
				setColor(brown, black);
				printf("▒");
			}
			else if (temp == 'T')
			{
				setColor(lightgreen, black);
				printf("◎");
			}
			else if (temp == 'd')
			{
				setColor(lightred, black);
				printf("ⓧ");
			}
			else if (temp == 'D')
			{
				setColor(11, black);
				printf("ヤ");
			}
			else if (temp == 'H')
			{
				if (k == 0) {

					setColor(white, black);
					printf("-다음 맵으로 이동합니다.");
				}
				if (k == 1) {

					setColor(white, black);
					printf("-코인. 획득시 점수를 올려줍니다. 15개를 모으면 Life를 얻습니다.");
				}
				if (k == 2) {

					setColor(white, black);
					printf("-함정. 닿을 경우 Life를 하나 잃고 스테이지를 재시작합니다.");
				}
				if (k == 3) {

					setColor(white, black);
					printf("-열쇠. 획득시 잠긴 문(▒)을 하나 열 수 있습니다.");
				}
			}
			else if (temp == 'J')
			{
				if (k == 2) {
					setColor(white, black);
					printf("Life가 0인 상태에서 사망시 게임오버.");
				}
				if (k == 3) {
					setColor(white, black);
					printf("-곡괭이. 획득시 벽을 하나 파괴할 수 있습니다.");
				}
				
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

void die(void)
{
	gotoxy(pX, pY);
	setColor(11, black); //11 = 밝은 하늘색
	int i;
	for (i = 1; i <= 5; i++) {
		gotoxy(pX, pY);
		printf("♡");
		Sleep(100);
		gotoxy(pX, pY);
		printf("♥");
		Sleep(100);
	}

	gotoxy(pX, pY);
	printf("■");
	Sleep(100);
	gotoxy(pX, pY);
	printf("▦");
	Sleep(100);
	gotoxy(pX, pY);
	printf("▒");
	Sleep(100);
	gotoxy(pX, pY);
	printf("  ");
	Sleep(100);
}

void move(int _x, int _y)
{
	char mapObject = tempMap[pY + _y][pX + _x];
	setColor(white, black);

	if (mapObject == '0' || mapObject == 's')
	{
		gotoxy(pX, pY);
		printf("  ");

		setColor(red, black);
		gotoxy(pX + _x, pY + _y);
		printf("♥");
		pX += _x;
		pY += _y;
	}
	else if (mapObject == '1')
	{
		// 아무일도 하지 않음
		if (pPx >= 1)
		{
			pPx -= 1;
			tempMap[pY + _y][pX + _x] = '0';
			gotoxy(pX, pY);
			printf("  ");
			gotoxy(pX + _x, pY + _y);
			setColor(red, black);
			printf("♥");
			pX += _x;
			pY += _y;
			score += 100;

		}
	}
	else if (mapObject == 'c')
	{
		pCoin += 1;
		tempMap[pY + _y][pX + _x] = '0';
		gotoxy(pX, pY);
		printf("  ");
		gotoxy(pX + _x, pY + _y);
		setColor(red, black);
		printf("♥");
		pX += _x;
		pY += _y;
		score += 100;
		if (pCoin >= 15)
		{
			pLife += 1;
			pCoin -= 15;
		}

	}
	else if (mapObject == 'k')
	{
		pKey += 1;
		tempMap[pY + _y][pX + _x] = '0';
		gotoxy(pX, pY);
		printf("  ");
		gotoxy(pX + _x, pY + _y);
		setColor(red, black);
		printf("♥");
		pX += _x;
		pY += _y;
		score += 100;
	}
	else if (mapObject == 'D')
	{
		pPx += 1;
		tempMap[pY + _y][pX + _x] = '0';
		gotoxy(pX, pY);
		printf("  ");
		gotoxy(pX + _x, pY + _y);
		setColor(red, black);
		printf("♥");
		pX += _x;
		pY += _y;
		score += 100;
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
			score += 100;
		}

	}
	else if (mapObject == 'q')
	{
		system("cls");
		EndDraw();
		system("cls");
		playing = 0;
		score += 1000;
	}
	else if (mapObject == 'd')
	{
		if (pLife == 0) {
			die();
			score -= 1000;
			setColor(white, black);

			system("cls");
			EndDraw();
			system("cls");
			playing = 0;
		}
		else {
			die();
			setColor(white, black);
			pPx = 0;
			system("cls");;
			pLife--;		
			DieDraw();
			system("cls");
			memcpy(tempMap, *map[k], sizeof(tempMap));
			drawMap();
		}
	}
	else if (mapObject == 'T')
	{	
		pPx = 0;
		system("cls");
		ClearDraw();
		system("cls");
		k++;
		score += 1000;
		memcpy(tempMap, *map[k], sizeof(tempMap));
		drawMap();
	}
}

void drawUI(void)
{
	int i;
	setColor(white, black);
	gotoxy(0, 14);
	printf("##########################################################################################");

	setColor(red, black);
	gotoxy(6, 16);
	printf("Life:");
	for (i = 0; i < pLife; i++) { printf("♥"); }

	gotoxy(4, 17);
	setColor(white, black);
	printf("플레이어 위치:(%02d,%02d)", pX, pY);

	setColor(yellow, black);
	gotoxy(34, 16);
	printf("Key: %d개", pKey);
	gotoxy(34, 18);
	printf("Coin: %d개", pCoin);
	gotoxy(26, 18);
	printf("Pickaxe: %d개", pPx);
	setColor(13, black);
	gotoxy(26, 16);
	printf("Score: %d점", score);

	setColor(white, black);
}