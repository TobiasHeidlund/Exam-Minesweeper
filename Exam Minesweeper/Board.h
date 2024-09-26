#pragma once
#include <fstream>
class Board
{
protected:
	Board(int h, int w);
	Board(int h, int w, std::ifstream* file);
	Board(const Board& board);
	int height, width;
	char* map;
	bool setCoord(int x, int y, char c);
	const char* exportMap();
	~Board();
public:
	Board& operator=(const Board& other);
	const char getCoord(int x, int y);
	const int getWidth();
	const int getHeight();
	bool isCoordEmpty(int x, int y);
	bool isWithinBounds(int x, int y);
};

