#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

bool test_totalEVs() {
    State aStates[10];
    int res;

    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 10;

    printf(" Checking totalEVs() for 5 States:\n");
    res = totalEVs(aStates,5);
    if (res != 38) {
        printf("  individual state EVs are 5, 8, 13, 6, 7\n");
        printf("  expected total EVs = 38, actual total EVs = %d\n",res);
        return 0;
    }

    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 15;
    aStates[6].electoralVotes = 12;
    aStates[7].electoralVotes = 8;
    aStates[8].electoralVotes = 14;
    aStates[9].electoralVotes = 13;

    printf(" Checking totalEVs() for 10 States:\n");
    res = totalEVs(aStates,10);
    if (res != 100) {
        printf("  expected total EVs = 100, actual total EVs = %d\n",res);
        return false;
    }

    return true;
}

bool test_totalPVs() {
    //--------------------------------------------------------
    // TODO: Task 6 - write your own test case for totalPVs();
    //                use test_totalEVs() as a sample;
    //                make sure to test all components
    //--------------------------------------------------------
    State aStates[10];
    int res;

    aStates[0].popularVotes = 100;
    aStates[1].popularVotes = 200;
    aStates[2].popularVotes = 300;
    aStates[3].popularVotes = 150;
    aStates[4].popularVotes = 50;

    printf("Checking totalPVs() for 5 States:\n");
    res = totalPVs(aStates, 5);
    if (res != 800) {
        printf("  individual state PVs are 100, 200, 300, 150, 50\n");
        printf("  expected total PVs = 800, actual total PVs = %d\n", res);
        return false;
    }

    aStates[0].popularVotes = 100;
    aStates[1].popularVotes = 200;
    aStates[2].popularVotes = 300;
    aStates[3].popularVotes = 150;
    aStates[4].popularVotes = 50;
    aStates[5].popularVotes = 1000;
    aStates[6].popularVotes = 800;
    aStates[7].popularVotes = 600;
    aStates[8].popularVotes = 700;
    aStates[9].popularVotes = 1200;

    printf("Checking totalPVs() for 10 States:\n");
    res = totalPVs(aStates, 10);
    if (res != 5150) {
        printf("  expected total PVs = 5150, actual total PVs = %d\n", res);
        return false;
    }

    return true;
}

bool test_setSettings() {
    //-----------------------------------------------------------
    // TODO: Task 6 - write your own test case for setSettings();
    //                use test_totalEVs() as a sample;
    //                make sure to test all components
    //-----------------------------------------------------------
    char* argv[] = { "program_name", "-y", "1992", "-f", "-q" };
    int year;
    bool fastMode, quietMode;

    bool result = setSettings(5, argv, &year, &fastMode, &quietMode);

    if (!result) {
        printf("setSettings() failed.\n");
        return false;
    }

    if (year != 1992 || !fastMode || !quietMode) {
        printf("setSettings() failed to set correct values.\n");
        return false;
    }

    return true;
}

bool test_inFilename() {
    //----------------------------------------------------------
    // TODO: Task 6 - write your own test case for inFilename();
    //                use test_totalEVs() as a sample;
    //                make sure to test all components
    //----------------------------------------------------------
    char filename[50];
    int year = 2023;

    // Test with a non-fast mode, non-quiet mode
    inFilename(filename, year);
    if (strcmp(filename, "election2023.txt") != 0) {
        printf("Test 1 failed: inFilename() with default settings\n");
        return false;
    }

    // Test with a different year and fast mode enabled
    year = 2024;
    inFilename(filename, year);
    if (strcmp(filename, "election2024_fast.txt") != 0) {
        printf("Test 2 failed: inFilename() with a different year and fast mode enabled\n");
        return false;
    }

    // Test with a different year and quiet mode enabled
    year = 2025;
    inFilename(filename, year);
    if (strcmp(filename, "election2025_quiet.txt") != 0) {
        printf("Test 3 failed: inFilename() with a different year and quiet mode enabled\n");
        return false;
    }

    // Test with a year outside the valid range
    year = 1900;
    inFilename(filename, year);
    if (strcmp(filename, "election_invalid.txt") != 0) {
        printf("Test 4 failed: inFilename() with an invalid year\n");
        return false;
    }

    printf("All tests passed: inFilename()\n");
    return true;
}

bool test_outFilename() {
    //-----------------------------------------------------------
    // TODO: Task 6 - write your own test case for outFilename();
    //                use test_totalEVs() as a sample;
    //                make sure to test all components
    //-----------------------------------------------------------
    char filename[50];
    int year = 2023;

    // Test with a non-fast mode, non-quiet mode
    outFilename(filename, year);
    if (strcmp(filename, "result2023.txt") != 0) {
        printf("Test 1 failed: outFilename() with default settings\n");
        return false;
    }

    // Test with a different year and fast mode enabled
    year = 2024;
    outFilename(filename, year);
    if (strcmp(filename, "result2024_fast.txt") != 0) {
        printf("Test 2 failed: outFilename() with a different year and fast mode enabled\n");
        return false;
    }

    // Test with a different year and quiet mode enabled
    year = 2025;
    outFilename(filename, year);
    if (strcmp(filename, "result2025_quiet.txt") != 0) {
        printf("Test 3 failed: outFilename() with a different year and quiet mode enabled\n");
        return false;
    }

    // Test with a year outside the valid range
    year = 1900;
    outFilename(filename, year);
    if (strcmp(filename, "result_invalid.txt") != 0) {
        printf("Test 4 failed: outFilename() with an invalid year\n");
        return false;
    }

    printf("All tests passed: outFilename()\n");
    return true;
}

