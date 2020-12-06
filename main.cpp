//
//  main.cpp
//  ai_8queen
//
//  Created by Berke Yavas on 5.12.2020.
//
// HOW TO RUN:
// g++ -o main main.cpp queen.cpp state.cpp -std=c++11
// ./main

/*
 
 Steepest-Ascent Hill climbing:
    It first examines all the neighboring nodes and then selects the node closest to the solution state as of next node.
        Step 1: Evaluate the initial state, if its goal state, return int
        Step 2: Find best successor among the all neighbour
        Step 3: Continue to explore best successor until it stuck or hit the goal state
 */

#include <iostream>
#include "state.hpp"
#include "Timer.hpp"
#include <fstream>


State hillclimb(State init, std::ofstream &f){
    int collision = init.countCollisions();
    // Base case, if init is goal state return init
    if(collision == 0){
        return init;
    }
    
    State next;
    while(collision > 0){
        f.open("out.txt", std::ios::app);
        next = init.bestSuccessor();
        if(next.countCollisions() >= collision){
            f.close();
            return init;
        }
        f << "No collision: " << next.countCollisions() << "\n";
        std::cout << "No collision: " << next.countCollisions() << "\n";
        f.close();
        next.printBoard(f);
        if(next.countCollisions() == 0){
            f.close();
            return next;
        }
        init = next;
        collision = next.countCollisions();
    }
    f.close();
    return init;
}



int main(int argc, const char * argv[]) {
    double totalTimeElapsed = 0.0;
    std::ofstream f;
    f.open("out.txt",std::ios::trunc);
    f.close();
    for (int i = 0; i < 10; ++i) {
        f.open("out.txt", std::ios::app);
        f << "\n\n -------RANDOM TEST " << i << "-------\n";
        std::cout << "\n\nRandom  Test " << i <<"\n";
        Timer t;
        State s;
        f << "Initial Collision " << s.countCollisions() << "\n";
        std::cout << "Initial Collision: " << s.countCollisions() << "\n";
        f.close();
        s.printBoard(f);
        hillclimb(s, f);
        auto timeElapsed  = t.elapsed();
        totalTimeElapsed  += timeElapsed;
        f.open("out.txt", std::ios::app);
        f << "Time elapsed: " << std::to_string(timeElapsed) << "\n";;
        std::cout << "Time elapsed: " << t.elapsed() << "\n";
        f.close();
        t.reset();
    }
    std::cout << "\n\nTotal  Time Elapsed for 10 Random Input:  "  << totalTimeElapsed  << "\n";
    return 0;
}
