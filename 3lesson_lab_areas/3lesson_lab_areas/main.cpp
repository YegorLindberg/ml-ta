//
//  main.cpp
//  3lesson_lab_areas
//
//  Created by Moore on 19/02/2018.
//  Copyright © 2018 Moore. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;


int main(int argc, const char * argv[]) {

    vector<int> arr;
    
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    
    arr.insert(arr.begin() + 2, 0);
    arr.insert(arr.end() - 4, 9);
    
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << endl;
    }
    
    
    //
    /*
    int N = 0;
    cout << "Enter number of hectares: ";
    cin >> N;
    if ((N == 0) && (isalpha(N)))
    {
        cout << "areas from Ivan = 0.\n";
        return 1;
    }
    
    int area[N];
    area[0] = 0;
    int count;
    for (count = 1; count <= N; count++)
    {
        double number = sqrt(count);
        if (number == int(number))
        {
            area[count] = 1;
        }
        int blocks = 0;
        int sum = 0;
        for (int i = 1; sum <= N; i++)
        {
            ++blocks;
            sum = i * count;
            area[sum] = blocks;
        }
        
        //cout << "ok\n";
    }
    
    for (count = 1; count <= N; count++)
    {
        cout << area[count] << endl;
    }
    */
    return 0;
}
