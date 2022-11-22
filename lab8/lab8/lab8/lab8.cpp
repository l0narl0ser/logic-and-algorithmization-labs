// lab8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <queue>
using namespace std;


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
				sourseMatrix[i][j] = rand() & 1;
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

void breadthFirstSearch(int** sourceMatrix, int matrixSize) {
	int* visitedVertexs = NULL;

	visitedVertexs = (int*)calloc(matrixSize, sizeof(int));

	queue<int> vertexQueue;
	vertexQueue.push(0);

	visitedVertexs[0] = 1;

	while (!vertexQueue.empty())
	{
		int vertex = vertexQueue.front();

		vertexQueue.pop();

		printf("%d", vertex);

		for (int i = 0; i < matrixSize; i++)
		{
			if (sourceMatrix[vertex][i] == 1 && visitedVertexs[i] == 0) {

				vertexQueue.push(i);
				visitedVertexs[i] = 1;
			}

		}
	}
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	int** sourceMatrix = NULL;
	int matrixSize = 0;
	

	printf("Введите размер матрицы смежности = ");
	scanf_s("%d", &matrixSize);


	allocateMatrix(&sourceMatrix, matrixSize, matrixSize);
	fillMatrixRandomElements(sourceMatrix, matrixSize, matrixSize);

	printf("\nИсходная матрица смежности\n");

	printMatrix(sourceMatrix, matrixSize, matrixSize);
	printf("\n");
	breadthFirstSearch(sourceMatrix, matrixSize);
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
