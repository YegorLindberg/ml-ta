//
//  main.cpp
//  Behind_Bars
//
//  Yegor Lindberg, PS-22
//  Created in XCode 9.3
/*
        11.11. За решеткой (6)
        Два бегемота, Вася и Эдик, живут в зоопарке. Каждый живет в отдельной прямоугольной
        клетке, три стены которой каменные, а четвертая образована решеткой. Через решетки бегемоты
        видят друг друга. Однажды ночью обоих мучила бессонница, и Вася предложил сыграть в
        морской бой, чтобы скоротать время. Чтобы сообщать о своем ходе как можно тише (ночь все-
        таки, все остальные звери спят), Эдик предложил найти такие положения около решеток,
        расстояние между которыми минимально.
        Ввод из файла INPUT.TXT. В единственной строке задаются через пробел восемь чисел:
        сначала описание первой решетки, затем второй. Каждая решетка задается координатами концов
        (x 1 , y 1 , x 2 , y 2 ). Все числа целые, по модулю не больше 10000.

        Вывод в файл OUTPUT.TXT. В единственной строке вывести минимальное расстояние,
        которое может быть между Васей и Эдиком, если каждый будет стоять около своей решетки.
        Расстояние должно быть выведено с тремя знаками после запятой.
 
        Пример:
        Ввод:
        0 1 0 5 1 -1 1 0
        Вывод:
        1.414
*/
//  Created by Moore on 28/04/2018.
//  Copyright © 2018 Moore. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "math.h"

using namespace std;

struct point
{
    float x = NULL;
    float y = NULL;
};

struct cut
{
    point firstPoint;
    point secondPoint;
};

const int FILE_IS_NOT_OPENED = 1;
float minLong = __FLT_MAX__;

bool CheckCrosses(cut& a, cut& b);
void CheckPerpendicular(cut& a, point C);
void CalculatesLength(point A, point B);


//-----------------------------------------------
int main()
{
    
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    if (!inputFile.is_open() || !outputFile.is_open())
    {
        cout << "Output or Input File can't be opened.\n";
        return FILE_IS_NOT_OPENED;
    }
    
    cut firstSnippet;
    cut secondSnippet;
    
    inputFile >> firstSnippet.firstPoint.x >> firstSnippet.firstPoint.y;
    inputFile >> firstSnippet.secondPoint.x >> firstSnippet.secondPoint.y;
    
    inputFile >> secondSnippet.firstPoint.x >> secondSnippet.firstPoint.y;
    inputFile >> secondSnippet.secondPoint.x >> secondSnippet.secondPoint.y;
    
    if (CheckCrosses(firstSnippet, secondSnippet))
    {
        outputFile << "0\n";
    }
    else
    {
        CheckPerpendicular(secondSnippet, firstSnippet.firstPoint);
        CheckPerpendicular(secondSnippet, firstSnippet.secondPoint);
        CheckPerpendicular(firstSnippet, secondSnippet.firstPoint);
        CheckPerpendicular(firstSnippet, secondSnippet.secondPoint);
        
        CalculatesLength(firstSnippet.firstPoint, secondSnippet.firstPoint);
        CalculatesLength(firstSnippet.firstPoint, secondSnippet.secondPoint);
        CalculatesLength(firstSnippet.secondPoint, secondSnippet.firstPoint);
        CalculatesLength(firstSnippet.secondPoint, secondSnippet.secondPoint);
    }
    
    outputFile << minLong << "\n";
    return 0;
}
//-----------------------------------------------


bool CheckCrosses(cut& a, cut& b)
{
    bool cross = false;
    float x1 = a.firstPoint.x;
    float y1 = a.firstPoint.y;
    float x2 = a.secondPoint.x;
    float y2 = a.secondPoint.y;
    
    float x3 = b.firstPoint.x;
    float y3 = b.firstPoint.y;
    float x4 = b.secondPoint.x;
    float y4 = b.secondPoint.y;
    
    float x = ((x1*y2-x2*y1)*(x4-x3)-(x3*y4-x4*y3)*(x2-x1))/((y1-y2)*(x4-x3)-(y3-y4)*(x2-x1));
    float y = ((y3-y4)*x-(x3*y4-x4*y3))/(x4-x3);

    bool first_X_Check = (((x1 <= x) && (x2 >= x)) || ((x2 <= x) && (x1 >= x)));
    bool second_X_Check = (((x3 <= x) && (x4 >= x)) || ((x4 <= x) && (x3 >= x)));
    bool first_Y_Check = (((y1 <= y) && (y2 >= y)) || ((y2 <= y) && (y1 >= y)));
    bool second_Y_Check = (((y3 <= y) && (y4 >= y)) || ((y4 <= y) && (y3 >= y)));
    
    if ((first_X_Check && first_Y_Check) || (second_X_Check && second_Y_Check))
    {
        cross = true;
    }
    return cross;
}

void CheckPerpendicular(cut& a, point C)
{
    point H; // to height
    
    float xA = a.firstPoint.x;
    float yA = a.firstPoint.y;
    float xB = a.secondPoint.x;
    float yB = a.secondPoint.y;
    
    float diffX = xB - xA;
    float diffY = yA - yB;
    
    H.x = (diffY * ((-xB) * yA + xA * yB) + diffX * ((-C.x) * diffX + C.y * diffY));
    H.x = H.x / ((-1 * (diffX * diffX)) - (diffY * diffY));
    
    H.y = (diffX * ((-xB) * yA + xA * yB) - diffY * ((-C.x) * diffX + C.y * diffY));
    H.y = H.y / ((-1 * (diffX * diffX)) - (diffY * diffY));
    
    bool first_X_Check = (((xA <= H.x) && (xB >= H.x)) || ((xB <= H.x) && (xA >= H.x)));
    bool first_Y_Check = (((yA <= H.y) && (yB >= H.y)) || ((yB <= H.y) && (yA >= H.y)));
    
    if (first_X_Check && first_Y_Check)
    {
        float line = sqrt(((H.x - C.x) * (H.x - C.x)) + ((H.y - C.y) * (H.y - C.y)));
        if (line < minLong)
        {
            minLong = line;
        }
    }
}

void CalculatesLength(point A, point B)
{
    float line = sqrt(((B.x - A.x) * (B.x - A.x)) + ((B.y - A.y) * (B.y - A.y)));
    if (line < minLong)
    {
        minLong = line;
    }
}
