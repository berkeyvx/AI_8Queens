//
//  state.cpp
//  ai_8queen
//
//  Created by Berke Yavas on 5.12.2020.
//

#include "state.hpp"
#include <random>
#include <iostream>
#include <fstream>
#include <array>



State::State(){
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(0,7);
    
    for (int i = 0; i < 8; ++i) {
        Queen q(distribution(generator), i);
        this->table.push_back(q);
    }
}

State::~State(){}
std::vector<Queen>& State::getTable(){ return table; }



std::vector<State> State::createSuccessors(){
    std::vector<State> successors;
    int curr_x, curr_y;
    for (int i = 0; i < 8; ++i) {
        curr_x = table[i].getQueenPosX();
        curr_y = table[i].getQueenPosY();
        
        while(table[i].moveLeft() != STOP)
            successors.push_back(*this);
        
        table[i].setQueenPosX(curr_x);
        table[i].setQueenPosY(curr_y);
        
        while (table[i].moveRight() != STOP) {
            successors.push_back(*this);
        }
        
        table[i].setQueenPosY(curr_y);
        table[i].setQueenPosX(curr_x);
    }
    
    return successors;
}



State State::bestSuccessor(){
    auto successors = this->createSuccessors();
    int maxCollision = 64;
    std::vector<int> bestSuccessorIndex;
    int collisions;
    
    for (int i = 0; i < successors.size(); ++i) {
        collisions = successors.at(i).countCollisions();
        if (collisions < maxCollision) {
            maxCollision = collisions;
            bestSuccessorIndex.clear();
            bestSuccessorIndex.push_back(i);
        }
        else if (collisions == maxCollision)
            bestSuccessorIndex.push_back(i);
    }
    
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(0,static_cast<int>(bestSuccessorIndex.size() - 1));
    
    int randomIndex = distribution(generator);
    
    return successors[bestSuccessorIndex[randomIndex]];
}



int State::countCollisions(){
    int countAttacksInRows = 0;
    std::array<int, 8> queensByRow;
    queensByRow.fill(0);
    
    int countAttacksInDiagonal = 0;
    std::array<int,15>  queensByDiagnoal,queensByAntiDiagonal;
    queensByDiagnoal.fill(0);
    queensByAntiDiagonal.fill(0);
    
    int x,y;
    for (int i = 0; i < 8; ++i) {
        x = table[i].getQueenPosX();
        y = table[i].getQueenPosY();
        ++queensByRow[x];
        ++queensByDiagnoal[x+y];
        ++queensByAntiDiagonal[7+y-x];
    }
    
    for (int i = 0; i < 8; ++i) {
        if (queensByRow[i] > 1) {
            countAttacksInRows += queensByRow[i] - 1;
        }
    }
    
    for (int i = 0; i < 15; ++i) {
        if (queensByDiagnoal[i] > 1) {
            countAttacksInDiagonal += queensByDiagnoal[i] - 1;
        }
        
        if (queensByAntiDiagonal[i] >  1) {
            countAttacksInDiagonal += queensByAntiDiagonal[i] -1 ;
        }
    }
    
    return countAttacksInDiagonal + countAttacksInRows;
}



void State::printBoard(std::ofstream &f){
    f.open("out.txt", std::ios::app);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if(table[i].getQueenPosX() == j){
                std::cout << "W";
                f << "W";
            }else{
                std::cout <<  "_";
                f << "_";
            }
        }
        std::cout << "\n";
        f << "\n";
    }
    std::cout << "\n\n";
    f << "\n\n";
    f.close();
}



State& State::operator=(const State& s){
    this->table =  s.table;
    return *this;
}
