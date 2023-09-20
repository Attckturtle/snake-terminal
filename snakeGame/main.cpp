#include<iostream>
#include<vector>
#include<conio.h>
#include<Windows.h>
#include<ctime>
#include<cstdlib>

constexpr int boxHeight = 20, boxWidth = 20;

struct Pos {
	int x, y;
};

std::vector<Pos> snake = {};
Pos fruit;

char lastKey = 0;

void clearScreen()
{
	COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void update() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
		case 'W':
			if (lastKey != 's') lastKey = 'w';
			break;

		case 's':
		case 'S':
			if (lastKey != 'w') lastKey = 's';
			break;

		case 'a':
		case 'A':
			if (lastKey != 'd') lastKey = 'a';
			break;

		case 'd':
		case 'D':
			if (lastKey != 'a') lastKey = 'd';
			break;
		}
	}

	Pos head = snake[0];
	Pos lastCell = snake.back();

	switch (lastKey) {
	case 'w':
		snake[0].y -= 1;
		break;
	case 's':
		snake[0].y += 1;
		break;
	case 'a':
		snake[0].x -= 1;
		break;
	case 'd':
		snake[0].x += 1;
		break;
	}

	if (snake.size() > 1) {
		for (int i = snake.size() - 1; i >= 2; i--) {
			snake[i] = snake[i - 1];
		}
		snake[1] = head;
	}

	if (snake[0].x == fruit.x && snake[0].y == fruit.y) {
		int fruitX = rand() % boxWidth;
		int fruitY = rand() % boxHeight;

		fruit = { fruitX, fruitY };

		snake.push_back(lastCell);
	}
}

void draw() {

	clearScreen();
	for (int j = 0; j < boxWidth + 2; j++) std::cout << "||";

	for (int i = 0; i < boxHeight; i++) {
		std::cout << "\n||";
		for (int j = 0; j < boxWidth; j++) {
			bool isSnake = false;

			for (int k = 1; k < snake.size(); k++)
				if (snake[k].x == j && snake[k].y == i) {
					std::cout << "BB";
					isSnake = true;
				}

			if (!isSnake) {
				if (snake[0].x == j && snake[0].y == i) std::cout << "HH";
				else if (fruit.x == j && fruit.y == i) std::cout << "FF";
				else std::cout << "  ";
			}
		}
		std::cout << "||";
	}

	std::cout << "\n";
	for (int j = 0; j < boxWidth + 2; j++) std::cout << "||";
}

int main() {
	bool gameend = false;
	srand(time(0));
	int fruitX = rand() % boxWidth;
	int fruitY = rand() % boxHeight;
    fruit = { fruitX, fruitY };
	int startSnakeX = rand() % boxWidth;
	int startSnakeY = rand() % boxHeight;
	snake.push_back({ startSnakeY, startSnakeX });
	while (1) {
		draw();
		update();

		for (int i = 1; i < snake.size(); i++) {
			if ((snake[0].x > boxWidth || snake[0].x < 0 || snake[0].y > boxHeight || snake[0].y < 0) ||
				(snake[0].x == snake[i].x && snake[0].y == snake[i].y)) {
			clearScreen();
			std::cout << "You lose\n";
			std::cout << "Your score was: " << snake.size() - 1;
			gameend = true;
			break;
		}
	}
		if (gameend) {
			break;
		}
		Sleep(100);
	}
	return 0;
}