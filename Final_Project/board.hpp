//
//  board.hpp
//  Final_Project
//
//  Created by Ivan Jorge on 4/15/18.
//  Copyright © 2018 Ivan Jorge. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include <stdio.h>
struct HighValueTargets {
  int x, y;
};

class Board {
private:
    char** boardTable;
    int dimensionX, dimensionY, number_of_Hvt;
    HighValueTargets * targets;

public:
    Board(int boardX, int boardY, int number_of_Hvts)
    {
        this->dimensionX = boardX;
        this->dimensionY = boardY;
        this->number_of_Hvt = number_of_Hvts;
        this->targets = new HighValueTargets [number_of_Hvts];
        this->boardTable = new char* [boardY];
        for (int y = 0; y < boardY; y++) {
            this->boardTable[y] = new char [boardX];
        }
    }

    void setCorners();
    HighValueTargets* getHvt();
    void initBoard();
    void printBoard();
    void renderHighValueTargets();
    void render(int, int, char);
    void renderOnSpot(int, int, char);
    void render(int, int, char, int, int);
    bool isPositionAvailable(int, int);
    bool isNearMe(char, int, int, int);
    void clear(int, int);
};

#endif /* board_hpp */
