//
//  Timer.hpp
//  ai_8queen
//
//  Created by Berke Yavas on 6.12.2020.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <chrono> // for std::chrono functions
 
class Timer
{
private:
    // Type aliases to make accessing nested type easier
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;
    
    std::chrono::time_point<clock_t> m_beg;
 
public:
    Timer();
    void reset();
    double elapsed() const;
};

#endif /* Timer_hpp */
