#include "Puzzle.h"
#include <iostream>
#include <algorithm>
#include <cmath>

Puzzle::Puzzle(const Puzzle& p) {
    state = p.state;
    goal = p.goal;
    path = p.path;
    g = p.g;
    hValue = p.hValue;
    f = p.f;
}

Puzzle::Puzzle(const string& initialState, const string& goalState)
    : state(initialState), goal(goalState), g(0), hValue(0), f(0) {}


// Heuristic function to calculate h based on the provided heuristic function
int Puzzle::h(int heuristicFunction) {
    int sum = 0;
    switch (heuristicFunction) {
    case 0:
        for (int i = 0; i < 9; ++i) {
            if (state[i] != goal[i] && state[i] != '0') {
                sum++;
            }
        }
        hValue = sum;
        break;
    case 1:
        for (int i = 0; i < 9; ++i) {
            if (state[i] != '0') {
                int current = state[i] - '1';
                int goalPos = goal.find(state[i]);
                int rowDist = abs(i / 3 - goalPos / 3);
                int colDist = abs(i % 3 - goalPos % 3);
                sum += rowDist + colDist;
            }
        }
        hValue = sum;
        break;
    }
    return hValue;
}

// Updates the total f cost (f = g + h)
void Puzzle::updateFCost() {
    f = g + hValue;
}

// Check if the current state matches the goal state
bool Puzzle::goalMatch() const {
    return state == goal;
}

// Check if the blank (0) can move up
bool Puzzle::canMoveUp() const {
    int pos = state.find('0');
    return pos > 2;  // The blank can't move up if it's in the first row
}

// Check if the blank (0) can move down
bool Puzzle::canMoveDown() const {
    int pos = state.find('0');
    return pos < 6;  // The blank can't move down if it's in the last row
}

// Check if the blank (0) can move left
bool Puzzle::canMoveLeft() const {
    int pos = state.find('0');
    return pos % 3 != 0;  // The blank can't move left if it's in the first column
}

// Check if the blank (0) can move right
bool Puzzle::canMoveRight() const {
    int pos = state.find('0');
    return pos % 3 != 2;  // The blank can't move right if it's in the last column
}

// Move up and return a new Puzzle object
Puzzle* Puzzle::moveUp() const {
    if (!canMoveUp()) return nullptr;
    Puzzle* newPuzzle = new Puzzle(*this);
    int pos = state.find('0');
    std::swap(newPuzzle->state[pos], newPuzzle->state[pos - 3]);
    newPuzzle->g = g + 1;  // Increase g-value
    newPuzzle->path += "U";
    return newPuzzle;
}

// Move down and return a new Puzzle object
Puzzle* Puzzle::moveDown() const {
    if (!canMoveDown()) return nullptr;
    Puzzle* newPuzzle = new Puzzle(*this);
    int pos = state.find('0');
    std::swap(newPuzzle->state[pos], newPuzzle->state[pos + 3]);
    newPuzzle->g = g + 1;
    newPuzzle->path += "D";
    return newPuzzle;
}

// Move left and return a new Puzzle object
Puzzle* Puzzle::moveLeft() const {
    if (!canMoveLeft()) return nullptr;
    Puzzle* newPuzzle = new Puzzle(*this);
    int pos = state.find('0');
    std::swap(newPuzzle->state[pos], newPuzzle->state[pos - 1]);
    newPuzzle->g = g + 1;
    newPuzzle->path += "L";
    return newPuzzle;
}

// Move right and return a new Puzzle object
Puzzle* Puzzle::moveRight() const {
    if (!canMoveRight()) return nullptr;
    Puzzle* newPuzzle = new Puzzle(*this);
    int pos = state.find('0');
    std::swap(newPuzzle->state[pos], newPuzzle->state[pos + 1]);
    newPuzzle->g = g + 1;
    newPuzzle->path += "R";
    return newPuzzle;
}
