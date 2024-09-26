#pragma once
#include "BombLayer.h"
#include "ShaderLayer.h"
#include "string"
#include <fstream>
#include <iostream>
class CombinedLayer
{
private:
	ShaderLayer* sl;
	BombLayer* bl;
	int width, height, openTiles;
	bool alive, playing;
public:
	static const int minWidth = 5, maxWidth = 20, minHeight = 5, maxHeight = 9;
	CombinedLayer(int w, int h, int b);
	CombinedLayer(int w, int h, BombLayer* b, ShaderLayer* sl, int ot);
	~CombinedLayer();
	CombinedLayer& operator=(const CombinedLayer* other);
	char unvail(int x, int y);
	const int getWidth();
	const int getHeight();
	const char getValueOfCoord(int x, int y);
	const bool isAlive();
	void mark(int x, int y);
	void setDead();
	void stopPlaying();
	const bool isPlaying();
	const bool allUnvailed();
	const std::string toFile();
	static CombinedLayer* fromFile(std::ifstream* s);
};

