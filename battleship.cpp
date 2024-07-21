#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

const int row = 10;
const int col = 10;
char playerBoard[row][col];
char computerBoard[row][col];

void AvailableChoices() {
	cout << R"(-----------------------
Available choices:
1- Start the game
2- See Rules
3- Exit)" << endl;
}

void Rules() {
	cout << R"(
Rule No. 1- You can't enter the coordinates which the board doesn't include. You can enter numbers between 1-10 and letters between A-J; otherwise, you will be warned, and you won't be able to place a ship.
Rule No. 2- Ships can be placed Manually or Randomly.
Rule No. 3- You can't place ships next to each other. Randomly, they will be placed automatically according to this rule.
--------------------
Available choices:
1- Start the game
2- See Rules
3- Exit
)" << endl;
}

void InitializeBoards() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			playerBoard[i][j] = '*';
			computerBoard[i][j] = '*';
		}
	}
}

void PrintBoard(char board[row][col], bool showShips = true) {
	cout << "   ";
	for (char c = 'A'; c < 'A' + col; c++) {
		cout << c << "  ";
	}
	cout << endl;

	for (int i = 0; i < row; i++) {
		if (i + 1 < 10) {
			cout << i + 1 << "  ";
		}
		else {
			cout << i + 1 << " ";
		}

		for (int j = 0; j < col; j++) {
			if (board[i][j] == 'S' && !showShips) {
				cout << "*  ";
			}
			else {
				if (board[i][j] == 'S') {

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
				}
				cout << board[i][j] << "  ";

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		}
		cout << endl;
	}
}

bool CheckPlacementMethod(char& choice) {
	cout << "How do you want to place your ships? (Random- r Manual- m): ";
	cin >> choice;

	if (choice == 'r' || choice == 'm')
		return true;
	else
		return false;
}

bool CheckEmptyHorizontal(char board[row][col], int r, int c, int health) {
	for (int i = 0; i < health; i++) {
		if (board[r][c + i] != '*') {
			return false;
		}
	}
	return true;
}

bool CheckEmptyVertical(char board[row][col], int r, int c, int health) {
	for (int i = 0; i < health; i++) {
		if (board[r + i][c] != '*') {
			return false;
		}
	}
	return true;
}
void PlaceShipRandom(char board[row][col], int health) {
	int r, c;
	int direction = rand() % 2;

	if (direction == 0) {
		do {
			r = rand() % row;
			c = rand() % (col - health + 1);
		} while (!CheckEmptyHorizontal(board, r, c, health));

		for (int i = 0; i < health; i++) {
			board[r][c + i] = 'S';
		}
	}
	else {
		do {
			r = rand() % (row - health + 1);
			c = rand() % col;
		} while (!CheckEmptyVertical(board, r, c, health));

		for (int i = 0; i < health; i++) {
			board[r + i][c] = 'S';
		}
	}
}

void PlaceShipManually(char board[row][col], int& health5, int& health4, int& health3, int& health2, int& health1) {
	int numCoordinate;
	char letterCoordinate;

	PrintBoard(board);
	cout << "Enter coordinates for a ship (e.g., 4 B): ";
	cin >> numCoordinate >> letterCoordinate;

	int r = numCoordinate - 1;
	int c = letterCoordinate - 'A';

	if (r >= 0 && r < row && c >= 0 && c < col && board[r][c] == '*') {
		char orientation;
		cout << "Enter ship orientation (H for horizontal, V for vertical): ";
		cin >> orientation;

		int health = 1;

		if (orientation == 'H' || orientation == 'h') {
			cout << "Enter ship length: ";
			cin >> health;

			if (health < 1 || health > 5) {
				cout << "Invalid ship length. Length should be between 1 and 5." << endl;
				return;
			}

			if (c + health > col) {
				cout << "Warning: Ship placement is out of range. Try again." << endl;
				return;
			}

			if (!CheckEmptyHorizontal(board, r, c, health)) {
				cout << "Ships cannot be placed next to each other horizontally. Try again." << endl;
				return;
			}
		}
		else if (orientation == 'V' || orientation == 'v') {
			cout << "Enter ship length: ";
			cin >> health;

			if (health < 1 || health > 5) {
				cout << "Invalid ship length. Length should be between 1 and 5." << endl;
				return;
			}

			if (r + health > row) {
				cout << "Warning: Ship placement is out of range. Try again." << endl;
				return;
			}

			if (!CheckEmptyVertical(board, r, c, health)) {
				cout << "Ships cannot be placed next to each other vertically. Try again." << endl;
				return;
			}
		}
		else {
			cout << "Invalid orientation. Use 'H' for horizontal or 'V' for vertical." << endl;
			return;
		}

		switch (health) {
		case 5:
			if (health5 >= 1) {
				cout << "Warning: You can place only one 5-health ship. Try again" << endl;
				return;
			}
			health5++;
			break;
		case 4:
			if (health4 >= 1) {
				cout << "Warning: You can place only one 4-health ship. Try again" << endl;
				return;
			}
			health4++;
			break;
		case 3:
			if (health3 >= 1) {
				cout << "Warning: You can place only one 3-health ship. Try again" << endl;
				return;
			}
			health3++;
			break;
		case 2:
			if (health2 >= 1) {
				cout << "Warning: You can place only one 2-health ship. Try again" << endl;
				return;
			}
			health2++;
			break;
		case 1:
			if (health1 >= 1) {
				cout << "Warning: You can place only one 1-health ship try again" << endl;
				return;
			}
			health1++;
			break;
		default:
			cout << "Invalid ship length" << endl;
			return;
		}

		if (orientation == 'H' || orientation == 'h') {
			for (int i = 0; i < health; ++i) {
				board[r][c + i] = 'S';
			}
		}
		else if (orientation == 'V' || orientation == 'v') {
			for (int i = 0; i < health; ++i) {
				board[r + i][c] = 'S';
			}
		}
	}
	else {
		cout << "Invalid coordinates please try again" << endl;
		return;
	}
}



bool PlayerTurn() {
	int numCoordinate;
	char letterCoordinate;

	cout << "Enter coordinates to attack (for example: 4B): ";
	cin >> numCoordinate >> letterCoordinate;

	int r = numCoordinate - 1;
	int c = letterCoordinate - 'A';

	if (r >= 0 && r < row && c >= 0 && c < col) {
		if (computerBoard[r][c] == 'S') {
			computerBoard[r][c] = 'H';
			return true;
		}
		else if (computerBoard[r][c] == '*') {
			computerBoard[r][c] = 'M';
		}
		else {
			cout << "You already attacked this position please choose a different one" << endl;
		}
	}
	else {
		cout << "Invalid coordinates please try again" << endl;
	}

	return false;
}

bool ComputerTurn() {
	int r, c;

	do {
		r = rand() % row;
		c = rand() % col;
	} while (playerBoard[r][c] == 'H' || playerBoard[r][c] == 'M');

	if (playerBoard[r][c] == 'S') {
		playerBoard[r][c] = 'H';
		return true;
	}
	else {
		playerBoard[r][c] = 'M';
	}

	return false;
}

bool CheckWin(char board[row][col]) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (board[i][j] == 'S') {
				return false;
			}
		}
	}
	return true;
}

