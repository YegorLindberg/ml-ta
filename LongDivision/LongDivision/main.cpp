//
//  main.cpp
//  LongDivision
//
//  Created by Moore on 23/03/2018.
//  Copyright © 2018 Moore. All rights reserved.
//  Линдберг Егор, ПС-22 (Lindberg Yegor PS-22)
//  Данная программа была написана в XCode.
/*
 6.2
 Заданы два целых положительных числа. Требуется найти их частное и остаток от деления.
 Ввод. В первой строке файла INPUT.TXT задано делимое, во второй – делитель. Количество
 цифр делимого и делителя от 1 до 100.
 Вывод. В первой строке файла OUTPUT.TXT вывести частное, во второй строке - остаток.
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

vector<int> Subtraction(vector<int> dividend, vector<int> divider);
bool RemainingNumberGreaterThanDivisor(vector<int> dividend, vector<int> divider);

const int maxDigit = 9;

int main() {
    
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    
    if ((!inputFile.is_open()) || (!outputFile.is_open())) {
        return 1;
    }
    
    string toDividend;
    string toDivider;
    
    getline(inputFile, toDividend);
    getline(inputFile, toDivider);
    
    if (toDividend.length() >= toDivider.length()) {
        
        vector<int> dividend(toDividend.length());
        vector<int> divider(toDividend.length());
        
        for (int i = 0; i < toDividend.length(); ++i) {
            dividend[i] = (int)toDividend[i] - 48;
        }
        
        size_t count_chars = 0;
        size_t diff = toDividend.length() - toDivider.length();
        for (size_t i = 0; i < toDividend.length(); ++i) {
            if (diff > i) {
                divider[i] = 0;
            } else {
                divider[i] = (int)toDivider[count_chars] - 48;
                ++count_chars;
            }
        }
        
        size_t whole = 0;
        while (RemainingNumberGreaterThanDivisor(dividend, divider)) {
            dividend = Subtraction(dividend, divider);
            ++whole;
        }
        //cout << "whole number: " << whole << "\nremainder: ";
        outputFile << whole << '\n';
        int count = 0;
        while (count < dividend.size()) {
            if (dividend[count] != 0) {
                break;
            }
            ++count;
        }
        if (count < dividend.size() - 1) {
            for (int i = count; i < dividend.size(); ++i) {
                //cout << dividend[i];
                outputFile << dividend[i];
            }
        } else {
            outputFile << "0\n";
        }
        //cout << '\n';
    } else {
        outputFile << toDividend;
    }
    
    inputFile.close();
    outputFile.close();
    
    cout << "work is done.\n";
    
    return 0;
}


bool RemainingNumberGreaterThanDivisor(vector<int> dividend, vector<int> divider) {
    for (int i = 0; i < dividend.size(); ++i) {
        if (dividend[i] > divider[i]) {
            return true;
        } else if ((i == dividend.size() - 1) && (dividend[i] == divider[i])) {
            return true;
        }
    }
    return false;
}

vector<int> Subtraction(vector<int> dividend, vector<int> divider) {
    int length = dividend.size();
    vector<int> result(length);
    for (int i = length - 1; i >=0; --i) {
        if ((dividend[i] - divider[i]) >= 0) {
            result[i] = dividend[i] - divider[i];
        } else {
            for (int counter = i - 1; counter >= 0; --counter) {
                if (dividend[counter] != 0) {
                    --dividend[counter];
                    result[i] = dividend[i] + 10 - divider[i];
                    break;
                } else {
                    dividend[counter] = maxDigit;
                }
            }
        }
    }
    return result;
}

