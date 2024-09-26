#pragma once
#include <fstream>
class Util
{
public:
	static int lineToint(std::ifstream* s);
	static bool validInt(int i, int min, int max);
};