int main() {
	srand(time(NULL));
	char choice;

	int health5 = 0, health4 = 0, health3 = 0, health2 = 0, health1 = 0;

	while (true) {
		system("cls");
		AvailableChoices();
		cout << "Enter your choice (1-3): ";
		cin >> choice;

		switch (choice) {
		case '1': {
			InitializeBoards();
			if (CheckPlacementMethod(choice)) {
				if (choice == 'r') {
					for (int i = 1; i <= 5; i++) {
						PlaceShipRandom(playerBoard, i);
						PlaceShipRandom(computerBoard, i);
					}
				}
				else if (choice == 'm') {
					int totalShips = 0;
					while (totalShips < 15) {
						PlaceShipManually(playerBoard, health5, health4, health3, health2, health1);
						totalShips++;

						if (totalShips % 5 == 0) {
							PrintBoard(playerBoard);
							cout << "You have placed " << totalShips << " ships. Maximum limit reached." << endl;
							break;
						}
					}
					for (int i = 1; i <= 5; i++) {
						PlaceShipRandom(computerBoard, i);
					}
				}
			}
			else {
				cout << "Invalid choice. Please enter 'r' for random placement or 'm' for manual placement." << endl;
				return 1;
			}
			bool playerTurn = true;

			while (true) {
				system("cls");
				cout << "Player's board:" << endl;
				PrintBoard(playerBoard, true);
				cout << endl;
				cout << "Computer's board:" << endl;
				PrintBoard(computerBoard, false);
				cout << endl;

				if (playerTurn) {
					if (PlayerTurn()) {
						cout << "You hit a ship!" << endl;
					}
					else {
						cout << "You missed!" << endl;
						playerTurn = false;
					}
				}
				else {
					if (ComputerTurn()) {
						cout << "Computer hit your ship!" << endl;
					}
					else {
						cout << "Computer missed!" << endl;
						playerTurn = true;
					}
				}

				if (CheckWin(playerBoard)) {
					cout << "The computer has won the game" << endl;
					break;
				}
				else if (CheckWin(computerBoard)) {
					cout << "Congratulations, You've defeated all of the enemy's ships and you've won the game" << endl;

					Sleep(3000);
					system("cls");
					cout << "Player's board:" << endl;
					PrintBoard(playerBoard, true);
					cout << endl;
					cout << "Computer's board:" << endl;
					PrintBoard(computerBoard, false);
					cout << endl;
					break;
				}

				_getch();
			}
			break;
		}
		case '2': {
			system("cls");
			Rules();
			cout << "Press any key to go back to the menu..." << endl;
			_getch();
			break;
		}
		case '3': {
			cout << "Bye";
			Sleep(1000);
			cout << ".";
			Sleep(1000);
			cout << ".";
			Sleep(1000);
			cout << ".";
			return 0;
		}
		default: {
			cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
			break;
		}
		}
	}
}