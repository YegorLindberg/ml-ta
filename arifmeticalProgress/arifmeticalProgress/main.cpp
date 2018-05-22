//  main.cpp
//  arifmeticalProgress
//  Yegor Lindberg PS-22
//  Created by Moore on 21/05/2018.
//  Copyright © 2018 Moore. All rights reserved.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ifstream inputFile("in5.txt");
    if (!inputFile.is_open())
    {
        cout << "File is not opened.\n";
        return 1;
    }

    int quantityBlocks = 0;
    inputFile >> quantityBlocks;
    vector<vector<int>> blocks(quantityBlocks);
    for (size_t i = 0; i < quantityBlocks; ++i)
    {
        int N = 0;
        inputFile >> N;
        for (size_t k = 0; k < N; ++k)
        {
            int value = 0;
            inputFile >> value;
            blocks[i].push_back(value);
        }
    }
    
    for (size_t i = 0; i < quantityBlocks; ++i)
    {
        sort(blocks[i].begin(), blocks[i].end());
        int diff = 0;
        int prevDiff = 0;
        if (blocks[i].size() > 2)
        {
            for (size_t k = 1; k < blocks[i].size(); ++k)
            {
                diff = blocks[i][k] - blocks[i][k - 1];
                if (k != 1)
                {
                    if (diff != prevDiff)
                    {
                        cout << "NO\n";
                        break;
                    }
                    if ((k == blocks[i].size() - 1) and (diff == prevDiff))
                    {
                        cout << "YES\n";
                    }
                }
                
                prevDiff = diff;
            }
        }
        else
        {
            cout << "YES\n";
        }
    }
    return 0;
}
