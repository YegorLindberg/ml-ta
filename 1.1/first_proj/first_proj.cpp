/*
1.1 Покраска лабиринта.(5)
-Лабиринт представляет собой квадрат, ×состоящий из N × N сегментов. Каждый из сегментов
может быть либо пустым, либо заполненным монолитной каменной стеной.Гарантируется, что
левый верхний и правый нижний сегменты пусты.Лабиринт обнесён сверху, снизу, слева и справа
стенами, оставляющими свободными только левый верхний и правый нижний углы.Директор
лабиринта решил покрасить стены лабиринта, видимые изнутри(см.рисунок).Помогите ему
рассчитать количество краски, необходимой для этого.
-Ввод из файла INPUT.TXT. В первой строке находится число N, затем идут N строк по N
символов: точка обозначает пустой сегмент, решётка - сегмент со стеной.
-Вывод в файл OUTPUT.TXT. Вывести одно число - площадь видимой части внутренних стен
лабиринта в квадратных метрах.
-Ограничения: 3 <= N <= 33, размер сегмента 3 × 3 м, высота стен 3 м, время 1 с.

Выполнил: Егор Линдберг, ПС-22.

IDE: Microsoft Visual Studio Community Edition 2017.
*/

#include "stdafx.h"
using namespace std;

int N = 3;
char **matrix;

int QuantityOfWalls(int i, int j, int& quantity)
{
	if (matrix[i][j] == '.')
	{
		matrix[i][j] = 'o';
		QuantityOfWalls(i - 1, j, quantity); //up
		QuantityOfWalls(i, j + 1, quantity); //right
		QuantityOfWalls(i, j - 1, quantity); //left
		QuantityOfWalls(i + 1, j, quantity); //down
	}
	else if (matrix[i][j] == '#')
		quantity++;
	return quantity;
}

int CreateMatrix(ifstream &fin)
{
	int amount = 0;
	fin >> N;
	cout << "Matrix is " << N << "x" << N << endl;
	N = N + 2;
	matrix = new char *[N];
	for (int i = 0; i < N; i++)
		matrix[i] = new char[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			if (((i == 0) || (i == N - 1)) || ((j == 0) || (j == N - 1)))
				matrix[i][j] = '#';
			else
				fin >> matrix[i][j];
		}
	int firstQuantity = 0;
	int secondQuantity = 0;
	amount = QuantityOfWalls(1, 1, firstQuantity) + QuantityOfWalls(N - 2, N - 2, secondQuantity);
	return amount;
}

int main()
{
	ofstream fout;
	fout.open("output.txt");

	ifstream fin;
	fin.open("input.txt");
	
	int amountOfPaint = CreateMatrix(fin);	

	for (int k = 0; k < N; k++) {
		for (int t = 0; t < N; t++)
		{
			cout << matrix[k][t];
		}
		cout << endl;
	}

	amountOfPaint = (amountOfPaint - 4) * 9;

	cout << amountOfPaint << endl;
	fout << amountOfPaint << endl;
    return 0;
}
