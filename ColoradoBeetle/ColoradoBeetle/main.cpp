//
//  main.cpp
//  ColoradoBeetle
//  Lindberg Yegor, PS-22
//  Created by Moore on 09/04/2018.
//  Copyright © 2018 Moore. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int N = 0;
int M = 0;
char **matrix;
int maxBushes = 0;

void FindBush(int k, int m, int& bushes, char **mtx)
{
    if (mtx[k][m] == '#')
    {
        ++bushes;
        mtx[k][m] = 'o';
        FindBush(k - 1, m, bushes, mtx); //up
        FindBush(k, m + 1, bushes, mtx); //right
        FindBush(k, m - 1, bushes, mtx); //left
        FindBush(k + 1, m, bushes, mtx); //down
        if (maxBushes < bushes)
            maxBushes = bushes;
        --bushes;
        mtx[k][m] = '#';
    }
}

void CreateMatrix(ifstream& fin)
{
    fin >> M >> N;
    //cout << "Matrix is " << M << "x" << N << endl;
    N = N + 2;
    M = M + 2;
    matrix = new char *[N];
    for (int i = 0; i < N; i++)
        matrix[i] = new char[N];
    
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (((i == 0) || (i == N - 1)) || ((j == 0) || (j == N - 1)))
                matrix[i][j] = 'o';
            else
                fin >> matrix[i][j];
        }
    }
}

int main(int argc, const char * argv[]) {
    
    string inputFileName = argv[1];
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
        return 1;
    
    CreateMatrix(inputFile);
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (matrix[i][j] == '#')
            {
                int bushes = 0;
                int k = i;
                int m = j;
                FindBush(k, m, bushes, matrix);
            }
        }
    }
    
    cout << maxBushes << endl;
    
    return 0;
}
