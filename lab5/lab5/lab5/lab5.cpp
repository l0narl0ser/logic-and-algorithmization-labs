// lab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "lab5.h"

void allocateMatrix(int*** sourceMatrix, int rowCount, int columnCount) {

	*sourceMatrix = (int**)malloc(rowCount * sizeof(int*));

	for (int i = 0; i < rowCount; i++)
	{
		(*sourceMatrix)[i] = (int*)calloc(columnCount, sizeof(int));
	}
}

void fillMatrixRandomElements(int** sourseMatrix, int rowsCount, int columnCount) {

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{
			if (i == j) {
				sourseMatrix[i][j] = 0;
			}
			else
			{
				if (columnCount == rowsCount) {
					sourseMatrix[i][j] = rand() & 1;
					sourseMatrix[j][i] = sourseMatrix[i][j];
				}
				else {
					sourseMatrix[i][j] = rand() & 1;
				}


			}
			//sourseMatrix[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
		}
	}
}

void printMatrix(int** sourseMatrix, int rowsCount, int columnCount) {

	for (int i = 0; i < rowsCount; i++)
	{
		printf("\n");
		for (int j = 0; j < columnCount; j++)
		{
			printf("\t%d", sourseMatrix[i][j]);
		}
	}
}

int** identificationVertex(int** sourseMatrix, int rowCount, int columnCount, int firstVertexToDelete, int secondVertexToDelete) {


	int** newMatrix = NULL;
	int* firstRowToSave = NULL;
	int* secondRowToSave = NULL;

	int countRowsOfNewMatrix = rowCount - 1;
	int countColumnsOfNewMatrix = columnCount - 1;

	allocateMatrix(&newMatrix, countRowsOfNewMatrix, countColumnsOfNewMatrix);


	for (int i = 0; i < rowCount; i++)
	{
		if (i == firstVertexToDelete)
		{
			firstRowToSave = sourseMatrix[i];
		}
		if (i == secondVertexToDelete) {

			secondRowToSave = sourseMatrix[i];
		}
	}
	int index = 0;
	int secondIndex = 0;
	for (int i = 0; i < rowCount; i++) {

		if (i == firstVertexToDelete || i == secondVertexToDelete) {
			continue;
		}
		secondIndex = 0;
		for (int j = 0; j < columnCount; j++)
		{
			if (j == secondVertexToDelete || j == firstVertexToDelete) {
				continue;
			}

			newMatrix[index][secondIndex] = sourseMatrix[i][j];

			secondIndex++;
		}
		index++;
	}

	index = 0;

	for (int i = 0; i < rowCount; i++)
	{
		if (i == firstVertexToDelete || i == secondVertexToDelete)
		{
			continue;
		}
		newMatrix[countRowsOfNewMatrix - 1][index] = firstRowToSave[i];
		newMatrix[index][countColumnsOfNewMatrix - 1] = firstRowToSave[i];
		index++;
	}

	index = 0;

	for (int i = 0; i < rowCount; i++)
	{
		if (i == firstVertexToDelete || i == secondVertexToDelete) {
			continue;
		}

		if (newMatrix[index][countColumnsOfNewMatrix - 1] == 1 || secondRowToSave[i] == 0) {
			index++;
			continue;
		}
		newMatrix[countRowsOfNewMatrix - 1][index] = secondRowToSave[i];
		newMatrix[index][countColumnsOfNewMatrix - 1] = secondRowToSave[i];
		index++;
	}
	return newMatrix;
}

