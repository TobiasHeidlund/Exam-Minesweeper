#pragma once
#include "CombinedLayer.h"
class FileManager
{
private:
	CombinedLayer* layer;
public:
	FileManager(CombinedLayer* layer);
	void save();
	const bool hasSave();
	void load();
};

