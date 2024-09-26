#include "ShaderLayer.h"
#include "string"
#include <fstream>
#include "Util.h"
ShaderLayer::ShaderLayer(int h, int w) :Board(h, w), remaingHidden(h* w)
{
}



bool ShaderLayer::isVisable(int x, int y)
{
	return getCoord(x,y) == 'v';
}

void ShaderLayer::setVisable(int x, int y)
{
	remaingHidden--;
	setCoord(x, y, 'v');
}

void ShaderLayer::setMark(int x, int y)
{
	setCoord(x, y, 'P');
}

bool ShaderLayer::isMark(int x, int y)
{
	return getCoord(x, y) == 'P';
}

const int ShaderLayer::remainingHidden()
{
	return remaingHidden;
}

ShaderLayer::ShaderLayer(int height, int width, std::ifstream* file) :
	Board(height, width, file)
{

	int i = Util::lineToint(file);
	if (!Util::validInt(i, 1, 300)) {
		throw "invalid hidden";
	}
	remaingHidden = i;

}

ShaderLayer::ShaderLayer(const ShaderLayer& sl) : Board(sl), remaingHidden(sl.remaingHidden)
{
}

ShaderLayer& ShaderLayer::operator=(const ShaderLayer* other)
{
	if (this != other) {
		width = other->width;
		height = other->height;
		remaingHidden = other->remaingHidden;
		Board::operator=(*other);
	}
	return *this;
}


std::string ShaderLayer::toFile() {
	std::string s = std::string(exportMap());
	s.append("\n");
	s.append(std::to_string(remaingHidden));
	s.append("\n");
	return s;
}