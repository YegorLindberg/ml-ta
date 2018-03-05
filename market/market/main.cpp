//
//  main.cpp
//  market
//
//  Created by Moore on 05/03/2018.
//  Copyright © 2018 Moore. All rights reserved.
//
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, const char * argv[]) {
    
    const string inputFileName = argv[1];
    ifstream inputFile(inputFileName);
    
    long long quantityOfSellers = 0;
    long long quantityOfBuyers = 0;
    
    //read in vector:
    inputFile >> quantityOfSellers >> quantityOfBuyers;
    vector<long long> sellers(quantityOfSellers);
    vector<long long> buyers(quantityOfBuyers);
    for (int i = 0; i < sellers.size(); ++i)
        inputFile >> sellers[i];
    for (int i = 0; i < buyers.size(); ++i)
    inputFile >> buyers[i];
    //SORT
    sort(sellers.begin(), sellers.end());
    sort(buyers.begin(), buyers.end());
    
    long long maxPrice = 0;
    long long maxAmount = 0;
    long long amountOfPurchases = 0;
    long long amountOfAgreements = 0;
    long long newPrice = 0;
    long long countSell = 0;
    long long count = 0;
    long long betweenCounter = 0;
    
    while(count < buyers.size())
    {
        while (sellers[countSell] > buyers[count])
            ++count;
        amountOfPurchases = buyers.size() - count;
        while (buyers[count] >= sellers[betweenCounter])
            ++betweenCounter;
        amountOfAgreements = betweenCounter;
        long long coef = min(amountOfPurchases, amountOfAgreements);
        if((newPrice = coef * buyers[count]) > maxPrice)
        {
            maxPrice = newPrice;
            maxAmount = buyers[count];
        }
        ++count;
    }
    cout << maxAmount << " " << maxPrice << endl;
    
    return 0;
}
