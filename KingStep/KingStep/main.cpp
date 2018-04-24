//
//  main.cpp
//  KingStep
//
//  Created by Moore on 23/04/2018.
//  Copyright © 2018 Moore. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

int DeterminesWinner(int x, int y);

int main(int argc, const char * argv[]) {
    
    ifstream inputFile("input5.txt");
    
    int x = 0;
    int y = 0;
    int amountOfPoints = 0;
    inputFile >> amountOfPoints;
    while (amountOfPoints != 0)
    {
        inputFile >> y >> x;
        int winner = DeterminesWinner(x, y);
        cout << winner << endl;
        --amountOfPoints;
    }
    
    inputFile.close();
    
    return 0;
}

int DeterminesWinner(int x, int y)
{
    int answer = 4;
    if ((x % 2 == 0) || (y % 2 == 0) || ((x + y) % 2 != 0))
    {
        answer = 1;
    }
    else
    {
        answer = 2;
    }
    
    return answer;
}
