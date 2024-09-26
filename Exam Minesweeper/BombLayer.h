#pragma once
#include "Board.h"
#include "string"
class BombLayer : public Board
{
public:
	static const int minBombs = 3, maxBombs = 15;
	BombLayer(int h, int w, int m);
	BombLayer(int h, int w, std::ifstream* file);
	BombLayer& operator=(const BombLayer* other);
	BombLayer(const BombLayer& bl);
	bool isCoordMine(int x, int y);
	bool isCoordNumber(int x, int y);
	int getCoordNumber(int x, int y);
	const int numberOfMines();
	std::string toFile();
private:
	int mines;
	void placeBombs();
	void calculateNumbers();
	void markNextToBombs(int x, int y);
	
};

