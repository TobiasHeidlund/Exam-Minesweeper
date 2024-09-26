#include "BombLayer.h"
#include <random>
#include <string>
#include <fstream>
#include "Util.h"

BombLayer::BombLayer(int h, int w, int m): Board(h,w),mines(m)
{
	placeBombs();
	calculateNumbers();
}
BombLayer::BombLayer(int h, int w, std::ifstream* f):
	Board(h, w, f)
{
	int m = Util::lineToint(f);
	if (!Util::validInt(m, minBombs, maxBombs)) {
		throw "mines";
	}
	mines = m;
}

BombLayer& BombLayer::operator=(const BombLayer* other)
{
	if (this != other) {
		width = other->width;
		height = other->height;
		mines = other->mines;
		Board::operator=(*other);
	}
	return *this;
}

BombLayer::BombLayer(const BombLayer& bl) : Board(bl), mines(bl.mines)
{
}



bool BombLayer::isCoordMine(int x, int y)
{
	return getCoord(x,y)== 'b';
}
bool BombLayer::isCoordNumber(int x, int y)
{
	char curr = getCoord(x, y);
	return (int(curr) >= 48 && int(curr) <= 57);
}
int BombLayer::getCoordNumber(int x, int y)
{
	if (!isCoordNumber(x, y)) return -1;
	return int(getCoord(x,y))-48;
}
const int BombLayer::numberOfMines()
{
	return mines;
}
void BombLayer::placeBombs()
{
	std::default_random_engine r{ static_cast<long unsigned int>(time(0)) };
	//std::random_device r;
	std::uniform_int_distribution<int> dist(0, height * width);

	int nbrOfMines = mines;
	while (nbrOfMines > 0) {
		int coord = dist(r);
		if (map[coord] != 'b') {
			map[coord] = 'b';
			nbrOfMines--;
		}
	}
}

void BombLayer::calculateNumbers()
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (isCoordMine(x,y)) {
				markNextToBombs(x, y);
			}
		}

	}


}

void BombLayer::markNextToBombs(int x, int y)
{
	for (int lx = -1; lx < 2; lx++)
	{
		for (int ly = -1; ly < 2; ly++)
		{
			char curr = getCoord(x + lx, y + ly);
			if (isWithinBounds(x + lx, y + ly)) {
				if (curr != 'u' && curr != 'b') {
					if (isCoordNumber(x + lx, y + ly)) {
						setCoord(x + lx, y + ly, char(int(curr) + 1));
					}
					else setCoord(x + lx, y + ly, '1');

				}
			}


			
		}
	}

}


std::string BombLayer::toFile() {
	std::string s = std::string(exportMap());
	s.append("\n");
	s.append(std::to_string(mines));
	s.append("\n");
	return s;
}