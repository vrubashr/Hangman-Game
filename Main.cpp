#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;

void print(string msg, bool borderTop= true, bool borderBottom= true)
{
	bool frontSpace = true;

	if (borderTop)
	{
		cout << "+---------------------------------------------+" << endl;
		cout << "|";
	}
	else
	{
		cout << "|";
	}

	for (int i = msg.length(); i < 45; i++)
	{
		if (frontSpace)
		{
			msg = " " + msg;
		}
		else
		{
			msg = msg + " ";
		}
		frontSpace = !frontSpace;
	}
	cout << msg;
	
	if (borderBottom)
	{
		cout << "|" << endl;
		cout << "+---------------------------------------------+" << endl;
	}
	else
	{
		cout << "|" << endl;
	}
}

void drawMan(int guess = 0)
{
	if (guess >= 1)
		print("|", false, false);
	else
		print("", false, false);

	if (guess >= 2)
		print("|", false, false);
	else
		print("", false, false);

	if (guess >= 3)
		print("O", false, false);
	else
		print("", false, false);

	if (guess == 4)
		print("/  ", false, false);

	if (guess == 5)
		print("/| ", false, false);

	if (guess >= 6)
		print("/|\\", false, false);
	else
		print("", false, false);

	if (guess >= 7)
		print("|", false, false);
	else
		print("", false, false);

	if (guess == 8)
		print("/  ", false, false);

	if (guess >= 9)
	{
		print("/ \\", false, false);
		print("+---------------+", false, false);
		print("|_______________|", false, false);
	}
	else
		print("", false, false);
}

void Alphabets(string guess, char from, char to)
{
	string s;
	for (char i = from; i <= to; i++)
	{
		if (guess.find(i) == string::npos)
		{
			s += i;
			s += " ";
		}
		else
		{
			s += "  ";
		}
	}
	print(s, false, false);
}

void printAlphabet(string usedLetter)
{
	print("AVAILABLE LETTERS", true, true);
	Alphabets(usedLetter, 'A', 'M');
	Alphabets(usedLetter, 'N', 'Z');
}

bool wordCheck(string word, string guessed)
{
	bool won = true;
	string x;
	print("GUESS THE WORD", true, true);
	for (int i = 0; i < word.length(); i++)
	{
		if (guessed.find(word[i]) == string::npos)
		{
			won = false;
			x += "_ ";
		}
		else
		{
			x += word[i];
			x += " ";
		}
	}
	print(x, false, true);
	return won;
}

string loadWords(string path)
{
	int line = 0;
	string word;
	vector<string> wordfile;
	ifstream reader(path);
	if (reader.is_open())
	{
		while (std::getline(reader, word))
		{
			wordfile.push_back(word);
		}

		int randomWord = rand() % wordfile.size();
		word = wordfile.at(randomWord);
		reader.close();
	}
	return word;
}

int ChancesLeft(string word, string guessed)
{
	int error = 0;
	for (int i = 0; i < guessed.length(); i++)
	{
		if (word.find(guessed[i]) == string::npos)
		{
			error++;
		}
	}
	return error;
}

int main()
{
beginning:
	srand(time(0));
	string guess;
	string words=loadWords("words.txt");
	int guesses = 0;
	bool win = false;
	int options;

	srand(time(0));
	print("HANGMAN OPTIONS");
	print("1. PLAY", false, false);
	print("2. EXIT", false, true);
	cin >> options;
	switch (options)
	{
	case 1: goto play;
		break;
	case 2: return 0;
		break;
	}
	system("CLS");

	do
	{
	play:
		system("CLS");
		print("HANGMAN");
		drawMan(guesses);
		printAlphabet(guess);
		win=wordCheck(words, guess);

		if (win)
			break;
		


		char input;
		cout << "Enter the answer: ";
		cin >> input;
		if (guess.find(input) == string::npos)
		{
			guess += input;
		}

		guesses = ChancesLeft(words, guess);
	} while (guesses <=9);

	if (win)
		print("YOU WON!!");
	else if(guesses>=9)
		print("GAME OVER :(");

	system("pause");
	system("ClS");
	goto beginning;
	getchar();

	return 0;
}







/*
+---------------------------------------------+
|				HANGMAN						  |
+---------------------------------------------+
|					|			              |
|					|                         |
|					O                         |
|				   /|\                        |
|					|			              |
|			       / \                        |
|			+---------------+                 |
|		    |_______________|                 |
+---------------------------------------------+
|			Guess the Word                    |
+---------------------------------------------+
|			_ _ _ _ _ _ _ _					  |
+---------------------------------------------+
*/