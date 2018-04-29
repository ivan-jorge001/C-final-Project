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
#include <vector>

struct HighValueTargets {
  int x, y;
};

class Board {
private:
    // char** boardTable;
    std::vector<std::vector<char>> boardTable;
    int dimensionX, dimensionY, number_of_Hvt;
    std::vector<HighValueTargets> targets;

public:
    Board(int boardX, int boardY, int number_of_Hvts)
    {
        this->dimensionX = boardX;
        this->dimensionY = boardY;
        this->number_of_Hvt = number_of_Hvts;
        targets.reserve(number_of_Hvts);
        boardTable.reserve(dimensionY);

        for (int i = 0; i < number_of_Hvt; i++) {
            HighValueTargets hvt;
            this->targets.push_back(hvt);
        }

        for (int y = 0; y < dimensionY; y++) {
            std::vector<char> row;
            row.reserve(dimensionX);
            for (int x = 0; x < dimensionX; x++) {
                row.push_back(x);
            }
            boardTable.push_back(row);
        }
        // this->boardTable = new char* [boardY];
        // for (int y = 0; y < boardY; y++) {
        //     this->boardTable[y] = new char [boardX];
        // }
    }

    void setCorners();
    std::vector<HighValueTargets> getHvt();
    int numberOfHvt();
    int getDimensionX();
    int getDimensionY();
    void initBoard();
    void printBoard();
    void ereasedHvt(int);
    void renderHighValueTargets();
    void render(int, int, char);
    void renderOnSpot(int, int, char);
    void render(int, int, char, int, int);
    bool isPositionAvailable(int, int);
    bool isNearMe(char, int, int, int);
    void clear(int, int);
};

#endif /* board_hpp */
