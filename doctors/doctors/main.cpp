//
//  main.cpp
//  doctors
//
//  Created by Moore on 02/04/2018.
//  Copyright © 2018 Moore. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct tops
{
    int amountPredecessor;
    vector<int> predecessors;
    bool enter = false;
};

int main() {
    
    int quantityDoctors = 0;

    ifstream inputFile("input.0.txt");
    ofstream outputFile("output.txt");
    
    if ((!inputFile.is_open()) || (!outputFile.is_open()))
        return 1;
    
    inputFile >> quantityDoctors;
    vector<int> answer;
    vector<tops> accordings(quantityDoctors);
    vector<bool> available(quantityDoctors + 1);
    for (int i = 0; i < quantityDoctors + 1; ++i)
        available[i] = false;
    
    for (int i = 0; i < quantityDoctors; ++i)
    {
        inputFile >> accordings[i].amountPredecessor;
        if (accordings[i].amountPredecessor == 0)
        {
            available[accordings[i].amountPredecessor] = true;
            accordings[i].predecessors.push_back(0);
        }
        else
        {
            int value = 0;
            for (int j = 0; j < accordings[i].amountPredecessor; ++j)
            {
                inputFile >> value;
                accordings[i].predecessors.push_back(value);
            }
        }
    }
    
    bool change = true;
    while (change == true)
    {
        change = false;
        for (int i = 0; i < accordings.size(); ++i)
        {
            if ((accordings[i].amountPredecessor == 0) && (accordings[i].enter != true))
            {
                available[i + 1] = true;
                answer.push_back(i + 1);
                accordings[i].enter = true;
                change = true;
            }
            else
            {
                int diff = 0;
                for (int k = 0; k < accordings[i].amountPredecessor; ++k)
                {
                    if (available[accordings[i].predecessors[k]] == true)
                    {
                        accordings[i].predecessors[k] = 0;
                        change = true;
                        ++diff;
                    }
                }
                accordings[i].amountPredecessor = accordings[i].amountPredecessor - diff;
            }
        }
    }
    
    if (answer.size() != quantityDoctors)
        cout << "NO\n";
    else
    {
        cout << "YES\n";
        for (int i = 0; i < answer.size(); ++i)
            cout << answer[i] << endl;
    }
    
    cout << endl;
    return 0;
}
