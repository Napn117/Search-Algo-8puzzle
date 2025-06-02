#include "Puzzle.h"
#include <queue>
#include <unordered_map>
#include <ctime>
#include <iostream>
#include <memory>

using namespace std;

// Uniform Cost Search Algorithm function.
// Explores all possible states equally.
// Until goal is reached, continues expanding nodes with lowest cost.

string uc_explist(
    const string& initialState, 
    const string& goalState, 
    int& pathLength, 
    int& numOfStateExpansions, 
    int& maxQLength, 
    float& actualRunningTime) 
{
    clock_t startTime = clock();
    auto compare = [](Puzzle* a, Puzzle* b) { return a->f > b->f; };
    priority_queue<Puzzle*, vector<Puzzle*>, decltype(compare)> openList(compare);
    unordered_map<string, int> visited;
    Puzzle* start = new Puzzle(initialState, goalState); 
    start->updateFCost();
    openList.push(start);
    maxQLength = 1;
    numOfStateExpansions = 0;
    while (!openList.empty()) {
        size_t sizeBeforePop = openList.size();
        Puzzle* current = openList.top();
        openList.pop();
        if (current->goalMatch()) {
            pathLength = current->path.length();
            actualRunningTime = ((float)(clock() - startTime) / CLOCKS_PER_SEC);
            string resultPath = current->path;
            delete current;
            return resultPath;
        }

    if (visited.find(current->state) != visited.end() && visited[current->state] <= current->g) {
        delete current;
        continue;
    }

        visited[current->state] = current->g;
        numOfStateExpansions++;

        if (current->canMoveUp()) {
            Puzzle* upPuzzle = current->moveUp();
            upPuzzle->updateFCost();
            if (visited.find(upPuzzle->state) == visited.end() || visited[upPuzzle->state] > upPuzzle->g) {
                openList.push(upPuzzle);
            }
        }
        if (current->canMoveDown()) {
            Puzzle* downPuzzle = current->moveDown();
            downPuzzle->updateFCost();
            if (visited.find(downPuzzle->state) == visited.end() || visited[downPuzzle->state] > downPuzzle->g) {
                openList.push(downPuzzle);
            }
        }
        if (current->canMoveLeft()) {
            Puzzle* leftPuzzle = current->moveLeft();
            leftPuzzle->updateFCost();
            if (visited.find(leftPuzzle->state) == visited.end() || visited[leftPuzzle->state] > leftPuzzle->g) {
                openList.push(leftPuzzle);
            }
        }
        if (current->canMoveRight()) {
            Puzzle* rightPuzzle = current->moveRight();
            rightPuzzle->updateFCost();
            if (visited.find(rightPuzzle->state) == visited.end() || visited[rightPuzzle->state] > rightPuzzle->g) {
               openList.push(rightPuzzle);
            }   
        }

        maxQLength = max(maxQLength, (int)openList.size());
        delete current;
    }

    actualRunningTime = ((float)(clock() - startTime) / CLOCKS_PER_SEC);
    pathLength = 0;
    return "";
}

// A* Search Algorithm function (Misplaced tiles & Manhattan tiles).
// Uses heuristic to focus on the best path.
// Expands nodes based on a combination of cost to reach the current state and estimated cost to reach the goal.
string aStar_ExpandedList(
    const string& initialState, 
    const string& goalState, 
    int& pathLength, 
    int& numOfStateExpansions, 
    int& maxQLength, 
    float& actualRunningTime, 
    int heuristicFunction) 
{
    clock_t startTime = clock();
    auto compare = [](Puzzle* a, Puzzle* b) { return a->f > b->f; };
    std::priority_queue<Puzzle*, std::vector<Puzzle*>, decltype(compare)> openList(compare);
    unordered_map<string, int> visited;  
    Puzzle* start = new Puzzle(initialState, goalState);
    start->h(heuristicFunction);
    start->updateFCost();
    openList.push(start);
    maxQLength = 1;
    numOfStateExpansions = 0;

    while (!openList.empty()) {
        size_t sizeBeforePop = openList.size();

        Puzzle* current = openList.top();
        openList.pop();

        if (current->goalMatch()) {
            pathLength = current->path.length();
            actualRunningTime = ((float)(clock() - startTime) / CLOCKS_PER_SEC);
            std::string resultPath = current->path;
            delete current;
            return resultPath;
        }

        if (visited.find(current->state) != visited.end() && visited[current->state] <= current->g) {
            delete current;
            continue;
        }

        visited[current->state] = current->g;
        numOfStateExpansions++;

        if (current->canMoveUp()) {
            Puzzle* upPuzzle = current->moveUp();
            upPuzzle->h(heuristicFunction);
            upPuzzle->updateFCost();
                if (visited.find(upPuzzle->state) == visited.end() || visited[upPuzzle->state] > upPuzzle->g) {
                    openList.push(upPuzzle);
                }
        }
        if (current->canMoveDown()) {
            Puzzle* downPuzzle = current->moveDown();
            downPuzzle->h(heuristicFunction);
            downPuzzle->updateFCost();
            if (visited.find(downPuzzle->state) == visited.end() || visited[downPuzzle->state] > downPuzzle->g) {
                openList.push(downPuzzle);
            }
        }       
        if (current->canMoveLeft()) {
            Puzzle* leftPuzzle = current->moveLeft();
            leftPuzzle->h(heuristicFunction);
            leftPuzzle->updateFCost();
            if (visited.find(leftPuzzle->state) == visited.end() || visited[leftPuzzle->state] > leftPuzzle->g) {
                openList.push(leftPuzzle);
            }
        }
        if (current->canMoveRight()) {
            Puzzle* rightPuzzle = current->moveRight();
            rightPuzzle->h(heuristicFunction);
            rightPuzzle->updateFCost();
            if (visited.find(rightPuzzle->state) == visited.end() || visited[rightPuzzle->state] > rightPuzzle->g) {
                openList.push(rightPuzzle);
            }
        }

        maxQLength = max(maxQLength, (int)openList.size());
        delete current;
    }

    actualRunningTime = ((float)(clock() - startTime) / CLOCKS_PER_SEC);
    pathLength = 0;
    return "";
}
