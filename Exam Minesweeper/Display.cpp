#include "Display.h"
#include <iostream>
#include "Util.h"
using namespace std;
Display::Display(CombinedLayer* b, FileManager* f):board(b),fm(f)
{

}

int Display::getNumber(int min, int max)
{
	string str;
	cin >> str;
	int value = std::strtol(str.c_str(), NULL, 10);
	while (!Util::validInt(value, min, max)){
		cout << "Not a valid number please try again\n";
		cin.clear();
		cin >> str;
		value = std::strtol(str.c_str(), NULL, 10);
	}

	return value;
}

void Display::print()
{
	
	cout.width(board->getWidth() * 2 + 3);
	cout.fill('-');
	cout << '-' << endl;
	
	for (int y = -1; y < board->getHeight(); y++)
	{
		cout << '|';
		for (int x = -1; x < board->getWidth(); x++)
		{
			if (y == -1 && x == -1) {
				cout << ' ' << '|';
			}
			else if (y == -1) {
				cout << char(x + 65) << '|';
			}
			else if (x == -1) {
				cout << char(y + 49) << '|';
			}
			else {
				cout << board->getValueOfCoord(x, y) << '|';
			}
		}
		cout << endl;
		cout.width(board->getWidth() * 2 + 3);
		cout.fill('-');
		cout << '-' << endl;
		
	}
}
bool Display::executeCoord(string s, bool mark)
{
	int y{}, x{};
	//is a small letter
	if (s.at(0) >= 97 && s.at(0) <= 122) {
		x = s.at(0) - 97;
		y = std::strtol(s.substr(1).c_str(), NULL, 10);
		if (y == 0L) {
			return false;
		}
		//SHOULD BE A VALID COORD
		if (mark) {
			board->mark(x, y - 1);
		}
		else {
			char k = board->unvail(x, y - 1);
			if (k == 'b') {
				board->setDead();
			}
			else if (k == 'w') {
				board->stopPlaying();
			}
		}
		
		return true;

	}
	return false;
}
void Display::Dead()
{
	//cout.width(board->getWidth() * 2 + 3);
	cout.width(board->getWidth() * 2 + 3);
	cout.fill('-');
	cout <<' ' << endl;
	cout << "You have lost";
	cout.width(board->getWidth() * 2 + 3);
	cout.fill('-');
	cout << endl;

}
void Display::Won()
{
	//cout.width(board->getWidth() * 2 + 3);
	cout.width(board->getWidth() * 2 + 3);
	cout.fill('-');
	cout <<' '<< endl;
	cout << "You have won";
	cout.width(board->getWidth() * 2 + 3);
	cout.fill('-');
	cout << endl;

}
bool Display::issueCommand(string s)
{
	if (s.size() < 2) {
		return false;
	}
	switch (s.at(0)) {
	case '+': {
		return executeCoord(s.substr(1),true);
	}
	case '!': {
		if (s.substr(1) == "save") {
			 fm->save();
		}
		else if (s.substr(1) == "load") {
			fm->load();
		}else if (s.substr(1) == "q") {
			board->setDead();
		}
		return true;
		}
	}
	return executeCoord(s,false);
}

void Display::getUserInput()
{
	string input;
	bool notValidInput = true;
	do {
	cout << "What move do you want to make?\nYour options are:"
		<< "\n*Coords to guess ex: a5\n*+Coords to place marker ex: +a5"
		<< "\n*!save & !load\n*!q to Quit\n:";
		cin >> input;
		notValidInput = !issueCommand(input);
	} while (notValidInput);

}




