// SnakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

//constants for board area
const int width = 20;
const int height = 20;

//control variables
bool gameOver;
int score, speed = 1;

//location variables
int x, y, foodX, foodY;
int tailX[100], tailY[100];
int nTail;

//direction control
enum eDirecton { STOP = 0, Left, Right, up, down };
eDirecton dir;

//pre-game
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	foodX = rand() % width;
	foodY = rand() % height;
	score = 0;
}

//board outline + snake + food
void Display()
{
	system("cls"); //Please replace cls with clear if using Linux
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == foodY && j == foodX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
	cout << "Speed: "; 
	if (speed == 5)	cout << "Max" << endl;
	else cout << speed << "x" << endl;
	cout << "Controls: \n\t1. WASD for movement\n\t2. X to quit\n\tStart game by pressing movement key.\n";
}

//input from keyboard
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = Left;
			break;
		case 'd':
			dir = Right;
			break;
		case 'w':
			dir = up;
			break;
		case 's':
			dir = down;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

//logic for score, food, movement and tail
void LogicController()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case Left:
		x--;
		break;
	case Right:
		x++;
		break;
	case up:
		y--;
		break;
	case down:
		y++;
		break;
	default:
		break;
	}
	if (x > width-1 || x < 0 || y > height-1 || y < 0)
		gameOver = true;
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == foodX && y == foodY)
	{
		score += 10;
		foodX = rand() % width;
		foodY = rand() % height;
		nTail++;
	}
}
int main()
{
	Setup();
	while (!gameOver)
	{
		Display();
		Input();
		LogicController();
		if (score > (50*speed)) speed++; //increases game speed every 50 points
		Sleep(50 / speed); //game speed controller
	}
	cout << "Game Over, Press any key to close.";
	_getch();
	return 0;
}

// Microsoft Visual Studio 2019
// Run program: Ctrl + F5 or Debug > Start Without 
// Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
