//
//  main.cpp
//  lucky tickets
//
//  Created by Moore on 23/03/2018.
//  Copyright © 2018 Moore. All rights reserved.
//  Линдберг Егор, ПС-22 (Lindberg Yegor PS-22)
//  Данная программа была написана в XCode.
/*
6.3. Счастливые билеты (8). Номера автобусных билетов состоят из 2N цифр, включая
незначащие нули (1 ≤ N ≤ 500). Минимальный возможный номер состоит из 2N нулей, а
максимальный – из 2N девяток. Студент Вася ездит в университет на автобусе и коллекционирует
счастливые билеты, в которых сумма первых N цифр совпадает с суммой последних N цифр. Как и
всякий настоящий коллекционер, Вася готов пойти на все для пополнения своей коллекции.
Вместе с тем ему пока приходится учитывать свои финансовые возможности.
Каждый раз после приобретения билета Вася определяет, какое минимальное количество
билетов нужно купить еще, чтобы среди них обязательно оказался счастливый билет. Если у него
оказывается достаточно денег, он тут же покупает необходимое число билетов. Иногда он не
успевает закончить расчеты, проезжает свою остановку и опаздывает на занятия. Помогите Васе.
Ввод из файла INPUT.TXT. В первой строке находится число N. Во второй строке задан номер
первого билета Васи из 2N цифр.
Вывод в файл OUTPUT.TXT. В единственной строке вывести минимальное число следующих
билетов, необходимое для гарантированного получения счастливого билета.
*/

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int firstHalf = 1;
const int secondHalf = 2;
const int maxDigit = 9;
int halfOfTicket = 0;

int sumOfHalf(vector<int> ticket, int half)
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

void differenceOfTickets(vector<int> lucky, vector<int> initial, vector<int>& buyTickets)
{
    for (int i = (halfOfTicket * 2) - 1; i >= 0; --i)
    {
        if ((lucky[i] - initial[i]) >= 0)
           buyTickets[i] = lucky[i] - initial[i];
        else
        {
            for (int counter = i - 1; counter >= 0; --counter)
            {
                if (lucky[counter] != 0)
                {
                    --lucky[counter];
                    buyTickets[i] = lucky[i] + 10 - initial[i];
                    break;
                }
                else
                    lucky[counter] = maxDigit;
            }
        }
    }
}

int main(int argc, const char * argv[]) {

    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    
    if ((!inputFile.is_open()) || (!outputFile.is_open()))
        return 1;
    
    //read in vector:
    inputFile >> halfOfTicket;
    int fullTicket = halfOfTicket * 2;
    //cout << halfOfTicket << endl;
    vector<int> ticketNumber(fullTicket);
    vector<int> initialState(fullTicket);
    vector<int> buyAmountTickets(fullTicket);
    for (int i = 0; i < fullTicket; ++i)
        buyAmountTickets[i] = 0;
    
    char ch = '0';
    for (int i = 0; i < fullTicket; ++i)
    {
        inputFile >> ch;
        ticketNumber[i] = initialState[i] = (int)ch - 48;
    }
    
    int sumOfFirstHalf = sumOfHalf(ticketNumber, firstHalf);
    int sumOfSecondHalf = sumOfHalf(ticketNumber, secondHalf);
    
    int digitCountFirstH = fullTicket - 1; // так как вектор идет не с 1, а с 0.
    int digitCountSecH = fullTicket - 1;
    while (sumOfFirstHalf != sumOfSecondHalf)
    {
        if (sumOfFirstHalf > sumOfSecondHalf)
        {
            int diffBetweenFirstAndSecond = sumOfFirstHalf - sumOfSecondHalf;
            if (diffBetweenFirstAndSecond > maxDigit)
            {
                ticketNumber[digitCountFirstH] = maxDigit;
                --digitCountFirstH;
            }
            else
            {
                if ((diffBetweenFirstAndSecond + ticketNumber[digitCountFirstH]) <= maxDigit)
                    ticketNumber[digitCountFirstH] = ticketNumber[digitCountFirstH] + diffBetweenFirstAndSecond;
                else
                {
                    int i = digitCountFirstH;
                    while (diffBetweenFirstAndSecond != 0)
                    {
                        int difference = maxDigit - ticketNumber[i];
                        if ((diffBetweenFirstAndSecond - difference) >= 0)
                        {
                            ticketNumber[i] = ticketNumber[i] + difference;
                            diffBetweenFirstAndSecond = diffBetweenFirstAndSecond - difference;
                        }
                        else
                        {
                            ticketNumber[i] = ticketNumber[i] + diffBetweenFirstAndSecond;
                            break;
                        }
                        --i;
                    }
                }
                
            }
        }
        else if (sumOfFirstHalf < sumOfSecondHalf)
        {
            ticketNumber[digitCountSecH] = 0;
            if (ticketNumber[digitCountSecH - 1] == maxDigit)
            {
                int i = 0;
                for (i = digitCountSecH - 1; ticketNumber[i] == maxDigit; --i)
                    ticketNumber[i] = 0;
                ++ticketNumber[i];
            }
            else
                ++ticketNumber[digitCountSecH - 1];
            --digitCountSecH;
            sumOfFirstHalf = sumOfHalf(ticketNumber, firstHalf);
        }
        sumOfSecondHalf = sumOfHalf(ticketNumber, secondHalf);
    }
    /*
    //number of lucky ticket
    cout << "  lucky: ";
    for (int i = 0; i < fullTicket; ++i)
        cout << ticketNumber[i];
    cout << endl << "initial: ";
    for (int i = 0; i < fullTicket; ++i)
        cout << initialState[i];
     */
    //quantity of buying tickets
    differenceOfTickets(ticketNumber, initialState, buyAmountTickets);
    
    //output
    //cout << endl << endl;
    int counter = 0;
    while ((buyAmountTickets[counter] == 0) && (counter < fullTicket - 1))
        ++counter;
    for (int i = counter; i < fullTicket; ++i)
    {
        outputFile << buyAmountTickets[i];
        //cout << buyAmountTickets[i];
    }
    //cout << endl;
    
    inputFile.close();
    outputFile.close();
    
    return 0;
}
