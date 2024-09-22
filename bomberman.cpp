#include"bomberman.h"
#include<iostream>
#include<random>

auto randomNumber(int fromVal = -10, int toVal = 100) -> int
{

	std::random_device rd;
	std::mt19937 mersene(rd());
	return (fromVal + mersene() % toVal);
}

//генерация псевдослучайных чисел
auto getRandomNumber(int min, int max) -> int
{

#ifndef RANDINIT
#define RANDINIT
	// запуск алгоритма генерации случайных чисел
	srand(time(NULL));
	rand();
#endif

	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

	return static_cast<int>(min + rand() * fraction * (max - min + 1));
}

// генерация локации
template <typename T>
void fillPlayDesk(T *playDesk,
				  const int &row,
				  const int &column,
				  const int &countOfObjects)
{
	for(int y{ 0 }; y < row; ++y) {
		for(int x{ 0 }; x < column; ++x) {
			// по дефолту пишется случайное число
			playDesk[y][x] = randomNumber(0, countOfObjects); // 0 1 2 3

			// стены по краям
			if(x == 0 || y == 0 || x == column - 1 || y == row - 1)
				playDesk[y][x] = WALL;

			// вход и выход
			if(x == 0 && y == 2 || x == column - 1 && y == row - 3)
				playDesk[y][x] = HALL;

			if(playDesk[y][x] == ENEMY) {

				// определяется вероятность того, останется враг или нет
				// допустим, вероятность остаться на уровне - 10%
				int prob = randomNumber(0, 20); // 0-9
				if(prob != 0) // 1 2 3 4 5 6 7 8 9
					playDesk[y][x] = HALL;
			}
		}

	}
}

// показ локации
void showDesk(auto playDesk, const int &row, const int &column, const HANDLE &consoleHandle)
{

	for(int y = 0; y < row; ++y) // перебор строк
	{
		for(int x = 0; x < column; ++x) {
			// cout << location[y][x];
			switch(playDesk[y][x]) {
				case HALL: // коридор
					std::cout << " ";
					break;
				case WALL: // стена
					SetConsoleTextAttribute(consoleHandle, DARKGREEN); // 0-255
					std::cout << (char)177; //(char)219;
					break;
				case COIN: // монетки
					SetConsoleTextAttribute(consoleHandle, YELLOW);
					std::cout << (char)15; // 249
					break;
				case ENEMY: // враги
					SetConsoleTextAttribute(consoleHandle, RED);
					std::cout << (char)1;
					break;
				default:
					std::cout << playDesk[y][x];
					break;
			}
		}
		std::cout << "\n";
	}
}

void playGame()
{

}