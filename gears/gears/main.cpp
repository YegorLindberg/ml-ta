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
        return 1;
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

    
    vector<string> result; // запись результата пары шестеренок.
    vector<pairOfGears> mainPairs;
    bool firstEnter = true;
    int amountOfGears = 0;
    int amountOfPairs = 0;
    while (!inputFile.eof())
    {
        if(firstEnter == false)
        {
            int firstNumber = 0;
            int secondNumber = 0;
            inputFile >> firstNumber >> secondNumber;
            pairOfGears temp;
            temp.firstNum = firstNumber;
            temp.secondNum = secondNumber;
            temp.movingFirst = temp.movingSecond = "undefined";
            mainPairs.push_back(temp);
        }
        else
        {
            inputFile >> amountOfGears;
            inputFile >> amountOfPairs;
            firstEnter = false;
        }
    }
    
    while(amountOfGears + 1 != 0)
    {
        result.push_back("immovable");
        --amountOfGears;
    }
    
        //initialization
    mainPairs.erase(mainPairs.end() - 1);
    result.erase(result.end() - 1);
    result[0] = "BEGIN:";
    mainPairs[0].movingFirst = "clockwise";
    mainPairs[0].movingSecond = "unclockwise";
    result[mainPairs[0].firstNum] = "clockwise";
    result[mainPairs[0].secondNum] = "unclockwise";
    mainPairs.erase(mainPairs.begin());
    --amountOfPairs;
    
    bool breaker = false;
    bool change = true;
    
    while(change == true)
    {
        change = false;
        for (int i = 0; i < amountOfPairs; ++i)
        {
        
            //сделай для перечислений норм крч, не через циклы. Хорошая идея была же
        
            //cout << amountOfPairs << " - amount of pairs\n";
            if (((mainPairs[i].firstNum == j) && (mainPairs[i].movingFirst != result[j])) ||
                ((mainPairs[i].secondNum == j) && (mainPairs[i].movingSecond != result[j])))
            {
                change = true;
                if (mainPairs[i].firstNum == j)
                    mainPairs[i].movingFirst = result[j];
                else
                    mainPairs[i].movingSecond = result[j];
                if (((mainPairs[i].movingFirst == "clockwise") && (mainPairs[i].movingSecond == "unclockwise")) ||
                    ((mainPairs[i].movingFirst == "unclockwise") && (mainPairs[i].movingSecond == "clockwise")))
                {
                    mainPairs.erase(mainPairs.begin() + i);
                    --amountOfPairs;
                }
                else if (((mainPairs[i].movingFirst == "unclockwise") && (mainPairs[i].movingSecond == "unclockwise")) ||
                         ((mainPairs[i].movingFirst == "clockwise") && (mainPairs[i].movingSecond == "clockwise")))
                {
                    change = false;
                    breaker = true;
                    break;
                }
            }

        }
        
    }
    
    //conclusion
    if(breaker == false)
    {
        for (int i = 0; i < mainPairs.size(); ++i)
        {
            cout << mainPairs[i].firstNum << ":" << mainPairs[i].secondNum << " - " << mainPairs[i].movingFirst << ", " << mainPairs[i].movingSecond <<"\n";
        }
        for (int i = 0; i < result.size(); ++i)
        {
            cout << result[i] <<"\n";
        }
    }
    else
        cout << "blocked\n";
    
    
    
    
    // end of main code.
    
    if (!outputFile.flush())
    {
        cout << "Failed to save data on disk\n";
        return 3;
    }
    inputFile.close();
    outputFile.close();
    //cout << "work is done.\n";
    return 0;
}
