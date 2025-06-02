
#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include <ctime>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;


string testAlgorithm(
    string const initialState, 
    string const goalState, 
    int &numOfStateExpansions, 
    int& maxQLength, 
    float &actualRunningTime, 
    int ultimateMaxDepth);
    
string aStar_ExpandedList(
    const string& initialState, 
    const string& goalState, 
    int& pathLength, 
    int& numOfStateExpansions, 
    int& maxQLength, 
    float& actualRunningTime, 
    int heuristicFunction);

string uc_explist(
    const string& initialState, 
    const string& goalState, 
    int& pathLength, 
    int& numOfStateExpansions, 
    int& maxQLength, 
    float& actualRunningTime);

#endif