int** splitVertex(int** sourseMatrix, int columnCount, int rowsCount, int splitVertex) {
	int** splitMatrix = NULL;
	int sizeOfNewMatrix = columnCount + 1;

	allocateMatrix(&splitMatrix, sizeOfNewMatrix, sizeOfNewMatrix);

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{
			splitMatrix[i][j] = sourseMatrix[i][j];
		}
	}


	int copyIndex = 0;

	for (int i = 0; i < rowsCount; i++)
	{
		if (sourseMatrix[i][splitVertex] == 1)
		{
			copyIndex = i;
			splitMatrix[i][splitVertex] = 0;
			splitMatrix[splitVertex][i] = 0;
			break;
		}
	}

	splitMatrix[sizeOfNewMatrix - 1][splitVertex] = 1;
	splitMatrix[splitVertex][sizeOfNewMatrix - 1] = 1;

	splitMatrix[copyIndex][sizeOfNewMatrix - 1] = 1;
	splitMatrix[sizeOfNewMatrix - 1][copyIndex] = 1;

	return splitMatrix;
}

int** unionOfGraphs(int** firstMatrix, int columnCount, int rowsCount, int** secondMatrix, int columnCountSecond, int rowsCountSecond) {

	int** resultMatrix = NULL;

	allocateMatrix(&resultMatrix, columnCount, rowsCount);

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < columnCount; j++) {
			if (firstMatrix[i][j] == 1 || secondMatrix[i][j] == 1)
			{
				resultMatrix[i][j] = 1;
			}
		}
	}
	return resultMatrix;
}

int** intersectionGraphs(int** firstMatrix, int columnCount, int rowsCount, int** secondMatrix, int columnCountSecond, int rowsCountSecond) {
	int** resultMatrix = NULL;

	allocateMatrix(&resultMatrix, columnCount, rowsCount);

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < columnCount; j++) {
			if (firstMatrix[i][j] == 1 && secondMatrix[i][j] == 1)
			{
				resultMatrix[i][j] = 1;
			}
		}
	}
	return resultMatrix;
}

int** xorGraphs(int** firstMatrix, int columnCount, int rowsCount, int** secondMatrix, int columnCountSecond, int rowsCountSecond) {
	int** resultMatrix = NULL;

	allocateMatrix(&resultMatrix, columnCount, rowsCount);

	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < columnCount; j++) {
			if (firstMatrix[i][j] == 1 ^ secondMatrix[i][j] == 1)
			{
				resultMatrix[i][j] = 1;
			}
			else
			{
				resultMatrix[i][j] = 0;
			}
		}
	}
	return resultMatrix;

}

int** cartesianProductOfGraphs(int** firstMatrix, int** secondMatrix, int columnCount, int rowsCount) {
	int** resultMatrix = NULL;
	int sizeOfNewMatrix = columnCount * columnCount;

	allocateMatrix(&resultMatrix, sizeOfNewMatrix, sizeOfNewMatrix);

	for (int i = 0; i < sizeOfNewMatrix; i++)
	{
		for (int j = 0; j < sizeOfNewMatrix; j++)
		{
			if (i < columnCount && j < rowsCount)
			{
				resultMatrix[i][j] = firstMatrix[i][j];
				continue;
			}
			if (i > columnCount - 1  && j > rowsCount - 1)
			{
				resultMatrix[i][j] = secondMatrix[i - columnCount - 1][j - columnCount - 1 ];
				continue;
			}
			resultMatrix[i][j] = 1;
		}

	}
	return resultMatrix;
}


void printListAdjacency(int** sourseMatrix, int rowsCount, int columnCount) {

	printf("\nСписок смежности:\n");

	for (int i = 0; i < rowsCount; i++)
	{

		for (int j = 0; j < columnCount; j++)
		{
			if (sourseMatrix[i][j] == 1)
			{
				printf("%d -> %d\n", i, j);
			}

		}
		printf("\n");
	}
	printf("\n");
}


