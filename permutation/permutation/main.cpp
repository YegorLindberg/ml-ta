//
//  main.cpp
//  permutation
//
//  Created by Moore on 19/03/2018.
//  Copyright © 2018 Moore. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

int main() {
    
    vector<int> inputLine;
    int value = 0;
    cout << "Enter numbers: ";
    while((cin >> value))
        inputLine.push_back(value);
    
    bool permutation = true;
    bool print = true;
    size_t size = inputLine.size();
    cout << endl << size << endl;
    int i = 0;
    while((i < 5) and (permutation != false))
    {
        permutation = false;
        /*if (inputLine[size] < inputLine[size - 1])
        {
            iter_swap(inputLine.begin() + (size), inputLine.begin() + (size - 1));
            permutation = true;
        }*/
        if (inputLine[size] > inputLine[size - 1])
        {
            iter_swap(inputLine.begin() + size, inputLine.begin() + (size - 1));
            permutation = true;
        }
        else if (inputLine[size] > inputLine[size - 2])
        {
            iter_swap(inputLine.begin() + (size), inputLine.begin() + (size - 2));
            permutation = true;
        }
        else if (inputLine[size - 1] > inputLine[size - 2])
        {
            iter_swap(inputLine.begin() + (size - 1), inputLine.begin() + (size - 2));
            permutation = true;
        }
        else
        {
            if ((size - 1) > 3)
            {
                size = size - 1;
                permutation = true;
                print = false;
                --i;
            }
        }
        //output
        if (print == true)
        {
            for(int i = 0; i < inputLine.size(); ++i)
                cout << inputLine[i] << " ";
            cout << endl;
        }
        else
            print = true;
        ++i;
    }
    
    return 0;
}
