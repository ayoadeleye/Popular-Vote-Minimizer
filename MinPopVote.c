#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

bool setSettings(int argc, char** argv, int* year, bool* fastMode, bool* quietMode) {
    //------------------------------------------------
    // TODO: Task 1 - write the setSettings() function
    //------------------------------------------------

    // Initialize the output variables to their default values
    *year = 0;
    *fastMode = false;
    *quietMode = false;

    // Process command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-y") == 0) {
            i++;
            // Check if there is a valid year value following -y
            if (i < argc) {
                int yr = atoi(argv[i]);
                if ((yr >= 1828 && yr <= 2020) && yr % 4 == 0) {
                    *year = yr;
                }
            }
        }else if (strcmp(argv[i], "-f") == 0) {
            *fastMode = true;
        }else if (strcmp(argv[i], "-q") == 0) {
            *quietMode = true;
        } else {
            // Invalid command-line flag
            return false;
        }
    }

    // All command-line arguments processed successfully
    return true;
}


void inFilename(char* filename, int year) {
    //------------------------------------------------
    // TODO: Task 2 - write the inFilename() function
    //------------------------------------------------
    // inFilename function to generate input data file path
    snprintf(filename, 100, "data/%d.csv", year);
}

void outFilename(char* filename, int year) {
    //------------------------------------------------
    // TODO: Task 2 - write the outFilename() function
    //------------------------------------------------
    snprintf(filename, 100, "toWin/%d_win.csv", year);
}

bool parseLine(char* line, State* myState) {
    //------------------------------------------------
    // TODO: Task 4 - write the parseLine() function
    //------------------------------------------------
    // Check if the line is empty
    if (line == NULL || strlen(line) == 0) {
        return false;
    }

    // Remove the newline character if it exists at the end
    if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }

    // Tokenize the input line using commas as delimiters
    char* token = strtok(line, ",");
    if (token == NULL) {
        return false;  // Missing state name
    }
    strcpy(myState->name, token);

    token = strtok(NULL, ",");
    if (token == NULL) {
        return false;  // Missing postal code
    }
    strcpy(myState->postalCode, token);

    token = strtok(NULL, ",");
    if (token == NULL) {
        return false;  // Missing electoral votes
    }
    myState->electoralVotes = atoi(token);

    token = strtok(NULL, ",");
    if (token == NULL) {
        return false;  // Missing popular votes
    }
    myState->popularVotes = atoi(token);

    // Check if there are no extra tokens (extra commas or data)
    token = strtok(NULL, ",");
    if (token != NULL) {
        return false;  // Extra data in the line
    }

    return true;  // Successfully parsed the line
}

bool readElectionData(char* filename, State* allStates, int* nStates) {
    //-----------------------------------------------------
    // TODO: Task 5 - write the readElectionData() function
    //-----------------------------------------------------
    FILE* file = fopen(filename, "r");

    // Initialize the number of states to 0
    *nStates = 0;

    // Buffer to store a line from the file
    char line[1000];

    if(file == NULL){
        return false;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        // Check for end-of-file
        if (feof(file)) {
            break;
        }

        // Parse the line and fill the State array
        if (parseLine(line, &allStates[*nStates])) {
            (*nStates)++; // Increment the number of states
        }
    }

    // Close the file
    fclose(file);

    return true;
}

int totalEVs(State* states, int szStates) {
    //----------------------------------------------
    // TODO: Task 6 - write the totalEVs() function;
    //                note test_totalEVs() is
    //                provided in test.c to test
    //                the functionality of totalEVs()
    //                   >> make build_test
    //                   >> make run_test
    //----------------------------------------------
    int totalElectoralVotes = 0;
    for (int i = 0; i < szStates; i++) {
        totalElectoralVotes += states[i].electoralVotes;
    }
    return totalElectoralVotes;
}

int totalPVs(State* states, int szStates) {
    //--------------------------------------------------
    // TODO: Task 6 - write the totalPVs() function;
    //                then, write your own test function
    //                test_totalPVs() in test.c
    //                   >> make build_test
    //                   >> make run_test
    //--------------------------------------------------
    int totalPopularVotes = 0;
    for (int i = 0; i < szStates; i++) {
        totalPopularVotes += states[i].popularVotes;
    }
    return totalPopularVotes;
}

