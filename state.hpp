//
//  state.hpp
//  ai_8queen
//
//  Created by Berke Yavas on 5.12.2020.
//

#ifndef state_hpp
#define state_hpp

#include "queen.hpp"
#include <vector>

class State {
    std::vector<Queen> table;

    
    
public:
    State();
    ~State();
    
    std::vector<State> createSuccessors();
    State bestSuccessor();
    int countCollisions();
    std::vector<Queen>& getTable();
    void printBoard(std::ofstream &f);
    
    State& operator=(const State& s);
    
};

#endif /* state_hpp */
