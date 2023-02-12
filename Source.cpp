/**
*
* Solution to course project # 7
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Mira Velikova
* @idnumber 5MI0600269
* @compiler VC
*
* <program code>
*
*/

#include <iostream>
#include <iomanip> //for setw
#include <stdlib.h> //for system("cls")
#include <time.h> //for rand()

void showField(char** field, int size, int bombs);

void fillBombs(char** field, int size, int bombs);

void command(char** realField, char** revealed, int size, int bombs);

void addOne(int i, int j, char** field, int size);

void fillField(char** field, int size, char symbol);

void Engine();

int whichAction();

void open(int i, int j, char** realField, char** revealed, int size, bool& lose, bool& win, int& revealedOrMarkedCorrectly);

void mark(int i, int j, char** realField, char** revealed, int size, bool& win, int& revealedOrMarkedCorrectly, int bombs);

void unmark(int i, int j, char** realField, char** revealed, int size, int& revealedOrMarkedCorrectly, int bombs);

bool inBounds(int i, int j, int size);

int validSize();

int validBombs(int size);

int main() {

	Engine();

}

void Engine() {
	int size = validSize();
	int bombs = validBombs(size);
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
	showField(revealed, size, bombs);
	command(realField, revealed, size, bombs);
	for (int i = 0; i < size; i++) {
		delete [] realField[i];
		delete [] revealed[i];
	}
	delete [] realField;
	delete [] revealed;
}

int validSize() {
	const int MIN_SIZE = 3, MAX_SIZE = 10;
	int size = 0;
	std::cout << "Enter size of field: ";
	std::cin >> size;
	if (size<MIN_SIZE || size>MAX_SIZE) {
		std::cout << "Size must be between 3 and 10. ";
		return validSize();
	}
	return size;
}

int validBombs(int size) {
	const int MIN_BOMBS = 1, MAX_BOMBS = size*3;
	int bombs = 0;
	std::cout << "Enter number of bombs: ";
	std::cin >> bombs;
	if (bombs<MIN_BOMBS || bombs>MAX_BOMBS) {
		std::cout << "Bombs can be from 1 to "<<size*3<<". ";
		return validBombs(size);
	}
	return bombs;
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
		retry:
		int action = whichAction(); //open-1, mark-2, unmark-3
		int i, j;
		std::cin >> j >> i;
		if (inBounds(i, j, size)) {
			switch (action) {
			case 1:
				if (revealed[i][j] == 'X') {
					std::cout << "Cannot open marked spaces. Enter another command: ";
					break;
				}
				open(i, j, realField, revealed, size, lose, win, revealedOrMarkedCorrectly);
				showField(revealed, size, bombs);
				break;
			case 2:
				mark(i, j, realField, revealed, size, win, revealedOrMarkedCorrectly, bombs);
				break;
			case 3:
				unmark(i, j, realField, revealed, size, revealedOrMarkedCorrectly, bombs);
				break;
			}
		}
		else {
			std::cout << "Out of bounds. Try again: ";
			goto retry;
		}
	}
	if (win) {
		std::cout << std::endl << "Congratulations! You won!"<<std::endl;
		return;
	}
	if (lose) {
		std::cout << std::endl << "Uh-oh! You stepped on a mine!" << std::endl;
		return;
	}
}

bool inBounds(int i, int j, int size) {
	if (i >= 0 && i < size && j >= 0 && j < size) {
		return true;
	}
	else {
		return false;
	}
}

void open(int i, int j, char** realField, char** revealed, int size, bool& lose, bool& win, int& revealedOrMarkedCorrectly) {
	if (!inBounds(i, j, size)) {
		return;
	}
	if (revealed[i][j] == '?') {
		revealed[i][j] = realField[i][j];
		if (realField[i][j] == 'X') {
			lose = true;
			return;
		}
		revealedOrMarkedCorrectly++;
		if (revealedOrMarkedCorrectly == size * size) {
			win = true;
			return;
		}
		if (revealed[i][j] == ' ') {
			open(i - 1, j - 1, realField, revealed, size, lose, win, revealedOrMarkedCorrectly);
			open(i - 1, j, realField, revealed, size, lose, win, revealedOrMarkedCorrectly);
			open(i - 1, j + 1, realField, revealed, size, lose, win, revealedOrMarkedCorrectly);
			open(i, j - 1, realField, revealed, size, lose, win, revealedOrMarkedCorrectly);
			open(i, j + 1, realField, revealed, size, lose, win, revealedOrMarkedCorrectly);
			open(i + 1, j - 1, realField, revealed, size, lose, win, revealedOrMarkedCorrectly);
			open(i + 1, j, realField, revealed, size, lose, win, revealedOrMarkedCorrectly);
			open(i + 1, j + 1, realField, revealed, size, lose, win, revealedOrMarkedCorrectly);
		}
	}
}

void mark(int i, int j, char** realField, char** revealed, int size, bool& win, int& revealedOrMarkedCorrectly, int bombs) {
	if (revealed[i][j] == 'X') {
		std::cout << "Already marked! Enter another command: ";
		return;
	}
	if (revealed[i][j] != '?') {
		std::cout << "You cannot mark there! Enter another command: ";
		return;
	}
	revealed[i][j] = 'X';
	if (realField[i][j] == 'X') {
		revealedOrMarkedCorrectly++;
		if (revealedOrMarkedCorrectly == size * size) {
			win = true;
		}
	}
	showField(revealed, size, bombs);
}

void unmark(int i, int j, char** realField, char** revealed, int size, int& revealedOrMarkedCorrectly, int bombs) {
	if (revealed[i][j] != 'X') {
		std::cout << "That place isn't marked! Enter another command: ";
		return;
	}
	revealed[i][j] = '?';
	if (realField[i][j] == 'X') {
		revealedOrMarkedCorrectly--;
	}
	showField(revealed, size, bombs);
}

void fillField(char** field, int size, char symbol) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			field[i][j] = symbol;
		}
	}
}

void showField(char** field, int size, int bombs) {
	system("cls");
	std::cout << "Number of bombs: " << bombs << std::endl << std::endl;
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
		if (field[i][j] != 'X') {
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
	if (inBounds(i, j, size)) {
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