void printMatrixView(int** firstMatrix, int firstMatrixRowsCount, int firstMatrixColumnsCount, int** secondMatrix, int secondMatrixRowsCount, int secondMatrixColumnsCount)
{
	printf("\tM1: \n");
	fillMatrixRandomElements(firstMatrix, firstMatrixRowsCount, firstMatrixColumnsCount);
	printMatrix(firstMatrix, firstMatrixRowsCount, firstMatrixColumnsCount);
	printf("\n");
	printListAdjacency(firstMatrix, firstMatrixRowsCount, firstMatrixColumnsCount);

	printf("\n\n\n\n");

	printf("\tM2: \n");
	fillMatrixRandomElements(secondMatrix, secondMatrixRowsCount, secondMatrixColumnsCount);
	printMatrix(secondMatrix, secondMatrixRowsCount, secondMatrixColumnsCount);
	printf("\n");
	printListAdjacency(secondMatrix, secondMatrixRowsCount, secondMatrixColumnsCount);
}


void workWithMatrixIdentification(int** matrix, int matrixRowsCount, int matrixColumnsCount){
	int firstVertexToDelete = 0;
	int secondVertexToDelete = 0;

	printf("\nНомер первой удаляемой вершины = ");
	scanf_s("%d", &firstVertexToDelete);
	printf("\n");
	printf("Номер второй удаляемой вершины = ");
	scanf_s("%d", &secondVertexToDelete);
	int** identificationMatrix = identificationVertex(matrix, matrixRowsCount, matrixColumnsCount, firstVertexToDelete, secondVertexToDelete);
	printMatrix(identificationMatrix, matrixRowsCount - 1, matrixColumnsCount - 1);
	free(identificationMatrix);
}

void workWithRemoveEdge(int** matrix, int matrixColumnCount, int matrixRowCount) {
	int firstVertexToDelete = 0;
	int secondVertexToDelete = 0;

	printf("\nИндекс удаляемого ребра  = ");
	scanf_s("%d %d", &firstVertexToDelete, &secondVertexToDelete);
	printf("\n");

	int** edgeContractionFirstMatrix = identificationVertex(matrix, firstVertexToDelete, secondVertexToDelete, firstVertexToDelete, secondVertexToDelete);
	printMatrix(edgeContractionFirstMatrix, matrixColumnCount - 1, matrixRowCount - 1);

}


void workWithSplitVertix(int** matrix, int matrixColumnCount, int matrixRowCount) {

	int userInputFirstMatrix = 0;

	printf("\nИндекс расщепляемой вершины  = ");
	scanf_s("%d", &userInputFirstMatrix);
	printf("\n");
	int** splitFirstMatrix = splitVertex(matrix, matrixColumnCount, matrixRowCount, userInputFirstMatrix);
	printMatrix(splitFirstMatrix, matrixColumnCount + 1, matrixRowCount + 1);
	free(splitFirstMatrix);
}

void firstTask() {

	int** firstMatrix = NULL;
	int** secondMatrix = NULL;
	int** resultMatrix = NULL;

	int firstMatrixRowsCount = 0;
	int firstMatrixColumnsCount= 0;


	int secondMatrixRowsCount = 0;
	int secondMatrixColumnsCount = 0;

	int userInputSecondMatrix = 0;

	printf("Введите количество строк для перовй матрицы смежности = ");
	scanf_s("%d", &firstMatrixRowsCount);
	printf("Введите количество столбцов для перовй матрицы смежности = ");
	scanf_s("%d", &firstMatrixColumnsCount);



	printf("Введите количество строк для второй матрицы смежности = ");
	scanf_s("%d", &secondMatrixRowsCount);
	printf("Введите количество столбцов для второй матрицы смежности = ");
	scanf_s("%d", &secondMatrixColumnsCount);


	printf("\n");
	allocateMatrix(&firstMatrix, firstMatrixRowsCount, firstMatrixColumnsCount);
	allocateMatrix(&secondMatrix, secondMatrixRowsCount, secondMatrixColumnsCount);

	printMatrixView(firstMatrix, firstMatrixRowsCount, firstMatrixColumnsCount, secondMatrix, secondMatrixRowsCount, secondMatrixColumnsCount);

	printf("\nОтождествление вершин графа M1:\n");
	workWithMatrixIdentification(firstMatrix, firstMatrixRowsCount, firstMatrixColumnsCount);
	printf("\nОтождествление вершин графа M2:\n");
	workWithMatrixIdentification(secondMatrix, secondMatrixRowsCount, secondMatrixColumnsCount);


	printf("\n\nСтягивание ребра графа M1:\n");
	workWithRemoveEdge(firstMatrix, firstMatrixRowsCount, firstMatrixColumnsCount);
	printf("\n\nИндекс удаляемого ребра М2 = ");
	workWithRemoveEdge(secondMatrix, secondMatrixRowsCount, secondMatrixColumnsCount);


	printf("\n\nРасщепление вершины для M1:\n");
	workWithSplitVertix(firstMatrix, firstMatrixRowsCount, firstMatrixColumnsCount);

	printf("\n\nРасщепление вершины для M2:\n");
	workWithSplitVertix(secondMatrix, secondMatrixRowsCount, secondMatrixColumnsCount);

	free(firstMatrix);
	free(secondMatrix);

}

