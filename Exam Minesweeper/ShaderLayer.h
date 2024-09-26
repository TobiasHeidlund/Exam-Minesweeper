#pragma once
#include "Board.h"
#include "string"
class ShaderLayer:public Board
{
private: 
	int remaingHidden;
public:
	ShaderLayer(int h, int w);
	ShaderLayer(int h, int w, std::ifstream* file);
	ShaderLayer(const ShaderLayer& bl);
	ShaderLayer& operator=(const ShaderLayer* other);
	bool isVisable(int x, int y);
	void setVisable(int x, int y);
	void setMark(int x, int y);
	bool isMark(int x, int y);
	const int remainingHidden();
	std::string toFile();
};

