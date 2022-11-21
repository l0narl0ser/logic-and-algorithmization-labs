// lab6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


bool checkIsVertertexAdjacent(int** sourceMatrix, int firstVertexToDelite, int secondVertexToDelite) {
	if (sourceMatrix[firstVertexToDelite][secondVertexToDelite] == 1) {
		return true;
	}
	return false;
}

void allocateMatrix(int*** sourceMatrix, int columnCount, int rowsCount) {

	*sourceMatrix = (int**)malloc(columnCount * sizeof(int*));

	for (int i = 0; i < rowsCount; i++)
	{
		(*sourceMatrix)[i] = (int*)calloc(rowsCount, sizeof(int));
	}
}

void fillMatrixRandomElements(int** sourseMatrix, int columnCount, int rowsCount) {

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{
			if (i == j) {
				sourseMatrix[i][j] = 0;
			}
			else
			{
				sourseMatrix[i][j] = rand() % 3;// & 2
				sourseMatrix[j][i] = sourseMatrix[i][j];

			}
			//sourseMatrix[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
		}
	}
}

void printMatrix(int** sourseMatrix, int columnCount, int rowsCount) {

	for (int i = 0; i < rowsCount; i++)
	{
		printf("\n");
		for (int j = 0; j < columnCount; j++)
		{
			printf("\t%d", sourseMatrix[i][j]);
		}
	}
}

int calculateSizeGraph(int** sourseMatrix, int columnCount, int rowsCount) {

	int summer = 0;

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{
			if (sourseMatrix[i][j] != 0) {

				summer ++;
			}
		}
	}
	return summer / 2;
}

void printPowVertix(int** sourseMatrix, int columnCount, int rowsCount) {

	int summer = 0;

	for (int i = 0; i < rowsCount; i++)
	{
		summer = 0;
		for (int j = 0; j < columnCount; j++)
		{
			if (sourseMatrix[i][j] !=0)
			{
				summer++;
			}

		}
		printf("\nНомер вершины %d Степень вершины равна: %d ",i ,summer);

		if (summer == 0)
		{
			printf(" - изолированая");
		}
		if (summer == 1)
		{
			printf(" - концевая");
		}
		if (summer == columnCount - 1) {

			printf(" - доминирующая");
		}
	}

}

int**  createAdjacentMatrix(int** sourseMatrix, int columnCount, int rowsCount) {

	int** resultMatrix = NULL;

	int countEdges = calculateSizeGraph(sourseMatrix, columnCount, rowsCount);
	allocateMatrix(&resultMatrix, columnCount, countEdges);

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{
			
		}
	}
	return resultMatrix;
}

int main()
{
	setlocale(LC_ALL, "Rus");

	
	int** firstMatrix = NULL;
	int firstCount =  0;
	int sizeGraph = 0;

	srand(time(NULL));
	printf("Введите размер матрицы смежности = ");
	scanf_s("%d", &firstCount);

	printf("\tM1: \n");
	allocateMatrix(&firstMatrix, firstCount, firstCount);
	fillMatrixRandomElements(firstMatrix, firstCount, firstCount);
	printMatrix(firstMatrix, firstCount, firstCount);
	printf("\n");
	 
	sizeGraph = calculateSizeGraph(firstMatrix, firstCount, firstCount);
	printf("\n");
	printf("Размер графа: %d", sizeGraph);
	printf("\n");
	printPowVertix(firstMatrix, firstCount, firstCount);
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
