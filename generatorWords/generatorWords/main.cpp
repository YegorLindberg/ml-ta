//
//  main.cpp
//  generatorWords
//
//  Created by Moore on 16/04/2018.
//  Copyright © 2018 Moore. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() { //int argc, const char * argv[]
    
    ifstream inputFile("input7.txt");
    ofstream outputFile("output.txt");
    if ((!inputFile.is_open()) || (!outputFile.is_open()))
        return 1;
    
    string enterWord = "enter is nothing";
    inputFile >> enterWord;
    
    string wordInDictionary = "NO";
    vector<string> dictionary;
    while (inputFile >> wordInDictionary)
        dictionary.push_back(wordInDictionary);
    
    vector<string> foundWords;
    for (size_t i = 0; i < dictionary.size(); ++i)
    {
        string separateWord = dictionary[i];
        string startWord = enterWord;
        bool compiledWord = true;
        for (size_t k = 0; k < separateWord.length(); ++k)
        {
            size_t found = startWord.find(separateWord[k]);
            if (found == string::npos)
            {
                compiledWord = false;
                break;
            }
            else
                startWord[found] = '0';
        }
        if (compiledWord == true)
            foundWords.push_back(dictionary[i]);
    }
    
    size_t amountOfChars = 0;
    size_t quantityElem = foundWords.size();
    
    size_t minElem = INT_MAX;
    for (auto elem : foundWords)
    {
        if (elem.length() < minElem)
            minElem = elem.length();
        amountOfChars = amountOfChars + (elem.length());
    }
    
    vector<string> answer;
    bool change = true;
    size_t startElem = 0;
    size_t endElem = 0;
    while (change == true)
    {
        change = false;
        for (size_t i = 0; i < quantityElem; ++i)
        {
            if (foundWords[i].length() == minElem)
            {
                answer.insert(answer.begin() + startElem, foundWords[i]);
                change = true;
                ++endElem;
            }
        }
        sort(answer.begin() + startElem, answer.begin() + endElem);
        startElem = endElem;
        ++minElem;
    }
    
    cout << amountOfChars << endl;
    outputFile << amountOfChars << endl;

    for (auto element : answer)
        outputFile << element << endl;
    
    inputFile.close();
    outputFile.close();
    
    return 0;
}
