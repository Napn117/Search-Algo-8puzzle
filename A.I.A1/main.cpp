#include "algorithm.h"
#include "Puzzle.h" 
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#if defined __unix__ || defined __APPLE__
    #include <graphics.h>
    #include <unistd.h> 
#elif defined __WIN32__
    #include <windows.h>
    #include "graphics2.h"
#endif

using namespace std;

// Struct for storing the results.
struct SearchResult {
    string algorithm;
    string initialState;
    string goalState;
    string solutionPath;
    int pathLength;
    int numOfStateExpansions;
    int maxQLength;
    float actualRunningTime;
    int numOfDeletionsFromMiddleOfHeap;
    int numOfLocalLoopsAvoided;
    int numOfAttemptedNodeReExpansions;
};

// This function specifies which algorithm to run on the initial states, with a given end goal state.
void runAlgorithm(const string& algorithm, vector<SearchResult>& results) {
    vector<string> startStates = { "120483765", "208135467", "704851632", "536407182", "638541720"};
    string goalState = "123456780";

    for (const auto& initialState : startStates) {
        SearchResult result;
        result.algorithm = algorithm;
        result.initialState = initialState;
        result.goalState = goalState;
        result.numOfStateExpansions = 0;
        result.maxQLength = 0;
        result.actualRunningTime = 0.0f;

        // Call the relevant algorithm based on the mode
        if (algorithm == "uc_explist") {
            result.solutionPath = uc_explist(
                initialState,
                goalState,
                result.pathLength,
                result.numOfStateExpansions,
                result.maxQLength,
                result.actualRunningTime
            );
        } else if (algorithm == "astar_explist_manhattan") {
            result.solutionPath = aStar_ExpandedList(
                initialState, 
                goalState, 
                result.pathLength, 
                result.numOfStateExpansions, 
                result.maxQLength, 
                result.actualRunningTime, 
                1
            ); 
        } else if (algorithm == "astar_explist_misplacedtiles") {
            result.solutionPath = aStar_ExpandedList(
                initialState, 
                goalState, 
                result.pathLength, 
                result.numOfStateExpansions, 
                result.maxQLength, 
                result.actualRunningTime, 
                0
            );  
        }

        result.pathLength = result.solutionPath.length();
        results.push_back(result);
    }
}

// This function allows the user to run single/multiple or all algorithms based on the mode.
// Output the results to a CSV file.
void batch_run(const string& mode) {
    vector<SearchResult> results;

    if (mode == "all") {
        runAlgorithm("uc_explist", results);
        runAlgorithm("astar_explist_misplacedtiles", results);
        runAlgorithm("astar_explist_manhattan", results);
    } else {
        runAlgorithm(mode, results);
    }

    ofstream outputFile("batch_run_results.csv");
    outputFile << "Algorithm,Init_State,Goal_State,PathLength,StateExpansions,MaxQueueLength,RunningTime,Path\n";
    for (const auto& result : results) {
        outputFile << result.algorithm << ","
                   << result.initialState << ","
                   << result.goalState << ","
                   << result.pathLength << ","
                   << result.numOfStateExpansions << ","
                   << result.maxQLength << ","
                   << result.actualRunningTime << ","
                   << result.solutionPath << "\n";
    }
    outputFile.close();
    cout << "Batch run completed. Results saved to batch_run_results.csv\n";
}

// Program starts here. Checks for algorithm selected otherwise default too all.
int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "No command-line arguments provided. Defaulting to batch_run all." << endl;
        string mode = "all";
        batch_run(mode);
    } else {
        string mode = argv[2];
        if (mode == "uc_explist" || mode == "astar_explist_manhattan" || mode == "astar_explist_misplacedtiles" || mode == "all") {
            batch_run(mode);
        } else {
            cerr << "Unknown algorithm: " << mode << "\n";
            return 1;
        }
    }

    return 0;
}
