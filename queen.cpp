//
//  queen.cpp
//  ai_8queen
//
//  Created by Berke Yavas on 5.12.2020.
//

#include "queen.hpp"

// CONSTRUCTOR
Queen::Queen(int x, int y):x(x), y(y){}
Queen::~Queen(){}

// SETTER AND GETTER
int Queen::getQueenPosX(){ return x; }
int Queen::getQueenPosY(){ return y; }
void Queen::setQueenPosX(int x){ this->x = x;}
void Queen::setQueenPosY(int y){ this->y = y; }


// UTILITY FUNCTIONS
move Queen::moveLeft()
{
    if(x > 0){
        --x;
        return GO;
    }
    return STOP;
}



move Queen::moveRight(){
    if(x < 7){
        ++x;
        return  GO;
    }
    return STOP;
}
