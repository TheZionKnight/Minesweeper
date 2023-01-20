#include <iostream>
#include <iomanip> //for setw
#include <stdlib.h> //for system("cls")
#include <cstdlib> //for rand()
#include <time.h> //for rand()

void showField(char** field, int size);

void fillBombs(char** field, int size, int bombs);

void addNumbers(char** field, int size, int bomb);

void command(char** realField, char** revealed, int size, int bombs);

void addOne(int i, int j, char** field, int size);

void fillField(char** field, int size, char symbol);

void Engine();

int whichAction();

void open(int i, int j, char** realField, char** revealed, int size, bool& lose, bool& win, int& revealedOrMarkedCorrectly);

void mark(int i, int j, char** realField, char** revealed, int size, bool& win, int& revealedOrMarkedCorrectly);

void unmark(int i, int j, char** realField, char** revealed, int size, int& revealedOrMarkedCorrectly);

int main() {

	Engine();

}

void Engine() {
	int size = 0, bombs = 0;
	std::cout << "Enter size of field: ";
	std::cin >> size;
	std::cout << std::endl << "Enter number of bombs: ";
	std::cin >> bombs;
	std::cout << std::endl;
	char** realField = new char* [size];
	for (int i = 0; i < size; i++) {
		realField[i] = new char[size];
	}
	char** revealed = new char* [size];
	for (int i = 0; i < size; i++) {
		revealed[i] = new char[size];
	}
	fillField(realField, size, ' ');
	fillField(revealed, size, '?');
	fillBombs(realField, size, bombs);
	showField(revealed, size);
	command(realField, revealed, size, bombs);
}

int whichAction() {
	char input[10];
	std::cin >> input;
	if (input[0] == 'o' && input[1] == 'p' && input[2] == 'e' && input[3] == 'n' && input[4]=='\0') {
		return 1;
	}
	if (input[0] == 'm' && input[1] == 'a' && input[2] == 'r' && input[3] == 'k' && input[4] == '\0') {
		return 2;
	}
	if (input[0] == 'u' && input[1] == 'n' && input[2] == 'm' && input[3] == 'a' && input[4] == 'r' && input[5] == 'k' && input[6] == '\0') {
		return 3;
	}
	else {
		std::cout << "Wrong input. Try again: "<<std::endl;
		return whichAction();
	}
}

void command(char** realField, char** revealed, int size, int bombs) {
	bool win = false, lose = false;
	int revealedOrMarkedCorrectly = 0;
	while (!win && !lose) {
		int action = whichAction(); //open-1, mark-2, unmark-3
		int i, j;
		std::cin >> j >> i;
		switch (action) {
		case 1:
			open(i, j, realField, revealed, size, lose, win, revealedOrMarkedCorrectly);
			break;
		case 2:
			mark(i, j, realField, revealed, size, win, revealedOrMarkedCorrectly);
			break;
		case 3:
			unmark(i, j, realField, revealed, size, revealedOrMarkedCorrectly);
			break;
		}
	}
	if (win) {
		std::cout << std::endl << "Congratulations! You won!";
		return;
	}
	if (lose) {
		std::cout << std::endl << "Uh-oh! You stepped on a mine!";
		return;
	}
}

void open(int i, int j, char** realField, char** revealed, int size, bool& lose, bool& win, int& revealedOrMarkedCorrectly) {

}

void mark(int i, int j, char** realField, char** revealed, int size, bool& win, int& revealedOrMarkedCorrectly) {
	revealed[i][j] = 'X';
	if (realField[i][j] == 'X') {
		revealedOrMarkedCorrectly++;
		if (revealedOrMarkedCorrectly == size * size) {
			win = true;
		}
	}
	showField(revealed, size);
}

void unmark(int i, int j, char** realField, char** revealed, int size, int& revealedOrMarkedCorrectly) {
	
}

void fillField(char** field, int size, char symbol) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			field[i][j] = symbol;
		}
	}
}

void showField(char** field, int size) {
	system("cls");
	std::cout << "    ";
	for (int i = 0; i < size; i++) {
		std::cout << std::setw(3) << i;
	}
	std::cout << std::endl << "  ";
	for (int i = 0; i < size * 4; i++) {
		std::cout << "_";
	}
	std::cout << std::endl;
	for (int i = 0; i < size; i++) {
		std::cout << std::setw(3) << i << "|";
		for (int j = 0; j < size; j++) {
			std::cout << std::setw(3) << field[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << "Enter open/mark/unmark and the coordinates(horizontally, vertically)" << std::endl;
}

void fillBombs(char** field, int size, int bombs) {
	srand(time(0));
	int counter = 0;
	while (counter < bombs) {
		int i = rand() % size;
		int j = rand() % size;
		if (field[i][j] == ' ') {
			field[i][j] = 'X';
			addOne(i-1, j-1, field, size);
			addOne(i-1, j, field, size);
			addOne(i-1, j+1, field, size);
			addOne(i, j-1, field, size);
			addOne(i, j+1, field, size);
			addOne(i+1, j-1, field, size);
			addOne(i+1, j, field, size);
			addOne(i+1, j+1, field, size);
			counter++;
		}
	}
}

void addOne(int i, int j, char** field, int size) {
	if (i >= 0 && i < size && j >= 0 && j < size) {
		if (field[i][j] != 'X') {
			if (field[i][j] == ' ') {
				field[i][j] = '1';
			}
			else {
				field[i][j]++;
			}
		}
	}
}