MinInfo minPopVoteAtLeast(State* states, int szStates, int start, int EVs) {
    //----------------------------------------------
    // TODO: Task 7 - write minPopVoteAtLeast();
    //                a recursive helper function;
    //                returns MinInfo for the subset
    //                of [states] from index [start]
    //                to the end with the minimum
    //                popular vote total that has
    //                sufficient [EVs] to win
    //----------------------------------------------

    if (EVs <= 0) {
        MinInfo result;
        result.szSomeStates = 0;
        result.subsetPVs = 0;
        result.sufficientEVs = true;
        return result; // We've achieved sufficient electoral votes; return an empty result.
    }

    if (start >= szStates) {
        MinInfo result;
        result.szSomeStates = 0;
        result.subsetPVs = 0;
        result.sufficientEVs = false;
        return result; // We've achieved sufficient electoral votes; return an empty result.
    }

    // Exclude the current state from the subset.
    MinInfo excludeState = minPopVoteAtLeast(states, szStates, start + 1, EVs);

    // Include the current state in the subset.
    MinInfo includeState = minPopVoteAtLeast(states, szStates, start + 1, EVs - states[start].electoralVotes);
    includeState.subsetPVs += (states[start].popularVotes/2) + 1;
    includeState.someStates[includeState.szSomeStates] = states[start];
    includeState.szSomeStates++;

    if (includeState.sufficientEVs && (!excludeState.sufficientEVs || includeState.subsetPVs < excludeState.subsetPVs)) {
        // If including the current state results in sufficient EVs and has fewer PVs, choose it.
        includeState.sufficientEVs = true;
        return includeState;
    } else {
        // Otherwise, choose the one without the current state.
        return excludeState;
    }
}


MinInfo minPopVoteToWin(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election
    return minPopVoteAtLeast(states, szStates, 0, reqEVs);
}

MinInfo minPopVoteAtLeastFast(State* states, int szStates, int start, int EVs, MinInfo** memo) {
    //----------------------------------------------
    // TODO: Task 8 - write minPopVoteAtLeastFast();
    //                start by copying in fully
    //                functioning code from
    //                minPopVoteAtLeast() and make
    //                additions for memoization
    //---------------------------------------------

    MinInfo result;
    if (EVs <= 0) {
        result.szSomeStates = 0;
        result.subsetPVs = 0;
        result.sufficientEVs = true;
        return result;
    }

    if (start >= szStates) {
        result.szSomeStates = 0;
        result.subsetPVs = 0;
        result.sufficientEVs = false;
        return result;
    }

    if (memo[start][EVs].subsetPVs != -1) {
        return memo[start][EVs];
    }

    // Exclude the current state from the subset.
    MinInfo excludeState = minPopVoteAtLeastFast(states, szStates, start + 1, EVs, memo);

    // Include the current state in the subset.
    MinInfo includeState = minPopVoteAtLeastFast(states, szStates, start + 1, EVs - states[start].electoralVotes, memo);
    includeState.subsetPVs += (states[start].popularVotes / 2) + 1;
    includeState.someStates[includeState.szSomeStates] = states[start];
    includeState.szSomeStates++;

    if (includeState.sufficientEVs && (!excludeState.sufficientEVs || includeState.subsetPVs < excludeState.subsetPVs)) {
        // If including the current state results in sufficient EVs and has fewer PVs, choose it.
        includeState.sufficientEVs = true;
        memo[start][EVs] = includeState;
        return includeState;
    } else {
        // Otherwise, choose the one without the current state.
        memo[start][EVs] = excludeState;
        return excludeState;
    }
}

MinInfo minPopVoteToWinFast(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election

    MinInfo** memo = (MinInfo**)malloc((szStates+1)*sizeof(MinInfo*));
    for (int i = 0; i < szStates+1; i++) {
        memo[i] = (MinInfo*)malloc((reqEVs+1)*sizeof(MinInfo));
        for (int j = 0; j < reqEVs+1; j++) {
            memo[i][j].subsetPVs = -1;
        }
    }
    MinInfo res = minPopVoteAtLeastFast(states, szStates, 0, reqEVs, memo);

    //----------------------------------------------
    // TODO: Task 8 - [memo] will go out of scope
    //                upon return, so free all
    //                heap-allocated memory for
    //                [memo] before return
    //----------------------------------------------
    for (int i = 0; i < szStates + 1; i++){
        free(memo[i]);
    }
    free(memo);

    return res;

}

int compareStatesByName(const void* a, const void* b) {
    return strcmp(((State*)a)->name, ((State*)b)->name);
}

bool writeSubsetData(char* filenameW, int totEVs, int totPVs, int wonEVs, MinInfo toWin) {
    //-----------------------------------------------------
    // TODO: Task 9 - write the writeSubsetData() function
    //-----------------------------------------------------
    FILE* file = fopen(filenameW, "w");

    if(file == NULL){
        return false;
    }

    qsort(toWin.someStates, toWin.szSomeStates, sizeof(State), compareStatesByName);


    fprintf(file, "%d,%d,%d,%d\n", totEVs, totPVs, wonEVs, toWin.subsetPVs);

    for(int i = 0; i < toWin.szSomeStates; i++){
        fprintf(file, "%s,%s,%d,%d\n", toWin.someStates[i].name, toWin.someStates[i].postalCode, toWin.someStates[i].electoralVotes, (toWin.someStates[i].popularVotes / 2) + 1);
    }

    fclose(file);

    return true;
}
