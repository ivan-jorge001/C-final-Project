//
//  boardHelper.cpp
//  Final_Project
//
//  Created by Ivan Jorge on 4/19/18.
//  Copyright © 2018 Ivan Jorge. All rights reserved.
//
#include <stdio.h>
#include <iostream>
#include "boardHelper.hpp"
#include "action.hpp"
#include "board.hpp"

const char KEY_UP_W = char(87);
const char KEY_UP_w = char(119);
const char KEY_RIGHT_A = char(65);
const char KEY_RIGHT_a = char(97);
const char KEY_LEFT_d = char(100);
const char KEY_LEFT_D = char(68);
const char KEY_DOWN_S = char(83);
const char KEY_DOWN_s = char(115);
const char KEY_DOWN_n = char(110);
const char KEY_DOWN_N = char(78);
const char KEY_DOWN_m = char(109);
const char KEY_DOWN_M = char(77);
const std::string UP = "up";
const std::string LEFT = "left";
const std::string RIGHT = "right";
const std::string DOWN = "down";
const std::string TYPE_MOVE = "move";
const std::string TYPE_ATTACK = "attack";
const std::string ATTACK_NETFILTER = "NF";
const std::string ATTACK_SNOOP_DESTROYER = "SD";


namespace boardHelper {
    int randomNumber(int range) {
        return rand() % range + 1;
    };

    bool isRandomNumInBoard(int range_max, int number) {
        return number < 0 || number >= range_max - 1;
    }

    Action listenForKeyDown() {
        bool correctInput = false;
        Action playerAction;
        do {
            system("stty raw");
            std::cout << "\nPlease enter an action" << std::endl;
            char input = getchar();
            system("stty cooked");

            switch(input) {
                case KEY_UP_W :
                    // DELETE std::cout << "KEY_UP_W" << std::endl;
                    correctInput = true;
                    playerAction.type = TYPE_MOVE;
                    playerAction.action =  UP;
                    return playerAction;
                    break;
                case KEY_UP_w :
                    correctInput = true;
                    // DELETE std::cout << "KEY_UP_w" << std::endl;
                    playerAction.type = TYPE_MOVE;
                    playerAction.action =  UP;
                    return playerAction;
                    break;
                case KEY_RIGHT_A :
                    correctInput = true;
                    // DELETE std::cout << "KEY_RIGHT_A" << std::endl;
                    playerAction.type = TYPE_MOVE;
                    playerAction.action =  LEFT;
                    return playerAction;
                    break;
                case KEY_RIGHT_a :
                    correctInput = true;
                    // DELETE std::cout << "KEY_RIGHT_a" << std::endl;
                    playerAction.type = TYPE_MOVE;
                    playerAction.action =  LEFT;
                    return playerAction;
                    break;
                case KEY_LEFT_d :
                    correctInput = true;
                    // DELETE std::cout << "KEY_LEFT_d" << std::endl;
                    playerAction.type = TYPE_MOVE;
                    playerAction.action = RIGHT;
                    return playerAction;
                    break;
                case KEY_LEFT_D :
                    correctInput = true;
                    // DELETE std::cout << "KEY_LEFT_D" << std::endl;
                    playerAction.type = TYPE_MOVE;
                    playerAction.action = RIGHT;
                    return playerAction;
                    break;
                case KEY_DOWN_S :
                    correctInput = true;
                    // DELETE std::cout << "KEY_DOWN_S" << std::endl;
                    playerAction.type = TYPE_MOVE;
                    playerAction.action = DOWN;
                    return playerAction;
                    break;
                case KEY_DOWN_s :
                    correctInput = true;
                    // DELETE std::cout << "KEY_DOWN_s" << std::endl;
                    playerAction.type = TYPE_MOVE;
                    playerAction.action = DOWN;
                    return playerAction;
                    break;
                case KEY_DOWN_n :
                    correctInput = true;
                    // DELETE std::cout << "KEY_DOWN_S" << std::endl;
                    playerAction.type = TYPE_ATTACK;
                    playerAction.action = ATTACK_NETFILTER;
                    return playerAction;
                    break;
                case KEY_DOWN_N :
                    correctInput = true;
                    // DELETE std::cout << "KEY_DOWN_s" << std::endl;
                    playerAction.type = TYPE_ATTACK;
                    playerAction.action = ATTACK_NETFILTER;
                    return playerAction;
                    break;
                case KEY_DOWN_m :
                    correctInput = true;
                    // DELETE std::cout << "KEY_DOWN_S" << std::endl;
                    playerAction.type = TYPE_ATTACK;
                    playerAction.action = ATTACK_SNOOP_DESTROYER;
                    return playerAction;
                    break;
                case KEY_DOWN_M :
                    correctInput = true;
                    // DELETE std::cout << "KEY_DOWN_s" << std::endl;
                    playerAction.type = TYPE_ATTACK;
                    playerAction.action = ATTACK_SNOOP_DESTROYER;
                    return playerAction;
                    break;
                default:
                    correctInput = false;
                    std::cout << " Enter the wrong command please, retry\n";
                    break;
            }
        } while(correctInput);
        return playerAction;
    };

    void move(std::string direction, Board board, int& x, int& y, char chip) {
        int prevX = x, prevY = y;
        if (direction == UP) {
            x -=1;
        }

        if (direction == DOWN) {
            x +=1;
        }

        if (direction == LEFT) {
            y -=1;
        }

        if (direction == RIGHT) {
            y +=1;
        }

        if (board.isPositionAvailable(x, y)) {
            board.render(x, y, chip, prevX, prevY);
        } else {
            x = prevX;
            y = prevY;
        }
    }
}
