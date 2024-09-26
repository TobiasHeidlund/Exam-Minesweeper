#include "Util.h"
#include <iostream>
#include <fstream>
#include <string>

int Util::lineToint(std::ifstream* file)
{
	std::string s;
	std::getline(*file, s);
	return std::strtol(s.c_str(), NULL, 10);
}

bool Util::validInt(int i, int min, int max)
{
	return i>=min && i<=max;
}