// HangMan.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

//to create the board and display text to console
void printFunction(string message, bool topBorder = true, bool bottomBorder = true)
{
	if (topBorder)
	{
		cout << "+---------------------------------+" << endl;
		cout << "|";
	}
	else
	{
		cout << "|";
	}

	//to center the message
	bool front = true;
	for (int i = message.length(); i < 33; i++)
	{
		if (front)
		{
			message = " " + message;
		}
		else
		{
			message = message + " ";
		}
		front = !front;
	}
	cout << message.c_str(); //casting the message to character string

	if (bottomBorder)
	{
		cout << "|" << endl;
		cout << "+---------------------------------+" << endl;
	}
	else
	{
		cout << "|" << endl;
	}
}

//to print available letters
void printLetters(string input, char from, char to)
{
	string str;
	for (char i = from; i <= to; i++)
	{
		if (input.find(i) == string::npos)
		{
			str += i;
			str += " ";
		}
		else
			str += "  ";
	}
	printFunction(str, false, false);
}

//hangman logic and display
void printHangman(int guessCount = 0)
{
	if (guessCount >= 1)	printFunction("|", false, false);
	else	printFunction("", false, false);
	if (guessCount >= 2)	printFunction("|", false, false);
	else	printFunction("", false, false);
	if (guessCount >= 3)	printFunction("O", false, false);
	else	printFunction("", false, false);
	if (guessCount == 4)	printFunction("/  ", false, false);
	if (guessCount == 5)	printFunction("/| ", false, false);
	if (guessCount >= 6)	printFunction("/|\\", false, false);
	else	printFunction("", false, false);
	if (guessCount >= 7)	printFunction("|", false, false);
	else	printFunction("", false, false);
	if (guessCount == 8)	printFunction("/  ", false, false);
	if (guessCount >= 9)	printFunction("/ \\", false, false);
	else	printFunction("", false, false);
}

void availableLetters(string used)
{
	printFunction("Available letters");
	printLetters(used, 'A', 'M');
	printLetters(used, 'N', 'Z');
}

//fetch random word from file on system
string wordRandomizer(string local)
{
	int lineCount = 0;
	string word;
	vector<string> v;
	ifstream fileIn(local);
	if (fileIn.is_open())
	{
		while (std::getline(fileIn, word))
			v.push_back(word);

		int randomLine = rand() % v.size();
		word = v.at(randomLine);
		fileIn.close();
	}
	return word;
}

//calculate remaining guesses before losing condition
int guessesLeft(string actualWord, string guessedWord)
{
	int errors = 0;
	for (int i = 0; i < guessedWord.length(); i++)
	{
		if (actualWord.find(guessedWord[i]) == string::npos)
			errors++;
	}
	return errors;
}

//check winning condition
bool winCondition(string word, string guessed)
{
	bool won = true;
	string s;
	for (int i = 0; i < word.length(); i++)
	{
		if (guessed.find(word[i]) == string::npos)
		{
			won = false;
			s += "_ ";
		}
		else
		{
			s += word[i];
			s += " ";
		}
	}
	printFunction(s, false);
	return won;
}

int main()
{
	srand(time(0)); //feeder for randomizer function
	string guesses;
	string wordToGuess;
	string file;
	wordSel:
	cout << "Select word list for Hangman Game\n";
	cout << "1. 126 words in file \n2. 6 words in file (for testing)\n>";
	switch (_getch())
	{
		case '1': file = "words.txt";	break;
		case '2': file = "wordsBrief.txt";	break;
		default: cout << "\nWrong input, try again...\n";	
			system("pause");
			system("cls"); //replace cls with clear if you run Linux or MacOS
			goto wordSel;
			break;
	}
	wordToGuess = wordRandomizer(file);

	int attempts = 0;
	bool win = false;
	do
	{
		system("cls"); //replace cls with clear if you run Linux or MacOS
		printFunction("HANGMAN");
		printHangman(attempts);
		availableLetters(guesses);
		printFunction("Guess the word");

		win = winCondition(wordToGuess, guesses);
		if (win)
			break;
		
		char x;
		cout << "Guesses Left: ";
		attempts != 9 ? cout << 10 - attempts : cout << "Last one!";
		cout << endl;
		cout << "Type your guess below, letter by letter. Use uppercase letters.";
		cout << "\n>"; x = _getch();
		if (guesses.find(x) == string::npos)
			guesses += x;
		attempts = guessesLeft(wordToGuess, guesses);
	} while (attempts < 10);

	if (win)
		printFunction("YOU GUESSED IT!");
	else
		printFunction("WRONG WORD!");

	system("pause"); //remove on MacOS or Linux
	//add getchar(); instead of above line on MacOS or Linux
	return 0;
}

// Microsoft Visual Studio 2019
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
