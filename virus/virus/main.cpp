//
//  main.cpp
//  virus
//
//  Created by Moore on 30/04/2018.
//  Copyright © 2018 Moore. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N = 1;
int amountOfViruses = 0;
char **matrix;

struct point
{
    int x = 0;
    int y = 0;
};

void CreateMatrix(ifstream& fin);

int main(int argc, const char * argv[]) {
    
    ifstream inputFile("input9.txt");
    if (!inputFile.is_open())
    {
        cout << "File was not opened.\n";
        return 1;
    }
    
    CreateMatrix(inputFile);
    
    inputFile >> amountOfViruses;
    vector<point> viruses(amountOfViruses);
    for (size_t i = 0; i < amountOfViruses; ++i)
    {
        int x = 0;
        int y = 0;
        inputFile >> x >> y;
        viruses[i].x = x;
        viruses[i].y = y;
        matrix[x][y] = 'X';
    }
    
    bool change = true;
    size_t diff = 0;
    size_t counter = 0;
    while (change)
    {
        change = false;
        size_t bypass = viruses.size();
        for (size_t i = diff; i < bypass; ++i)
        {
            if (matrix[viruses[i].x - 1][viruses[i].y] == 'O')
            {
                matrix[viruses[i].x - 1][viruses[i].y] = 'X';
                viruses.push_back({viruses[i].x - 1, viruses[i].y});
                change = true;
            }
            if (matrix[viruses[i].x + 1][viruses[i].y] == 'O')
            {
                matrix[viruses[i].x + 1][viruses[i].y] = 'X';
                viruses.push_back({viruses[i].x + 1, viruses[i].y});
                change = true;
            }
            if (matrix[viruses[i].x][viruses[i].y - 1] == 'O')
            {
                matrix[viruses[i].x][viruses[i].y - 1] = 'X';
                viruses.push_back({viruses[i].x, viruses[i].y - 1});
                change = true;
            }
            if (matrix[viruses[i].x][viruses[i].y + 1] == 'O')
            {
                matrix[viruses[i].x][viruses[i].y + 1] = 'X';
                viruses.push_back({viruses[i].x, viruses[i].y + 1});
                change = true;
            }
        }
        if (change)
        {
            ++counter;
        }
        diff = bypass;
    }
    
    cout << counter << endl;
    
    return 0;
}


void CreateMatrix(ifstream& fin)
{
    fin >> N;
    N = N + 2;
    matrix = new char *[N];
    for (int i = 0; i < N; i++)
        matrix[i] = new char[N];
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (((i == 0) || (i == N - 1)) || ((j == 0) || (j == N - 1)))
                matrix[i][j] = '-';
            else
                matrix[i][j] = 'O';
        }
    }
}
