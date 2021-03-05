//Ascii symbols -> http://www.asciitable.com/ 

#include <stdio.h>
#include <windows.h> // COORD, HANDLE, STD etc
#include <stdlib.h> //system functions
#include <time.h> //time(0) in fruitspawn
#include <conio.h> //movement, getch, kbhit etc

#define ROWS 20
#define COLUMNS 40 

int gameField[ROWS][COLUMNS];
int snakeHead, snakeTail, Fruit;
int Game = 0;
int x, y, direction;
int score;

int getCharacter(); //retrieving chars if button is hit
void screenReset(); //Resets the cursor position after each iteration
void snakeInit();
void gameBoarder();
void fruitSpawn();
void movement();
void tailMovement();
void GameOver();

int main() {
	snakeInit();

	while (Game == 0) {
	gameBoarder();
	screenReset();
	fruitSpawn();
	movement();
	tailMovement();
	Sleep(100);
	}	
}

void GameOver() {
	Sleep(1500);
	system("CLS"); //clears the screen

	printf("\n\n\n\n\n\n\t\t\t\t\t\t\tGAME OVER\n\n");
	printf("\n\n\n\n\n\n\t\t\t\t\t\t\tScore: %d\n\n", score);
	Game = 1;
}
void tailMovement() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (gameField[i][j] == snakeTail) {
				gameField[i][j] = 0;
			}
		}
	}
	snakeTail++;
}

int getCharacter() {
	if (_kbhit()) {
		return _getch();
	}
}

void movement() {
	int button = getCharacter();
	button = tolower(button); //anti CAPS
	
	//continous movement
	//snake cant change x direction
	if ((button == 'd' || button == 'a') && abs(direction-button)>5) { 
		direction = button;
	}
	//snake cant change y direction
	if ((button == 's' || button == 'w') && abs(direction - button)>5) {
		direction = button;
	}
	
	if (direction == 'd') {
		y++;
		if (gameField[x][y] != 0 && gameField[x][y] != -1) {
			GameOver();
		}
		if (gameField[x][y] == -1) { // when snake eats the fruit a new one spawns
			Fruit = 0;
			snakeTail -= 1; //tail following
			score += 1;
		}
		snakeHead++;
		gameField[x][y] = snakeHead;	
		if (y == COLUMNS - 1) {  //snake reenters if reaching boarder
			y = 0;
		}
	}
	if (direction == 'a') {
		y--;
		if (gameField[x][y] != 0 && gameField[x][y] != -1) {
			GameOver();
		}
		if (gameField[x][y] == -1) {
			Fruit = 0;
			snakeTail -= 1;
			score += 1;
		}
		snakeHead++;
		gameField[x][y] = snakeHead;
		if (y == 0) {
			y = COLUMNS - 1;
		}
	}
	if (direction == 's') {
		x++;
		if (gameField[x][y] != 0 && gameField[x][y] != -1) {
			GameOver();
		}
		if (gameField[x][y] == -1) {
			Fruit = 0;
			snakeTail -= 1;
			score += 1;
		}
		snakeHead++;
		gameField[x][y] = snakeHead;
		if (x == ROWS - 1) {
			x = 0;
		}
	}
	if (direction == 'w') {
		x--;
		if (gameField[x][y] != 0 && gameField[x][y] != -1) {
			GameOver();
		}
		if (gameField[x][y] == -1) {
			Fruit = 0;
			snakeTail -= 1;
			score += 1;
		}
		snakeHead++;
		gameField[x][y] = snakeHead;
		if (x == 0) {
			x = ROWS - 1;
		}
	}
}

void fruitSpawn() {
	//Random fruitspawn, arithmetics to avoid gameboarder spawns
	int FruitX, FruitY;
	srand(time(0)); //makes the spawns random, due to time -> bad solution
	FruitX = 1 + rand() % ROWS - 3;
	FruitY = 1 + rand() % COLUMNS - 3;

	//checking if a fruit is spawned + making sure that the fruit isnt spawned on the snake
	if (Fruit == 0 && gameField[FruitX][FruitY] == 0) {
		gameField[FruitX][FruitY] = -1; //fruit value
		Fruit = 1;
	}
}

void screenReset() {

	HANDLE solver; // a HANDLE variabel(problem solver)
	COORD Position; // gives coordinate of console screen
	solver = GetStdHandle(STD_OUTPUT_HANDLE); //solver handles the standard output
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(solver, Position);

}

void snakeInit() {

	//Empty field
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j <COLUMNS; j++) {
			gameField[i][j]=0;
		}
	}
	
	x = ROWS / 2;
	y = COLUMNS / 2;
	snakeHead = 4;
	snakeTail = 1;
	Fruit = 0;
	direction = 'd'; //snake moves at start

	//Start position of snake
	for (int i = 0; i < snakeHead; i++) {
		gameField[x][snakeHead] = i + 1; 
	}	
}

void gameBoarder() {

	/*ASCIITABLE 
	201 = upper leftcorner 
	187 = upper leftcorner
	205 = horizontal line
	186 = vertical line
	200 = lower leftcorner 
	188 = lower rightcorner 
	219 = snakeHead
	174 = snakeTail
	64 = fruit */

	//upper row
	for (int i = 0; i <= COLUMNS + 1; i++) {
		if (i == 0) {
			printf("%c", 201);
		}
		else if (i == COLUMNS + 1) {
			printf("%c", 187);
		}
		else {
			printf("%c", 205);
		}
	}
	printf("Fruits Eaten: %d\t", score);
	printf("\n");

	//middle + start pos of snake/fruit
	for (int i = 0; i < ROWS; i++) {
		printf("%c", 186);
		for (int j = 0; j < COLUMNS; j++) {
			if (gameField[i][j] == 0) {
				printf(" ");
			}
			if (gameField[i][j] > 0 && gameField[i][j] != snakeHead) {
				printf("%c", 174);
			}
			if (gameField[i][j] == snakeHead) {
				printf("%c", 219);
			}
			if (j == COLUMNS - 1) {
				printf("%c\n", 186);
			}
			if (gameField[i][j] == -1) {
				printf("%c", 64);
			}
			
		}
	}
	//lower row
	for (int i = 0; i <= COLUMNS + 1; i++) {
		if (i == 0) {
			printf("%c", 200);
		}
		else if (i == COLUMNS + 1) {
			printf("%c", 188);
		}
		else {
			printf("%c", 205);
		}
	}
}
