// lab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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

int** identificationVertex(int** sourseMatrix, int columnCount, int rowsCount, int firstVertexToDelete, int secondVertexToDelete) {


	int** newMatrix = NULL;
	int* firstRowToSave = NULL;
	int* secondRowToSave = NULL;

	int sizeOfNewMatrix = columnCount - 1;

	allocateMatrix(&newMatrix, sizeOfNewMatrix, sizeOfNewMatrix);


	for (int i = 0; i < rowsCount; i++)
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
	for (int i = 0; i < rowsCount; i++) {

		if (i == firstVertexToDelete || i == secondVertexToDelete) {
			continue;
		}
		secondIndex = 0;
		for (int j = 0; j < columnCount; j++)
		{
			if (j == secondVertexToDelete || j == firstVertexToDelete) {
				continue;
			}

			newMatrix[secondIndex][index] = sourseMatrix[i][j];
			newMatrix[index][secondIndex] = sourseMatrix[i][j];

			secondIndex++;
		}
		index++;
	}

	index = 0;

	for (int i = 0; i < rowsCount; i++)
	{
		if (i == firstVertexToDelete || i == secondVertexToDelete)
		{
			continue;
		}
		newMatrix[sizeOfNewMatrix - 1][index] = firstRowToSave[i];
		newMatrix[index][sizeOfNewMatrix - 1] = firstRowToSave[i];
		index++;
	}

	index = 0;

	for (int i = 0; i < rowsCount; i++)
	{
		if (i == firstVertexToDelete || i == secondVertexToDelete) {
			continue;
		}

		if (newMatrix[index][sizeOfNewMatrix - 1] == 1 || secondRowToSave[i] == 0) {
			index++;
			continue;
		}
		newMatrix[sizeOfNewMatrix - 1][index] = secondRowToSave[i];
		newMatrix[index][sizeOfNewMatrix - 1] = secondRowToSave[i];
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

int** unionOfGraphs(int** firstMatrix, int** secondMatrix, int columnCount, int rowsCount) {

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

int** intersectionGraphs(int** firstMatrix, int** secondMatrix, int columnCount, int rowsCount) {
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

int** xorGraphs(int** firstMatrix, int** secondMatrix, int columnCount, int rowsCount) {
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

void cartesianProductOfGraphs(int** sourseMatrix, int columnCount, int rowsCount) {
	int** resultMatrix = NULL;
	int sizeOfNewMatrix = columnCount * columnCount;

	allocateMatrix(&resultMatrix, sizeOfNewMatrix, sizeOfNewMatrix);

	for (int i = 0; i < sizeOfNewMatrix; i++)
	{
		
	}
	
	

}
void printListAdjacency(int** sourseMatrix, int columnCount, int rowsCount) {

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



void firstTask() {

	int** firstMatrix = NULL;
	int** secondMatrix = NULL;
	int** resultMatrix = NULL;

	int countElements = 0;

	int firstVertexToDelete = 0;
	int secondVertexToDelete = 0;

	int userInput = 0;

	printf("Введите количество элементов = ");

	scanf_s("%d", &countElements);

	printf("\n");

	printf("\tM1: \n");
	allocateMatrix(&firstMatrix, countElements, countElements);
	fillMatrixRandomElements(firstMatrix, countElements, countElements);
	printMatrix(firstMatrix, countElements, countElements);
	printf("\n");
	printListAdjacency(firstMatrix, countElements, countElements);

	printf("\n\n\n\n");

	printf("\tM2: \n");
	allocateMatrix(&secondMatrix, countElements, countElements);
	fillMatrixRandomElements(secondMatrix, countElements, countElements);
	printMatrix(secondMatrix, countElements, countElements);
	printf("\n");
	printListAdjacency(secondMatrix, countElements, countElements);


	printf("\nНомер первой удаляемой вершины = ");
	scanf_s("%d", &firstVertexToDelete);

	printf("\n");

	printf("Номер второй удаляемой вершины = ");
	scanf_s("%d", &secondVertexToDelete);

	printf("\nОтождествление вершин графа:\n");

	printf("M1:\n");

	int** identificationFirstMatrix = identificationVertex(firstMatrix, countElements, countElements, firstVertexToDelete, secondVertexToDelete);
	printMatrix(identificationFirstMatrix, countElements - 1, countElements - 1);

	printf("\nНомер первой удаляемой вершины = ");
	scanf_s("%d", &firstVertexToDelete);

	printf("\n");

	printf("Номер второй удаляемой вершины = ");
	scanf_s("%d", &secondVertexToDelete);

	printf("\nM2: \n");

	int** identificationSecondMatrix = identificationVertex(secondMatrix, countElements, countElements, firstVertexToDelete, secondVertexToDelete);
	printMatrix(identificationSecondMatrix, countElements - 1, countElements - 1);

	printf("\n\nСтягивание ребра графа:\n");

	printf("\nИндекс удаляемого ребра М1 = ");
	scanf_s("%d %d", &firstVertexToDelete, &secondVertexToDelete);
	printf("\n");

	int** EdgeContraction = identificationVertex(firstMatrix, countElements, countElements, firstVertexToDelete, secondVertexToDelete);
	printMatrix(EdgeContraction, countElements - 1, countElements - 1);

	printf("\n\nРасщепление вершины:\n");

	printf("\nИндекс расщепляемой вершины М1 = ");
	scanf_s("%d", &userInput);
	printf("\n");
	int** splitFirstMatrix = splitVertex(firstMatrix, countElements, countElements, userInput);
	printMatrix(splitFirstMatrix, countElements + 1, countElements + 1);


	printf("\n\nИндекс расщепляемой вершины М1 = ");
	scanf_s("%d", &userInput);
	printf("\n");
	int** splitSecondMatrix = splitVertex(secondMatrix, countElements, countElements, userInput);
	printMatrix(splitSecondMatrix, countElements + 1, countElements + 1);




	free(firstMatrix);
	free(secondMatrix);
	free(identificationFirstMatrix);
	free(identificationSecondMatrix);
	free(EdgeContraction);
	free(splitFirstMatrix);
	free(splitSecondMatrix);
}

void secondTask() {
	int** firstMatrix = NULL;
	int** secondMatrix = NULL;
	int** resultMatrix = NULL;

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

	printf("\n\nОбъединение графов: \n");
	int** resultunionOfMatrix = unionOfGraphs(firstMatrix, secondMatrix, countElements, countElements);
	printMatrix(resultunionOfMatrix, countElements, countElements);
	printf("\n");

	printf("\n\nПересечение графов: \n");
	int** resultIntersectionMatrix = intersectionGraphs(firstMatrix, secondMatrix, countElements, countElements);
	printMatrix(resultIntersectionMatrix, countElements, countElements);

	printf("\n");

	printf("\n\nКольевая сумма графов: \n");
	int** resultXorMatrix = xorGraphs(firstMatrix, secondMatrix, countElements, countElements);
	printMatrix(resultXorMatrix, countElements, countElements);
}

void thirdTask() {

	int** firstMatrix = NULL;
	int** secondMatrix = NULL;
	int** resultMatrix = NULL;

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
}

int main()
{
	setlocale(LC_ALL, "Rus");
	//firstTask();
	secondTask();
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
