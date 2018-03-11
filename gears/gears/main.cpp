//
//  main.cpp
//  gears
//
//  Created by Moore on 04/03/2018.
//  Copyright © 2018 Moore. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

const int FILE_IS_NOT_OPENED = 1;
const int NECESSARY_AMOUNT_OF_ARGUMENTS = 2;
const int WRONG_AMOUNT_OF_ARGUMENTS = 3;

struct pairOfGears
{
    int firstNum;
    int secondNum;
    string movingFirst;
    string movingSecond;
};

int main(int argc, const char * argv[]) {

    if(argc != NECESSARY_AMOUNT_OF_ARGUMENTS + 1)
    {
        std::cout << " You should enter 2 arguments:\n" <<
        "\treplace.exe <input file> <output file>\n";
        return WRONG_AMOUNT_OF_ARGUMENTS;
    }
    
    const string inputFileName = argv[1];
    const string outputFileName = argv[2];
    
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
    {
        cout << "The File " << inputFileName << " can't be opened.\n";
        return FILE_IS_NOT_OPENED;
    }
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open())
    {
        cout << "The File " << outputFileName << " can't be opened.\n";
        return FILE_IS_NOT_OPENED;
    }
    
    //          main code:
    
    //initializaiton
    int amountOfGears = 0;
    int amountOfPairs = 0;
    inputFile >> amountOfGears >> amountOfPairs;
    vector<string> result(amountOfGears); // запись результата для каждой шестеренки(номер шестеренки является (порядок - 1))
    vector<pairOfGears> mainPairs(amountOfPairs);
    
    for (int i = 0; i < amountOfPairs; ++i)
    {
        int firstNumber = 0;
        int secondNumber = 0;
        inputFile >> firstNumber >> secondNumber;
        pairOfGears temp;
        temp.firstNum = firstNumber;
        temp.secondNum = secondNumber;
        temp.movingFirst = temp.movingSecond = "undefined";
        mainPairs[i] = temp;
    }
    
    for (int j = 0; j < amountOfGears; ++j)
        result[j] = "immovable";
    
    mainPairs[0].movingFirst = "clockwise";
    mainPairs[0].movingSecond = "unclockwise";
    result[mainPairs[0].firstNum - 1] = "clockwise";
    result[mainPairs[0].secondNum - 1] = "unclockwise";
    mainPairs.erase(mainPairs.begin());
    
    //magic
    bool breaker = false;
    bool change = true;
    
    while (change == true)
    {
        change = false;
        for (int i = 0; i < mainPairs.size(); ++i)
        {
            if ((result[mainPairs[i].firstNum - 1] != "immovable") && (mainPairs[i].movingFirst == "undefined"))
            {
                mainPairs[i].movingFirst = result[mainPairs[i].firstNum - 1];
                change = true;
            }
            else if ((mainPairs[i].movingSecond != "undefined") && (mainPairs[i].movingFirst == "undefined"))
            {
                if (mainPairs[i].movingSecond == "clockwise")
                    mainPairs[i].movingFirst = "unclockwise";
                else
                    mainPairs[i].movingFirst = "clockwise";
                result[mainPairs[i].firstNum - 1] = mainPairs[i].movingFirst;
                change = true;
            }
            if ((result[mainPairs[i].secondNum - 1] != "immovable") && (mainPairs[i].movingSecond == "undefined"))
            {
                mainPairs[i].movingSecond = result[mainPairs[i].secondNum - 1];
                change = true;
            }
            else if ((mainPairs[i].movingFirst != "undefined") && (mainPairs[i].movingSecond == "undefined"))
            {
                if (mainPairs[i].movingFirst == "clockwise")
                    mainPairs[i].movingSecond = "unclockwise";
                else
                    mainPairs[i].movingSecond = "clockwise";
                result[mainPairs[i].secondNum - 1] = mainPairs[i].movingSecond;
                change = true;
            }
            /* //пробовал с удалением, думал, что будет быстрее, но оказалось наоборот.
            if ((mainPairs[i].movingFirst == "clockwise" && mainPairs[i].movingSecond == "unclockwise") ||
                (mainPairs[i].movingFirst == "unclockwise" && mainPairs[i].movingSecond == "clockwise"))
                mainPairs.erase(mainPairs.begin() + i);
             */
            if ((mainPairs[i].movingFirst == "clockwise" && mainPairs[i].movingSecond == "clockwise") ||
                (mainPairs[i].movingFirst == "unclockwise" && mainPairs[i].movingSecond == "unclockwise"))
            {
                breaker = true;
                change = false;
                break;
            }
        }
    }
    
    //conclusion
    if(breaker == false)
    {
        /* //только для проверки некоторых случаев:
        for (int i = 0; i < mainPairs.size(); ++i)
        {
            cout << mainPairs[i].firstNum << ":" << mainPairs[i].secondNum << " - " << mainPairs[i].movingFirst << ", " << mainPairs[i].movingSecond <<"\n";
        }
        */
        for (int i = 0; i < result.size(); ++i)
        {
            outputFile << result[i] <<"\n";
        }
    }
    else
        outputFile << "blocked\n";
    
    if (!outputFile.flush())
    {
        cout << "Failed to save data on disk\n";
        return 3;
    }
    
    inputFile.close();
    outputFile.close();

    return 0;
}
