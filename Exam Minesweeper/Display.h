#pragma once
#include "CombinedLayer.h"
#include "string"
#include "FileManager.h"
class Display
{
private:
	CombinedLayer* board;
	FileManager* fm;

public:
	Display(CombinedLayer* b, FileManager* fm);
	static int getNumber(int min, int max);
	void print();
	void getUserInput();
	bool issueCommand(std::string s);
	bool executeCoord(std::string s, bool mark);
	void Dead();
	void Won();
};

