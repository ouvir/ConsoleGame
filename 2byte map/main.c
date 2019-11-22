// 본 프로그램 소스 코드는 C언어를 통해 콘솔게임 제작을 위한 사이트( https://codevkr.tistory.com/15?category=699626)의
//프로젝트를 참고하였습니다. 

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
		system("cls"); // 화면 모두 지우기
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
	system("mode con cols=56 lines=20 | title 게임제목"); 
	
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기 
	CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = 0; // false 또는 0 : 숨기기 
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(consoleHandle , &ConsoleCursor);
}

// 커서 위치 이동함수  
void gotoxy(int x, int y){
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기 
	COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
} 

// 첫번째: 텍스트, 두번째: 배경  
void setColor(int forground, int background){
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기 
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
	} else if(temp == ' '){ // 스페이스바(공백)이 선택 버튼  
		return SUBMIT;
	}
}

void titleDraw(){
	printf("\n\n\n"); // 맨위에 3칸 개행  
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
	gotoxy(x-2, y); // -2 한 이유는 > 를 출력해야하기 때문에  
	printf("> 게임시작");
	gotoxy(x, y+1);
	printf("게임정보");
	gotoxy(x, y+2);
	printf("  종료  ");
	while(1){ // 무한반복  
		int n = keyControl(); // 키보드 이벤트를 키값으로 받아오기  
		switch(n){
			case UP: { // 입력된 키의 값이 UP인경우 (w) 
				if(y > 12){ // y는 12~14까지만 이동  
					gotoxy(x-2, y); // x-2 하는 이유는 ">"를 두칸 이전에 출력하기위해  
					printf(" "); // 원래 위치를 지우고  
					gotoxy(x-2, --y); // 새로 이동한 위치로 이동하여  
					printf(">"); // 다시 그리기  
				}
				break;
			}
				
			case DOWN: { // 입력된 키의 값이 DOWN인경우 (s) 
				if(y < 14) { // 최대 14  
					gotoxy(x-2, y);
					printf(" ");
					gotoxy(x-2, ++y);
					printf(">");
				}
				break;
			}
			
			case SUBMIT: {
				return y-12; // 스페이스바(선택)되었을 경우 y-12
				// y 시작 위치가 12였으므로 y-12 를 하면 0, 1, 2 세 숫자를 받을 수 있다. 
			}
		}
	}
} 

void infoDraw(){
	system("cls"); // 화면 모두 지우기  
	printf("\n\n");
	printf("                        [ 조작법 ]\n\n");
	printf("                    이동: W, A, S, D\n");
	printf("                    선택: 스페이스바\n\n\n\n\n\n\n");
	printf("               개발자: codevkr.tistory.com\n\n");
	printf("      스페이스바를 누르면 메인화면으로 이동합니다.");
	
	while(1){
		if(keyControl() == SUBMIT){
			system("cls");
			break;
		}
	}
}

void drawMap(){
	system("cls"); // 화면 모두 지우기
	printf("\n\n"); // 맨위에 2칸 개행 
	printf("O:검은 돌, X:흰 돌\n");
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

