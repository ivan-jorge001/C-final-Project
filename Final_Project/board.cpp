//
//  board.cpp
//  Final_Project
//
//  Created by Ivan Jorge on 4/15/18.
//  Copyright © 2018 Ivan Jorge. All rights reserved.
//
#include "boardHelper.hpp"
#include "board.hpp"
#include <iostream>

/*
 * 61: "=" border
 * 124: "|" border
 * 46: "." empty
 * 35: "#" HVT
 * 36: "$" human
 * 86: "V" VSI
 * 73: "I" ISI
 * 79: "O" ISI Infected
 * 48: "0" VSI Infected
*/

const char BORDER_X = char(61);
const char BORDER_Y = char(124);
const char EMPTY = char(46);
const char HVT = char(35);
//DELETE const char HUMAN = char(36);
//DELETE const char VSI = char(86);
//DELETE const char ISI = char(73);

void Board::setCorners() {
    this->boardTable[0][0] = BORDER_X;
    this->boardTable[0][this->dimensionX - 1] = BORDER_X;
    this->boardTable[this->dimensionY - 1][0] = BORDER_X;
    this->boardTable[this->dimensionY - 1][this->dimensionX - 1] = BORDER_X;
}

void Board::initBoard() {
    for (int y = 0; y < this->dimensionY; y++) {
        for (int x = 0; x < this->dimensionX; x++) {
            if (!y || y == this->dimensionY - 1) {
                this->boardTable[y][x] = BORDER_X;
            } else if (!x || x == this->dimensionX - 1){
                this->boardTable[y][x] = BORDER_Y;
            } else {
                this->boardTable[y][x] = EMPTY;
            }
        }
    }
    this->setCorners();
    this->renderHighValueTargets();
}

void Board::printBoard() {
    std::cout << "\n\n\n";
    for (int y = 0; y < this->dimensionY; y++) {
        for (int x = 0; x < this->dimensionX; x++) {
            std::cout << this->boardTable[y][x];
        }
        if (y == 0) {
            std::cout <<  " BOARD: " <<std::endl;
        } else if (y == 2) {
            std::cout <<  "   Turns: " << std::endl;
        } else if (y == 3) {
            std::cout <<  "   Players: ";
            std::cout <<  "   Status: ";
            std::cout <<  "   Life: \n";
        }  else if (y == 4) {
            std::cout <<  "   Enemies: " << std::endl;
        } else {
            std::cout << std::endl;
        }
    }
}

bool Board::isNearMe(char chip, int range, int positionX, int positionY) {
    int rangeX = (positionX - range) < 0 ? positionX - range : 0;
    int rangeY = (positionY - range) < 0 ? positionY - range : 0;

    for (int x = rangeX; x <= (range + positionX); x++) {
        for (int y = rangeY; y <= (range + positionY); y++) {
            if (this->boardTable[x][y] == chip) {
                return true;
            }
        }
    }

    return false;
}

void Board::renderHighValueTargets() {
    HighValueTargets targets[this->number_of_Hvt];
    for (int i = 0; i < this->number_of_Hvt; i++) {
        int positionX = 0, positionY = 0;
        do {
            positionX = boardHelper::randomNumber(this->dimensionX);
            positionY = boardHelper::randomNumber(this->dimensionY);
            //DELETE std::cout << (positionX < 0) << "||" << (positionX >= this->dimensionX - 1) << "||"<< (positionY < 0) << "||" << (positionY >= this->dimensionY - 1) << std::endl;
        } while (positionX < 0 || positionX >= this->dimensionX - 1 || positionY < 0 || positionY >= this->dimensionY - 1);
        targets[i].x = positionX;
        targets[i].y = positionY;
    }

    for (int i = 0; i < this->number_of_Hvt; i++) {
        // DELETE std::cout<< targets[i].x << " === " << targets[i].y <<std::endl;
        this->boardTable[targets[i].y][targets[i].x] = HVT;

    }
    this->printBoard();
};

HighValueTargets* Board::getHvt() {
    return this->targets;
}

void Board::render(int x, int y, char figure) {
    if (Board::isPositionAvailable(x, y)) {
        this->boardTable[x][y] = figure;
        // std::cout << "success rendering\n";
        Board::printBoard();
        return;
    }
    std::cout << "not rendering\n";
    return;
}

void Board::render(int x, int y, char figure, int prevX, int prevY) {


    if (Board::isPositionAvailable(x, y) || (x == prevX && y == prevY)) {
        this->boardTable[prevX][prevY] = EMPTY;
        this->boardTable[x][y] = figure;
        // std::cout << "success rendering\n";
        Board::printBoard();
        return;
    }
    std::cout << "not rendering\n";
    return;
}

void Board::renderOnSpot(int x, int y, char figure) {
    this->boardTable[x][y] = figure;
    Board::printBoard();
    return;
}

bool Board::isPositionAvailable(int x, int y) {
    if (this->boardTable[x][y] && this->boardTable[x][y] == EMPTY) {
        return true;
    }
    return false;
}

void Board::clear(int x, int y) {
    this->boardTable[x][y] = EMPTY;
};
