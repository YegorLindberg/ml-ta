//
//  main.cpp
//  test_gears
//
//  Created by Moore on 11/03/2018.
//  Copyright © 2018 Moore. All rights reserved.
//

#include <iostream>
#include <fstream>

const int FILE_IS_NOT_OPENED = 1;
const int NECESSARY_AMOUNT_OF_ARGUMENTS = 1;
const int WRONG_AMOUNT_OF_ARGUMENTS = 2;

using namespace std;

int main(int argc, const char * argv[]) {
    
    if (argc != NECESSARY_AMOUNT_OF_ARGUMENTS + 1)
    {
        std::cout << " You should enter 1 argument:\n" <<
        "\ttest.exe <output file>\n";
        return WRONG_AMOUNT_OF_ARGUMENTS;
    }
    
    const string outputFileName = argv[1];

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open())
    {
        cout << "The File " << outputFileName << " can't be opened.\n";
        return FILE_IS_NOT_OPENED;
    }
    
    outputFile << 10000 << " " << 10000 << endl;
    for (int i = 1; i < 10000; ++i)
    {
        outputFile << i << " " << i+1 << endl;
    }
    
    if (!outputFile.flush())
    {
        cout << "Failed to save data on disk\n";
        return 3;
    }
    
    outputFile.close();
    return 0;
}
