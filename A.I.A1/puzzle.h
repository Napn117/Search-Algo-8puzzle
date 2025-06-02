#ifndef PUZZLE_H
#define PUZZLE_H

#include <string>
#include <vector>

using namespace std;

class Puzzle {
public:
    string state;
    string goal;    
    string path;    
    
    int g;               
    int hValue;          
    int f;              
    int h(int heuristicFunction);

    void updateFCost();

    bool goalMatch() const;
    bool canMoveUp() const;
    bool canMoveDown() const;
    bool canMoveLeft() const;
    bool canMoveRight() const;

    Puzzle(const Puzzle& p); 
    Puzzle(const string& initialState, const string& goalState);
    Puzzle* moveUp() const;
    Puzzle* moveDown() const;
    Puzzle* moveLeft() const;
    Puzzle* moveRight() const;
};

#endif
