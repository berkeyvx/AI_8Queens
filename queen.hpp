//
//  queen.hpp
//  ai_8queen
//
//  Created by Berke Yavas on 5.12.2020.
//

#ifndef queen_hpp
#define queen_hpp

enum move{
    STOP,
    GO
};


class Queen {
    int x;
    int y;
    
public:
    Queen(int x, int y);
    ~Queen();
    int getQueenPosX();
    int getQueenPosY();
    void setQueenPosX(int x);
    void setQueenPosY(int x);
    move moveLeft();
    move moveRight();
};

#endif /* queen_hpp */
