// �� ���α׷� �ҽ� �ڵ�� C�� ���� �ְܼ��� ������ ���� ����Ʈ( https://codevkr.tistory.com/15?category=699626)��
//������Ʈ�� �����Ͽ����ϴ�. 

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


int keyControl();
void titleDraw();
int menuDraw(); 
void drawMap();
void infoDraw();

void init(); 
void gotoxy(int, int);
void setColor(int, int);


int main(void) {
	int menuCode;
	init();
	while (1)
	{
		system("cls"); // ȭ�� ��� �����
		titleDraw();
		menuCode = menuDraw();
		switch (menuCode)
		{
			case 0:
				drawMap();
				break;
			case 1:
				infoDraw();
				break;
			case 2:
				return 0;
		}

	}
	titleDraw();
	menuCode = menuDraw();
	printf("Selected Menu:%d", menuCode);
	
	return 0;
}

void init(){
	system("mode con cols=56 lines=20 | title ��������"); 
	
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������ 
	CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = 0; // false �Ǵ� 0 : ����� 
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(consoleHandle , &ConsoleCursor);
}

// Ŀ�� ��ġ �̵��Լ�  
void gotoxy(int x, int y){
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������ 
	COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
} 

// ù��°: �ؽ�Ʈ, �ι�°: ���  
void setColor(int forground, int background){
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������ 
	int code = forground + background * 16; 
	SetConsoleTextAttribute(consoleHandle, code);
}




int keyControl(){
	char temp = _getch();
	
	if(temp == 'w' || temp == 'W'){
		return UP;
	} else if(temp == 'a' || temp == 'A'){
		return LEFT;
	} else if(temp == 's' || temp == 'S'){
		return DOWN;
	} else if(temp == 'd' || temp == 'D'){
		return RIGHT;
	} else if(temp == ' '){ // �����̽���(����)�� ���� ��ư  
		return SUBMIT;
	}
}

void titleDraw(){
	printf("\n\n\n"); // ������ 3ĭ ����  
	printf("              #####                  #######   \n");
	printf("            ##     ##                #     #   \n");
	printf("            #       #                #######   \n");
	printf("             #     #                    #      \n");
	printf("              ####                 ########### \n");
	printf("                #                              \n");
	printf("                #                   #########  \n");
	printf("          ##############                    #  \n");
} 

int menuDraw(){
	int x = 24; 
	int y = 12;
	gotoxy(x-2, y); // -2 �� ������ > �� ����ؾ��ϱ� ������  
	printf("> ���ӽ���");
	gotoxy(x, y+1);
	printf("��������");
	gotoxy(x, y+2);
	printf("  ����  ");
	while(1){ // ���ѹݺ�  
		int n = keyControl(); // Ű���� �̺�Ʈ�� Ű������ �޾ƿ���  
		switch(n){
			case UP: { // �Էµ� Ű�� ���� UP�ΰ�� (w) 
				if(y > 12){ // y�� 12~14������ �̵�  
					gotoxy(x-2, y); // x-2 �ϴ� ������ ">"�� ��ĭ ������ ����ϱ�����  
					printf(" "); // ���� ��ġ�� �����  
					gotoxy(x-2, --y); // ���� �̵��� ��ġ�� �̵��Ͽ�  
					printf(">"); // �ٽ� �׸���  
				}
				break;
			}
				
			case DOWN: { // �Էµ� Ű�� ���� DOWN�ΰ�� (s) 
				if(y < 14) { // �ִ� 14  
					gotoxy(x-2, y);
					printf(" ");
					gotoxy(x-2, ++y);
					printf(">");
				}
				break;
			}
			
			case SUBMIT: {
				return y-12; // �����̽���(����)�Ǿ��� ��� y-12
				// y ���� ��ġ�� 12�����Ƿ� y-12 �� �ϸ� 0, 1, 2 �� ���ڸ� ���� �� �ִ�. 
			}
		}
	}
} 

void infoDraw(){
	system("cls"); // ȭ�� ��� �����  
	printf("\n\n");
	printf("                        [ ���۹� ]\n\n");
	printf("                    �̵�: W, A, S, D\n");
	printf("                    ����: �����̽���\n\n\n\n\n\n\n");
	printf("               ������: codevkr.tistory.com\n\n");
	printf("      �����̽��ٸ� ������ ����ȭ������ �̵��մϴ�.");
	
	while(1){
		if(keyControl() == SUBMIT){
			system("cls");
			break;
		}
	}
}

void drawMap(){
	system("cls"); // ȭ�� ��� �����
	printf("\n\n"); // ������ 2ĭ ���� 
	printf("O:���� ��, X:�� ��\n");
	printf("| | | | | | | | | | | | | | | | |\n");
	printf("| | | | | | | | | | | | | | | | |\n");
	printf("| | | | | | | | | | | | | | | | |\n");
	printf("| | | | | | | | | | | | | | | | |\n");
	printf("| | | | | | | | | | | | | | | | |\n");
	printf("| | | | | | | | | | | | | | | | |\n");
	printf("| | | | | | | | | | | | | | | | |\n");
	printf("| | | | | | | | | | | | | | | | |\n");
	printf("| | | | | | | | | | | | | | | | |\n");
	printf("| | | | | | | | | | | | | | | | |\n");
	printf("| | | | | | | | | | | | | | | | |\n");
	printf("| | | | | | | | | | | | | | | | |\n");
	printf("| | | | | | | | | | | | | | | | |\n");
	while (1) {
		if (keyControl() == SUBMIT) {
			system("cls");
			break;
		}
	}
}

