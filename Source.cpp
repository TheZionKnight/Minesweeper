#include <iostream>
#include <iomanip> //for setw
#include <stdlib.h> //for system("cls")
#include <cstdlib> //for rand()
#include <time.h>

void showField(char** field, int size);

void fillBombs(char** field, int size, int bombs);

void addNumbers(char** field, int size, int bomb);

void command(char** realField, char** revealed, int size, int bombs);

void addOne(int i, int j, char** field, int size);

void fillField(char** field, int size, char symbol) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			field[i][j] = symbol;
		}
	}
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
	command(realField, revealed, size, bombs);
}

int main() {

	Engine();

}

void command(char** realField, char** revealed, int size, int bombs) {
	showField(realField, size);
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