void secondTask() {
	int** firstMatrix = NULL;
	int** secondMatrix = NULL;
	int** resultMatrix = NULL;

	int firstCount = 0;
	int secondCount = 0;
	int countElements = 0;

	printf("Введите количество элементов = ");

	scanf_s("%d", &firstCount);

	printf("\n");

	printf("Введите количество элементов = ");

	scanf_s("%d", &secondCount);

	printf("\n");

	printf("\tG1: \n");
	allocateMatrix(&firstMatrix, firstCount, firstCount);
	fillMatrixRandomElements(firstMatrix, firstCount, firstCount);
	printMatrix(firstMatrix, firstCount, firstCount);

	printf("\n");

	printf("\n\n\n\n");

	printf("\tG2: \n");
	allocateMatrix(&secondMatrix, secondCount, secondCount);
	fillMatrixRandomElements(secondMatrix, secondCount, secondCount);
	printMatrix(secondMatrix, secondCount, secondCount);
	printf("\n");

	printf("\n\nОбъединение графов: \n");
	int** resultunionOfMatrix = unionOfGraphs(firstMatrix, firstCount, firstCount, secondMatrix, secondCount, secondCount);
	printMatrix(resultunionOfMatrix, countElements, countElements);
	printf("\n");

	printf("\n\nПересечение графов: \n");
	int** resultIntersectionMatrix = intersectionGraphs(firstMatrix, firstCount, firstCount, secondMatrix, secondCount, secondCount);
	printMatrix(resultIntersectionMatrix, countElements, countElements);

	printf("\n");

	printf("\n\nКольевая сумма графов: \n");
	int** resultXorMatrix = xorGraphs(firstMatrix, firstCount, firstCount, secondMatrix, secondCount, secondCount);
	printMatrix(resultXorMatrix, countElements, countElements);
}

void thirdTask() {

	int** firstMatrix = NULL;
	int** secondMatrix = NULL;


	int countElements = 0;
	printf("Введите количество элементов = ");

	scanf_s("%d", &countElements);

	printf("\n");

	printf("\tG1: \n");
	allocateMatrix(&firstMatrix, countElements, countElements);
	fillMatrixRandomElements(firstMatrix, countElements, countElements);
	printMatrix(firstMatrix, countElements, countElements);

	printf("\n");

	printf("\n\n\n\n");

	printf("\tG2: \n");
	allocateMatrix(&secondMatrix, countElements, countElements);
	fillMatrixRandomElements(secondMatrix, countElements, countElements);
	printMatrix(secondMatrix, countElements, countElements);
	printf("\n");

	printf("\n\nДекартово произведение графов: \n");
	int** resultMatrix = cartesianProductOfGraphs(firstMatrix, secondMatrix, countElements, countElements);
	printMatrix(resultMatrix, countElements, countElements);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	firstTask();
	//secondTask();
	//thirdTask();
}
