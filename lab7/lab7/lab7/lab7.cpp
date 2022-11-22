// lab7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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


void depthFirstTraversal(int** sourceMatrix, int matrixSize, int* visitedVertex, int vertex) {
	visitedVertex[vertex] = 1;
	printf("%d", vertex);

	for (int i = 0; i < matrixSize; i++)
	{
		//в текущей вершине есть связь И вершина не посещена
		if (sourceMatrix[vertex][i] == 1 && visitedVertex[i] == 0) {
			
			depthFirstTraversal(sourceMatrix, matrixSize, visitedVertex, i);
		}
	}
}

void main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	int** sourceMatrix = NULL;
	int matrixSize = 0;
	int* visitedVertexs = NULL;

	printf("Введите размер матрицы смежности = ");
	scanf_s("%d", &matrixSize);

	visitedVertexs = (int*)calloc(matrixSize, sizeof(int));


	allocateMatrix(&sourceMatrix, matrixSize, matrixSize);
	fillMatrixRandomElements(sourceMatrix, matrixSize, matrixSize);

	printf("\nИсходная матрица смежности\n");

	printMatrix(sourceMatrix, matrixSize, matrixSize);
	printf("\n");

	depthFirstTraversal(sourceMatrix, matrixSize, visitedVertexs, 0);


}