bool test_parseLine() {
    //---------------------------------------------------------
    // TODO: Task 6 - write your own test case for parseLine();
    //                use test_totalEVs() as a sample;
    //                make sure to test all components
    //---------------------------------------------------------
    State testState;
    char validLine[] = "California,CA,55,2500000";
    char invalidLine[] = "Texas,TX,38";  // Missing data
    char incompleteLine[] = "New York,NY,45,3000000,";  // Extra data

    // Test parsing a valid line
    if (!parseLine(validLine, &testState)) {
        printf("Test 1 failed: parseLine() with a valid line\n");
        return false;
    }
    if (strcmp(testState.name, "California") != 0 ||
        strcmp(testState.postalCode, "CA") != 0 ||
        testState.electoralVotes != 55 ||
        testState.popularVotes != 2500000) {
        printf("Test 1 failed: parseLine() didn't parse data correctly\n");
        return false;
    }

    // Test parsing an invalid line
    if (parseLine(invalidLine, &testState)) {
        printf("Test 2 failed: parseLine() with an invalid line\n");
        return false;
    }

    // Test parsing a line with extra data
    if (parseLine(incompleteLine, &testState)) {
        printf("Test 3 failed: parseLine() with a line containing extra data\n");
        return false;
    }

    printf("All tests passed: parseLine()\n");
    return true;
}

bool test_readElectionData() {
    //----------------------------------------------------------------
    // TODO: Task 6 - write your own test case for readElectionData();
    //                make sure to test all components
    //----------------------------------------------------------------
    State testStates[3]; // Create an array to hold the test data
    int nStates;

    // Create a temporary file with test data
    FILE* testDataFile = fopen("testData.txt", "w");
    if (testDataFile == NULL) {
        printf("Test setup failed: Unable to create test data file\n");
        return false;
    }

    fprintf(testDataFile, "California,CA,55,2500000\n");
    fprintf(testDataFile, "Texas,TX,38,2200000\n");
    fprintf(testDataFile, "New York,NY,45,2800000\n");
    fclose(testDataFile);

    // Test reading the data from the temporary file
    if (!readElectionData("testData.txt", testStates, &nStates)) {
        printf("Test failed: readElectionData() failed to read data\n");
        return false;
    }

    // Verify that the data was correctly read
    if (nStates != 3) {
        printf("Test failed: readElectionData() returned an incorrect number of states\n");
        return false;
    }

    if (strcmp(testStates[0].name, "California") != 0 ||
        strcmp(testStates[1].name, "Texas") != 0 ||
        strcmp(testStates[2].name, "New York") != 0) {
        printf("Test failed: readElectionData() didn't read state names correctly\n");
        return false;
    }

    printf("Test passed: readElectionData()\n");

    // Clean up the temporary file
    remove("testData.txt");

    return true;
}

// Define a helper function to check if two MinInfo structures are equal
bool minInfoEqual(MinInfo info1, MinInfo info2) {
    if (info1.sufficientEVs != info2.sufficientEVs) return false;
    if (info1.szSomeStates != info2.szSomeStates) return false;
    if (info1.subsetPVs != info2.subsetPVs) return false;

    for (int i = 0; i < info1.szSomeStates; i++) {
        if (strcmp(info1.someStates[i].name, info2.someStates[i].name) != 0) return false;
    }

    return true;
}

bool test_minPVsSlow() {
    //-----------------------------------------------------------------
    // TODO: Task 7 - write your own test case for minPopVoteAtLeast();
    //                make sure to test all components
    //-----------------------------------------------------------------
    return false;
}

bool test_minPVsFast() {
    //---------------------------------------------------------------------
    // TODO: Task 8 - write your own test case for minPopVoteAtLeastFast();
    //                make sure to test all components
    //---------------------------------------------------------------------
    return false; //modify this
}

int main() {
    printf("Welcome to the Popular Vote Minimizer Testing Suite!\n\n");

    printf("Testing totalEVs()...\n");
    if (test_totalEVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing totalPVs()...\n");
    if (test_totalPVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing setSettings()...\n");
    if (test_setSettings()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing inFilename()...\n");
    if (test_inFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing outFilename()...\n");
    if (test_outFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing parseLine()...\n");
    if (test_parseLine()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing readElectionData()...\n");
    if (test_readElectionData()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing minPopVoteToWin()...\n");
    if (test_minPVsSlow()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing minPopVoteToWinFast()...\n");
    if (test_minPVsFast()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing minPopVoteToWinSlow()...\n");
    if (test_minPVsSlow) {
        printf("Test passed!\n");
    } else {
        printf("Test failed.\n");
    }

    return 0;
}
