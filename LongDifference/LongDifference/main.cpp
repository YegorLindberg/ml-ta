//
//  main.cpp
//  LongDifference
//
//  Created by Moore on 12.06.2018.
//  Copyright © 2018 Moore. All rights reserved.
//
/*
6.1. Длинная разность (4)
Заданы два целых положительных числа. Требуется найти их разность.
Ввод. В первых двух строках файла INPUT.TXT содержатся два целых числа M и N
(1 ≤N < M ≤ 10^200 ).
Вывод. В единственной строке выходного файла OUTPUT.TXT необходимо вывести разность
M – N.
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

vector<int> Subtraction(vector<int> reducing, vector<int> subtrahend);

const int maxDigit = 9;

int main() {
    
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    
    if ((!inputFile.is_open()) || (!outputFile.is_open())) {
        return 1;
    }
    
    string toReducing;
    string toSubtrahend;
    
    getline(inputFile, toReducing);
    getline(inputFile, toSubtrahend);
    
    if (toReducing.length() >= toSubtrahend.length()) {
        
        vector<int> reducing(toReducing.length());
        vector<int> subtrahend(toReducing.length());
        
        for (int i = 0; i < toReducing.length(); ++i) {
            reducing[i] = (int)toReducing[i] - 48;
        }
        
        size_t count_chars = 0;
        size_t diff = toReducing.length() - toSubtrahend.length();
        for (size_t i = 0; i < toReducing.length(); ++i) {
            if (diff > i) {
                subtrahend[i] = 0;
            } else {
                subtrahend[i] = (int)toSubtrahend[count_chars] - 48;
                ++count_chars;
            }
        }
        
        reducing = Subtraction(reducing, subtrahend);
        
        int count = 0;
        while (count < reducing.size()) {
            if (reducing[count] != 0) {
                break;
            }
            ++count;
        }
        if (count < reducing.size() - 1) {
            for (int i = count; i < reducing.size(); ++i) {
                //cout << dividend[i];
                outputFile << reducing[i];
            }
        } else {
            outputFile << "0\n";
        }
        
    } else {
        outputFile << toReducing;
    }
    
    inputFile.close();
    outputFile.close();
    
    cout << "work is done.\n";
    
    return 0;
}

vector<int> Subtraction(vector<int> reducing, vector<int> subtrahend) {
    int length = reducing.size();
    vector<int> result(length);
    for (int i = length - 1; i >=0; --i) {
        if ((reducing[i] - subtrahend[i]) >= 0) {
            result[i] = reducing[i] - subtrahend[i];
        } else {
            for (int counter = i - 1; counter >= 0; --counter) {
                if (reducing[counter] != 0) {
                    --reducing[counter];
                    result[i] = reducing[i] + 10 - subtrahend[i];
                    break;
                } else {
                    reducing[counter] = maxDigit;
                }
            }
        }
    }
    return result;
}

