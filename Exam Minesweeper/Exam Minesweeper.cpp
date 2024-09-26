// Exam Minesweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CombinedLayer.h"
#include "Display.h"

int main()
{
    std::cout << "What width shoud the board be(" << CombinedLayer::minWidth << '-' 
        << CombinedLayer::maxWidth << ')' << std::endl;
    int width = Display::getNumber(CombinedLayer::minWidth,CombinedLayer::maxWidth);
    std::cout << "What height shoud the board be(" << CombinedLayer::minHeight << '-'
        << CombinedLayer::maxHeight << ')' << std::endl;
    int height = Display::getNumber(CombinedLayer::minHeight,CombinedLayer::maxHeight);
    std::cout << "What height shoud the board be(" << BombLayer::minBombs << '-'
        << BombLayer::maxBombs << ')' << std::endl;
    int nbrOfMines = Display::getNumber(BombLayer::minBombs,BombLayer::maxBombs);
 
    CombinedLayer* layer = new CombinedLayer(width, height, nbrOfMines);
    FileManager* fm = new FileManager(layer);
    Display disp = Display(layer,fm);
    while (layer->isPlaying()) {
        disp.print();
        disp.getUserInput();
    }
    if (layer->isAlive()) {
        disp.Won();
    }
    else {
        disp.Dead();
    }
    
    delete(fm);
    delete(layer);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
