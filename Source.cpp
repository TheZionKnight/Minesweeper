#include <iostream>
#include <iomanip>
#include <stdlib.h>

void showField(char** field, int size);

void fillBombs(char** field, int size);

void fillNumbers(char** field, int size);

void nullField(char** field, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			field[i][j] = '?';
		}
	}
}

void startUp(int size, int bombs, bool** revealed, char** realField) {
	
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

	nullField(realField, size);
	nullField(revealed, size);
	showField(revealed, size);
}

int main() {

	Engine();

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
}

void fillBombs(char** field, int size) {

}

void fillNumbers(char** field, int size) {

}