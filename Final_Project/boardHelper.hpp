//
//  boardHelper.hpp
//  Final_Project
//
//  Created by Ivan Jorge on 4/19/18.
//  Copyright © 2018 Ivan Jorge. All rights reserved.
//

#ifndef boardHelper_hpp
#define boardHelper_hpp

#include <stdio.h>
#include <iostream>
#include "action.hpp"
#include "board.hpp"

namespace boardHelper {
    int randomNumber(int range);
    bool isRandomNumInBoard(int range_max, int number);
    void move(std::string, Board, int&, int&, char);
    Action listenForKeyDown();
}
#endif /* boardHelper_hpp */
