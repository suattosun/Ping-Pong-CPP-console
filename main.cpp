
#include <iostream> 
#include <windows.h>

const int col = 20;
const int row = 40;
int centerY = col / 2;
int centerX = row / 2;
char myArea[col][row];
int playerOnePoint = 0;
int playerTwoPoint = 0;
int topLimit = 2;
int bottomLimit = 3;
int ballSpeedSlow = 10;
class Area {
private:

public:
	void AreaInit() {
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < row; j++) {
				myArea[i][j] = ' ';
			}
		}
	}
};
class PinBall {
private:
	int pinballPlaceX = centerX;
	int pinballPlaceY = centerY;
public:
	void phisicsMove();
	void ScoreCount();
};
int moveDirX = 1;
int moveDirY = 1;
void PinBall::phisicsMove() {

	if (myArea[pinballPlaceY + moveDirY][pinballPlaceX] == '#') {
		moveDirY *= -1;
	}
	if (myArea[pinballPlaceY][pinballPlaceX + moveDirX] == '|') {
		moveDirX *= -1;
	}
	if (pinballPlaceY != 0 || pinballPlaceY != col || pinballPlaceX != 0 || pinballPlaceX != row) {
		myArea[pinballPlaceY][pinballPlaceX] = ' ';
		pinballPlaceY += moveDirY;
		pinballPlaceX += moveDirX;
		myArea[pinballPlaceY][pinballPlaceX] = '*';
	}
}

void PinBall::ScoreCount() {

	if (pinballPlaceX >= row ) {
		playerOnePoint++;
		myArea[pinballPlaceY][pinballPlaceX] = ' ';
		pinballPlaceX = centerX;
		pinballPlaceY = centerY;
		myArea[pinballPlaceY][pinballPlaceX] = '*';
	}
	else if (pinballPlaceX <= 0) {
		playerTwoPoint++;
		myArea[pinballPlaceY][pinballPlaceX] = ' ';
		pinballPlaceX = centerX;
		pinballPlaceY = centerY;
		myArea[pinballPlaceY][pinballPlaceX] = '*';
	}
}

class ColArea {
private:

public:
	void distance() {
		for (int i = 0; i < col; i += (col - 1)) {
			for (int j = 0; j < row; j++) {
				myArea[i][j] = '#';
			}

		}
	}
};

class Racket {
private:
	int firstRacketY = col / 2;
	int firstRacketX = 1;
	int SecondRacketY = col / 2;
	int SecondRacketX = row - 1;

public:
	void myRacketMove() {

		myArea[firstRacketY][firstRacketX] = '|';
		myArea[firstRacketY + 1][firstRacketX] = '|';
		myArea[firstRacketY - 1][firstRacketX] = '|';

		myArea[firstRacketY + 2][firstRacketX] = ' ';
		myArea[firstRacketY - 2][firstRacketX] = ' ';

		myArea[SecondRacketY][SecondRacketX] = '|';
		myArea[SecondRacketY + 1][SecondRacketX] = '|';
		myArea[SecondRacketY - 1][SecondRacketX] = '|';

		myArea[SecondRacketY + 2][SecondRacketX] = ' ';
		myArea[SecondRacketY - 2][SecondRacketX] = ' ';





	}
	void keyboardInput() {

		if (GetKeyState('W') & 0x8000) {
			if (firstRacketY > topLimit)
				firstRacketY--;
		}
		else if (GetKeyState('S') & 0x8000) {
			if (firstRacketY < (col - bottomLimit))
				firstRacketY++;
		}
		if (GetKeyState('O') & 0x8000) {
			if (SecondRacketY > topLimit)
				SecondRacketY--;
		}
		else if (GetKeyState('L') & 0x8000) {
			if (SecondRacketY < (col - bottomLimit))
				SecondRacketY++;
		}
	}
};

void clear_screen() { //Actually, this func does not clear,
	COORD coord = { 0 }; //it just set the cursor at the
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // top left corner of the screen
	SetConsoleCursorPosition(h, coord);
}

void hide_cursor() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // top left corner of the screen
	CONSOLE_CURSOR_INFO ConCurInf;
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;
	SetConsoleCursorInfo(h, &ConCurInf);
}

int main(){
	ColArea myCA;
	Area myClassArea;
	PinBall myPinball;
	Racket myRacket;
	myClassArea.AreaInit();
	myCA.distance();
	myPinball.phisicsMove();
	hide_cursor();
	while (true){
		std::cout << playerOnePoint << "   " << playerTwoPoint << std::endl;
		myPinball.phisicsMove();
		myPinball.ScoreCount();
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < row; j++) {
				std::cout << myArea[i][j];
			}
			std::cout << std::endl;
		}
		myRacket.keyboardInput();
		myRacket.myRacketMove();
		Sleep(ballSpeedSlow);
		clear_screen();

	}
}
