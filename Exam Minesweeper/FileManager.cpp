#include "FileManager.h"
#include <iostream>
#include <fstream>
using namespace std;
FileManager::FileManager(CombinedLayer* l): layer(l)
{
}

void FileManager::save()
{
	ofstream myfile;
	cout << layer->toFile();
	myfile.open("save");
	myfile << layer->toFile();
	myfile.close();
	
}

const bool FileManager::hasSave()
{
	ifstream myfile = ifstream("save");

	if (myfile) {
		return true;
	}
	return false;
}

void FileManager::load()
{
	ifstream* myfile = new ifstream("save");

	if (!myfile) {
		cout << "File Does not exist"<< endl;
		return;
	}

	if (myfile->is_open())
	{
		try {
			CombinedLayer* nlayer = CombinedLayer::fromFile(myfile);
			*layer = nlayer;
			delete(nlayer);
			//layer->fromFile(myfile);
		}
		catch (const char* a) {
			cout << "Loading failed: " << a << endl;
		}
		
		myfile->close();
	}
	delete myfile;
}
