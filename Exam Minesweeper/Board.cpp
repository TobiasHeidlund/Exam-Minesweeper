#include "Board.h"
#include "fstream"
using namespace std;

bool Board::setCoord(int x, int y, char c)
{
	// INDEX OUT OF BOUNDS
	if ((x<0 || x> width) || (y<0 || y>height)) return false;
	map[y * width + x] = c;
	return true;
}

Board::Board(int h, int w) : height(h), width(w)
{
	map = new char[h * w +1];
	for (int i = 0; i < h * w; i++)
	{
		map[i] = char(' ');
	}
	map[h * w] = '\0';
}

Board::Board(int h, int w, std::ifstream* f): height(h), width(w), map(new char[h * w + 1])
{
	char* mptr = map;
	while (f->good()) {
		if ((char)f->peek() == '\n') {
			*mptr = (char)f->get();
			map[h * w] = '\0';
			if (*(mptr + 1) == '\0') {
				throw "map to short";
			}
			return;
		}
		*mptr = (char)f->get();
		mptr++;
	}
	throw "eof";

}

Board::Board(const Board& board): height(board.height), width(board.width)
{
	map = new char[height * width + 1];
	std::memcpy(map, board.map, (height * width + 1) * sizeof(char));
}


Board::~Board()
{
	if (map != nullptr) {
		delete [] map;
	}
}
Board& Board::operator=(const Board& other)
{
	if (this != &other) {
		width = other.width;
		height = other.height;
		delete[] map;
		map = new char[height * width + 1];
		std::memcpy(map, other.map, (height * width + 1) * sizeof(char));
	}
	return *this;
}
const char Board::getCoord(int x, int y)
{
	// INDEX OUT OF BOUNDS
	if((x<0 || x> width)|| ( y<0 ||y>height)) return 'u';
	return map[y * width + x];
}
const int Board::getWidth()
{
	return width;
}
const int Board::getHeight()
{
	return height;
}
bool Board::isCoordEmpty(int x, int y)
{
	return getCoord(x,y) == ' ';
}
bool Board::isWithinBounds(int x, int y)
{
	return (x>=0 && x< width)&& ( y>=0 && y<height);
}

//returns a null terminated array
const char* Board::exportMap()
{
	return map;
}
;
