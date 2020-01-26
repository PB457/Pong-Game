#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

// Variables initialization
bool bGameOver;
const int Width = 30;
const int Height = 20;
int SnakeX, SnakeY, FruitX, FruitY, Score;
int TailX[100], TailY[100];
int TailLength;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;


void Setup()
{
	bGameOver = false;
	dir = STOP;
	SnakeX = Width / 2;
	SnakeY = Height / 2;
	FruitX = rand() % Width;
	FruitY = rand() % Height;
	Score = 0;
}

void Draw()
{
	system("cls"); // Clears the screen
	cout << "Score: " << Score << endl;
	for (int i = 0; i < Width; i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			if (j == 0)
			{
				cout << "#";
			}
			else if (i == SnakeY && j == SnakeX)
			{
				cout << "O";
			}

			else if (i == FruitY && j == FruitX)
			{
				cout << "F";
			}
			else
			{
				bool bPrint = false;
				for (int k = 0; k < TailLength; k++)
				{
					if (TailX[k] == j && TailY[k] == i)
					{
						cout << "o";
						bPrint = true;
					}
				}
				if (!bPrint)
				{
					cout << " ";
				}
			}
			if (j == Width - 1)
			{
				cout << "#";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < Width; i++)
	{
		cout << "#";
	}
	cout << endl;
}

void Input()
{
	// Receives keys as input
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			dir = UP;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			bGameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevTailX = TailX[0];
	int prevTailY = TailY[0];
	int prev2X, prev2Y;
	TailX[0] = SnakeX;
	TailY[0] = SnakeY;
	for (int i = 1; i < TailLength; i++)
	{
		prev2X = TailX[i];
		prev2Y = TailY[i];
		TailX[i] = prevTailX;
		TailY[i] = prevTailY;
		prevTailX = prev2X;
		prevTailY = prev2Y;
	}

	// Increase or decrease the snake coordinates according to the input
	switch (dir)
	{
	case LEFT:
		SnakeX--;
		break;
	case RIGHT:
		SnakeX++;
		break;
	case UP:
		SnakeY--;
		break;
	case DOWN:
		SnakeY++;
		break;
	default:
		break;
	}

	if (SnakeX >= Width) SnakeX = 0; else if (SnakeX < 0) SnakeX = Width - 1;
	if (SnakeY >= Height) SnakeY = 0; else if (SnakeY < 0) SnakeY = Height - 1;

	// Verifies if the tail collides with the head.
	for (int i = 0; i < TailLength; i++)
	{
		if (TailX[i] == SnakeX && TailY[i] == SnakeY)
		{
			bGameOver = true;
		}
	}

	// Detects if the snake eats the fruit
	if (SnakeX == FruitX && SnakeY == FruitY)
	{
		Score += 10;
		FruitX = rand() % Width;
		FruitY = rand() % Height;
		TailLength++;
	}
}

int main()
{
	Setup();
	while (!bGameOver)
	{
		Draw();
		Input();
		Logic();
	}
}
