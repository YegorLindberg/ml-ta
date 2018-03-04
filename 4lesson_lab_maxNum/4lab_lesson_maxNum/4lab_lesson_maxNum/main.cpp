//  main.cpp
//  3lesson_lab_areas
//  Created by Moore on 19/02/2018.
//  Copyright © 2018 Moore. All rights reserved.

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() { //int argc, const char * argv[]
    ifstream fin("input6.txt");
    
    int N = 2;
    fin >> N;
    
    vector<char> arr;
    char ch = ' ';
    while (fin >> ch)
        arr.push_back(ch);
    
    ch = '9';
    int position = 0;
    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i] <= ch)
        {
            if (arr[i] < ch)
            {
                ch = arr[i];
                position = i + 1;
            }
        }
        else
            break;
    }
    cout << endl << position << endl;
    return 0;
}

