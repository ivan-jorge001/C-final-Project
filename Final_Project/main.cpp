//
//  main.cpp
//  Final_Project
//
//  Created by Ivan Jorge on 4/15/18.
//  Copyright © 2018 Ivan Jorge. All rights reserved.
//
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "board.hpp"
#include "enemy.hpp"
#include "human.hpp"
#include "boardHelper.hpp"


const char infectedVSI = char(48);
const char infectedISI = char(79);

int main(int argc, const char * argv[]) {
    bool gameOn = false;
    bool isBoardRendered = false;
    int turns = 0;
    int number_of_enemies = 2;
    std::string type1 = "vsi";
    std::string type2 = "isi";
    int dimensionX = 30;
    int dimensionY = 20;
    std::vector<Enemy *> enemies(number_of_enemies);

    srand(time(NULL));
    Board board(dimensionX, dimensionY, 5);
    board.initBoard();
    // Enemy vsi(10, 10, "vsi");
    Human player(11, 10);
    player.render(board);

    for (int i = 0; i < number_of_enemies; i++) {
        int posX, posY;
        bool validPair = false;
        do
        {
            posX = boardHelper::randomNumber(dimensionX);
            posY = boardHelper::randomNumber(dimensionY);
            // std::cout<<"available" << board.isPositionAvailable(posX, posY)<< std::endl;
            if (board.isPositionAvailable(posX, posY)) {
                validPair = true;
            }
        } while(!validPair);
        enemies.at(i) = new Enemy(posY, posX, "vsi");
        // enemies.at(i)->render(board);
    }
    for (int i = 0; i < enemies.size(); i++) {
        enemies.at(i)->render(board);
    }

    return 0;
    do
    {
        if (!isBoardRendered) {
            // vsi.render(board);
            isBoardRendered = true;
            gameOn = true;
        }
        if (player.isInfected()) {
            std::cout << "Player Has Been Infected !!!"<< std::endl;
            int damagePerTurn = player.getDamagePerTurn();
            player.removeLife(damagePerTurn);
        }

        // if (player.isDead()) {
        //     gameOn = false;
        //     std::cout << "You Have Lost"<< std::endl;
        //     return 0;
        // }

        std::cout << "Player's Life: "<< player.get_life() << std::endl;
        // std::cout << "Enemies's Energy: "<< vsi.get_energy() << std::endl;

        std::cout << "Turns: "<< (turns + 1) << std::endl;

        // if (vsi.isDead()) {
        //     board.clear(vsi.getPosition('x'), vsi.getPosition('y'));
        // }


        // if (vsi.isStun()) {
        //     vsi.erasedStun();
        // }
        // player.playTurn(board, vsi);
        // if (!vsi.isAttached()) {
        //     vsi.playTurn(board, player);
        // }

        turns++;

    } while(gameOn);
    // board.printBoard();



    // std::string direction = boardHelper::listenForKeyDown();
    // std::cout << direction;

    // if

    return 0;
}

