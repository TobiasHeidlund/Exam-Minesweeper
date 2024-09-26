#include "CombinedLayer.h"
#include <iostream>
#include "Util.h"

CombinedLayer::CombinedLayer(int w, int h, int b) :bl(new BombLayer(h, w, b)), sl(new ShaderLayer(h, w)), width(w), height(h),
alive(true), playing(true), openTiles(w* h - b)
{}

CombinedLayer::CombinedLayer(int w, int h, BombLayer * b, ShaderLayer * s, int ot) :bl(b), sl(s), width(w), height(h),
alive(true), playing(true), openTiles(ot)
{

}

CombinedLayer::~CombinedLayer()
{
	delete(sl);
	delete(bl);
}

CombinedLayer& CombinedLayer::operator=(const CombinedLayer* other)
{
	if (this != other) {
		width = other->width;
		height = other->height;
		alive = other->alive;
		playing = other->playing;
		openTiles = other->openTiles;
		BombLayer* nbl = new BombLayer(*other->bl);
		*bl = nbl;
		delete(nbl);
		ShaderLayer* nsl = new ShaderLayer(*other->sl);
		*sl = nsl;
		delete(nsl);
		
	}
	return *this;
}

char CombinedLayer::unvail(int x, int y)
{
	if (!bl->isWithinBounds(x, y)) {
		return 'u';
	}
	else if (bl->isCoordMine(x, y)) {
		return 'b';
	}
	else if (sl->isVisable(x,y))
	{
		return 'u';
	}
	else if(bl->isCoordNumber(x,y))
	{
		sl->setVisable(x, y);
	}else{
		sl->setVisable(x, y);

		//Unvail area of empty slots
		for (int lx = -1; lx < 2; lx++)
		{
			for (int ly = -1; ly < 2; ly++)
			{
				if (!sl->isVisable(x+ lx,y+ly) && sl->isWithinBounds(x+ lx,y+ly)) {
					char v = unvail(x+ lx, y+ ly);
					if (v == 'w') {
						return 'w';
					}
				//std::cout << x + lx << "\t" << y + ly << "\t" << v << std::endl;
				}
			}
		}
	}
	if (sl->remainingHidden()- bl->numberOfMines() <= 0) {
		return 'w';
	}
	return 'g';
}

const int CombinedLayer::getWidth()
{
	return width;
}

const int CombinedLayer::getHeight()
{
	return height;
}

const char CombinedLayer::getValueOfCoord(int x, int y)
{
	if (sl->isVisable(x, y)) {
	//if (true) {
		return bl->getCoord(x, y);
	}else if(sl->isMark(x,y)){
		return 'P';
	}
	else return 'x';
}

const bool CombinedLayer::isAlive()
{
	return alive;
}

void CombinedLayer::mark(int x, int y)
{
	sl->setMark(x, y);
}

void CombinedLayer::setDead()
{
	this->playing = false;
	this->alive = false;
}

void CombinedLayer::stopPlaying()
{
	this->playing = false;
}

const bool CombinedLayer::isPlaying()
{
	return this->playing;
}

const bool CombinedLayer::allUnvailed()
{
	return false;
}


//FORMAT::
/*
int width, height,openTiles;
ShaderLayer sl;
BombLayer bl;
*/


CombinedLayer* CombinedLayer::fromFile(std::ifstream* file)
{
	int w = Util::lineToint(file);
	if (!Util::validInt(w, minWidth, maxWidth)) {
		std::cout << "invalid file";
		throw;
	}
	int h = Util::lineToint(file);
	if (!Util::validInt(h, minHeight, maxHeight)) {
		std::cout << "invalid file";
		throw;
	}
	int o = Util::lineToint(file);
	if (!Util::validInt(o, minHeight* minWidth, maxWidth* maxHeight)) {
		std::cout << "invalid file";
		throw;
	}
	ShaderLayer* sl = new ShaderLayer(h, w, file);
	BombLayer* bl = new BombLayer(h, w,file);

	return new CombinedLayer(w,h,bl,sl,o);
}



const std::string CombinedLayer::toFile()
{
	std::string s = "";
	s.append(std::to_string(width) + "\n");
	s.append(std::to_string(height) + "\n");
	s.append(std::to_string(openTiles) + "\n");
	s.append(sl->toFile());
	s.append(bl->toFile());
	return s;
}

