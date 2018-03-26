//
//  main.cpp
//  quantityOfLeftTurns
//
//  Created by Moore on 26/03/2018.
//  Copyright © 2018 Moore. All rights reserved.
// Линдберг Егор, ПС-22

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct coords
{
    int x = 0;
    int y = 0;
};

bool leftTurn(coords firstCoords, coords secondCoords, coords thirdCoords)
{
    bool turn = false; //right turn
    coords initialVec;
    coords guideVec;
    
    initialVec.x = secondCoords.x - firstCoords.x;
    initialVec.y = secondCoords.y - firstCoords.y;
    guideVec.x = thirdCoords.x - secondCoords.x;
    guideVec.y = thirdCoords.y - secondCoords.y;
    
    int vecMultiplication = (initialVec.x * guideVec.y) - (guideVec.x * initialVec.y);
    vecMultiplication > 0 ? turn = true : turn = false;
    return turn;
}

int main(int argc, const char * argv[]) {
    
    ifstream inputFile("in4.txt");
    int points = 0;
    inputFile >> points;
    vector<coords> theWay(points);
    
    for(int i = 0; i < points; ++i)
        inputFile >> theWay[i].x >> theWay[i].y;
    
    int countLeftTurns = 0;
    for(int i = 1; i + 1 < points; ++i)
    {
        bool leftT = leftTurn(theWay[i - 1], theWay[i], theWay[i + 1]);
        if (leftT == true)
            ++countLeftTurns;
    }
    
    cout << countLeftTurns << endl;
    return 0;
}
