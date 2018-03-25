//
//  main.cpp
//  lucky tickets
//
//  Created by Moore on 23/03/2018.
//  Copyright © 2018 Moore. All rights reserved.
//
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int firstHalf = 1;
const int secondHalf = 2;

int sumOfHalf(vector<int> ticket, int halfOfTicket, int half)
{
    int sum = 0;
    if (half == firstHalf)
    {
        for (int i = 0; i < halfOfTicket; ++i)
            sum = sum + ticket[i];
    }
    else if (half == secondHalf)
    {
        for (int i = halfOfTicket; i < (halfOfTicket * 2); ++i)
            sum = sum + ticket[i];
    }
    return sum;
}

int main(int argc, const char * argv[]) {
    
    if (argc < 3)
    {
        cout << "You must enter 2 argument with program:\n" <<
        "\tluckyTickets.exe <input file> <output file>";
    }
    const string inputFileName = argv[1];
    ifstream inputFile(inputFileName);
    
    const string outputFileName = argv[2];
    ifstream outputFile(outputFileName);
    
    int halfOfTicket = 0;
    
    //read in vector:
    inputFile >> halfOfTicket;
    int fullTicket = halfOfTicket * 2;
    cout << fullTicket << endl;
    vector<int> ticketNumber(fullTicket);
    char ch = '0';
    for (int i = 0; i < fullTicket; ++i)
    {
        inputFile >> ch;
        ticketNumber[i] = (int)ch - 48;
    }
    
    int sumOfFirstHalf = sumOfHalf(ticketNumber, halfOfTicket, firstHalf);
    int sumOfSecondHalf = sumOfHalf(ticketNumber, halfOfTicket, secondHalf);
    
    const int maxDigit = 9;
    vector<int> buyAmountTickets;
    unsigned long long buyManyTickets = 0;
    int digitCountFirstH = fullTicket - 1; // так как вектор идет не с 1, а с 0.
    int digitCountSecH = fullTicket - 1;
    int multiplierFirstH = 1; // множитель.
    int multiplierSecH = 1;
    //int exitCount = 0;
    while ((sumOfFirstHalf != sumOfSecondHalf)) // && (exitCount != 100)
    {
        if (sumOfFirstHalf > sumOfSecondHalf)
        {
            int digit = ticketNumber[digitCountFirstH];
            int diffBetweenFirstAndSecond = sumOfFirstHalf - sumOfSecondHalf;
            if (diffBetweenFirstAndSecond > maxDigit)
            {
                ticketNumber[digitCountFirstH] = maxDigit;
                buyManyTickets = buyManyTickets + (maxDigit - digit) * multiplierFirstH;
                multiplierFirstH = multiplierFirstH * 10;
                --digitCountFirstH;
            }
            else
            {
                if ((diffBetweenFirstAndSecond + ticketNumber[digitCountFirstH]) <= maxDigit)
                {
                    ticketNumber[digitCountFirstH] = ticketNumber[digitCountFirstH] + diffBetweenFirstAndSecond;
                    buyManyTickets = buyManyTickets + diffBetweenFirstAndSecond * multiplierFirstH;
                }
                else
                {
                    ++ticketNumber[digitCountFirstH - 1];
                    ticketNumber[digitCountFirstH] = ticketNumber[digitCountFirstH] + diffBetweenFirstAndSecond - maxDigit - 1;
                    buyManyTickets = buyManyTickets + diffBetweenFirstAndSecond * multiplierFirstH;
                }
            }
        }
        else if (sumOfFirstHalf < sumOfSecondHalf)
        {
            int digit = ticketNumber[digitCountSecH];
            ticketNumber[digitCountSecH] = 0;
            if (ticketNumber[digitCountSecH - 1] == 9)
            {
                int i = 0;
                for (i = digitCountSecH - 1; ticketNumber[i] == 9; --i)
                    ticketNumber[i] = 0;
                ++ticketNumber[i];
            }
            else
                ++ticketNumber[digitCountSecH - 1];
            buyManyTickets = buyManyTickets + (maxDigit + 1 - digit) * multiplierSecH;
            multiplierSecH = multiplierSecH * 10;
            --digitCountSecH;
            sumOfFirstHalf = sumOfHalf(ticketNumber, halfOfTicket, firstHalf);

        }
        //++exitCount;
        sumOfSecondHalf = sumOfHalf(ticketNumber, halfOfTicket, secondHalf);
    }
    
    //output
    for (int i = 0; i < fullTicket; ++i)
        cout << ticketNumber[i];
    
    cout << endl << buyManyTickets << " - buy this amount of tickets" << endl;
    
    return 0;
}
