// lab2.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void allocateMatrix(int*** sourceMatrix, int countElements) {

	*sourceMatrix = (int**)malloc(countElements * sizeof(int*));

	for (int i = 0; i < countElements; i++)
	{
		(*sourceMatrix)[i] = (int*)malloc(countElements * sizeof(int));
	}
}

void fillMatrixRandomElements(int** sourseMatrix, int countElements) {
	for (int i = 0; i < countElements; i++)
	{
		for (int j = 0; j < countElements; j++)
		{
			sourseMatrix[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
		}
	}
}

void freeMatrix(int** sourseMatrix, int countElements) {

	for (int i = 0; i < countElements; i++)
	{
		free(sourseMatrix[i]);
	}

	free(sourseMatrix);
}

int main()
{

	clock_t start, end; // объявляем переменные для определения времени выполнения

	const int maxCountElements = 200;

	int** firstMatrix = NULL;
	int** secondMatrix = NULL;
	int** resultMatrix = NULL;

	start = clock();

	srand(time(NULL)); // инициализируем параметры генератора случайных чисел

	allocateMatrix(&firstMatrix, maxCountElements);

	fillMatrixRandomElements(firstMatrix, maxCountElements);

	srand(time(NULL)); // инициализируем параметры генератора случайных чисел

	allocateMatrix(&secondMatrix, maxCountElements);

	fillMatrixRandomElements(secondMatrix, maxCountElements);

	allocateMatrix(&resultMatrix, maxCountElements);

	for (int i = 0; i < maxCountElements; i++)
	{
		for (int j = 0; j < maxCountElements; j++)
		{
			int sumElem = 0;

			for (int r = 0; r < maxCountElements; r++)
			{
				sumElem = sumElem + firstMatrix[i][r] * secondMatrix[r][j];

				resultMatrix[i][j] = sumElem;
			}
		}
	}

	end = clock();
	double diff = (end - start) / CLOCKS_PER_SEC;

	printf("time: %lf", diff);

	freeMatrix(firstMatrix, maxCountElements);

	freeMatrix(secondMatrix, maxCountElements);

	freeMatrix(resultMatrix, maxCountElements);

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
