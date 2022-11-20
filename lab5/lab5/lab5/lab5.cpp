// lab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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

int** identificationVertex(int** sourseMatrix, int columnCount, int rowsCount, int firstVertexToDelete, int secondVertexToDelete, bool isContraction) {


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

	if (!isContraction && checkIsVertertexAdjacent(sourseMatrix, firstVertexToDelete, secondVertexToDelete)) {
		newMatrix[sizeOfNewMatrix - 1][sizeOfNewMatrix - 1] = 1;
	}

	return newMatrix;
}
//
//Из этого определения следует, что расщеплением одной и той же
//вершины из одного графа можно, вообще говоря, получить несколько разных новых графов.
//1) окружение N(v) вершины v произвольным способом разбивается на два подмножества N1 и N2;

int** splitVertex(int** sourseMatrix, int columnCount, int rowsCount, int splitVertex) {
	int** splitMatrix = NULL;
	int sizeOfNewMatrix = columnCount + 1;

	allocateMatrix(&splitMatrix, sizeOfNewMatrix, sizeOfNewMatrix);

	//копируем матрицу в новую
	for (int i = 0; i < rowsCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{
			splitMatrix[i][j] = sourseMatrix[i][j];
		}
	}


	int copyIndex = 0;
	//Ищем первую свзяь и переносим ее на новую вершину. Из строки которую расщипояем удаялем эту связь
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

	//Связываем две вершины появившиеся
	splitMatrix[sizeOfNewMatrix - 1][splitVertex] = 1;
	splitMatrix[splitVertex][sizeOfNewMatrix - 1] = 1;

	splitMatrix[copyIndex][sizeOfNewMatrix - 1] = 1;
	splitMatrix[sizeOfNewMatrix - 1][copyIndex] = 1;

	return splitMatrix;
}

int** disjunctionGraphs(int** firstMatrix,  int** secondMatrix, int maxSize) {

	int** resultMatrix = NULL;

	allocateMatrix(&resultMatrix, maxSize, maxSize);

	for (int i = 0; i < maxSize; i++)
	{
		for (int j = 0; j < maxSize; j++) {
			if (firstMatrix[i][j] == 1 || secondMatrix[i][j] == 1)
			{
				resultMatrix[i][j] = 1;
			}
		}
	}
	return resultMatrix;
}

int** conjunctionGraphs(int** firstMatrix, int** secondMatrix, int maxSize) {
	int** resultMatrix = NULL;

	allocateMatrix(&resultMatrix, maxSize, maxSize);

	for (int i = 0; i < maxSize; i++)
	{
		for (int j = 0; j < maxSize; j++) {
			if (firstMatrix[i][j] == 1 && secondMatrix[i][j] == 1)
			{
				resultMatrix[i][j] = 1;
			}
		}
	}
	return resultMatrix;
}

int** xorGraphs(int** firstMatrix, int** secondMatrix, int maxSize) {
	int** resultMatrix = NULL;

	allocateMatrix(&resultMatrix, maxSize, maxSize);

	for (int i = 0; i < maxSize; i++)
	{
		for (int j = 0; j < maxSize; j++) {
			if ( (firstMatrix[i][j] == 1) ^ (secondMatrix[i][j] == 1))
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
	int sizeOfNewMatrix = columnCount * rowsCount;

	allocateMatrix(&resultMatrix, sizeOfNewMatrix, sizeOfNewMatrix);
	int w = 0;
	int z = 0;

	for (int i = 0; i < columnCount; i++)
	{
		for (int k = 0; k < columnCount; k++)
		{
			z++;
			for (int j = 0; j < columnCount; j++)
			{
				for (int l = 0; l < columnCount; l++)
				{
					w++;

					if (i == j)
					{
						resultMatrix[z][sizeOfNewMatrix] = secondMatrix[k][l];
					}
					if (k == l)
					{
						resultMatrix[sizeOfNewMatrix][w] = firstMatrix[i][j];
					}
				}
			}
		}
		
	}

//	int firstIndex = 0;
//	int secondIndex = 0;
//
//
//	int firstHalf = 0;
//	int secondHalf = 0;
//	for (int i = 0; i < sizeOfNewMatrix; i++)
//	{
//		firstIndex++;
//
//		for (int j = 0; j < sizeOfNewMatrix; j++)
//		{
//			firstHalf++;
//			if (i == j) {
//				resultMatrix[i][j] = 0;
//				continue;
//			}
//			if (j <= rowsCount) {
//				resultMatrix
//			}
//		}
//	}
//
	return resultMatrix;
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

void printMatrixAndAdjacency(int** sourceMatrix, int rowCount, int columnCount) {
	printf("\nМатрица смежности \n");
	printMatrix(sourceMatrix, rowCount, columnCount);

	printListAdjacency(sourceMatrix, rowCount, columnCount);
}

void firstTask() {

	int** firstMatrix = NULL;
	int** secondMatrix = NULL;
	int** resultMatrix = NULL;

	int firstCount = 0;
	int secondCount = 0;

	int firstVertexToDelete = 0;
	int secondVertexToDelete = 0;

	int userInputFirstMatrix = 0;
	int userInputSecondMatrix = 0;

	printf("Введите количество первой матрицы смежности = ");

	scanf_s("%d", &firstCount);

	printf("Введите количество второй матрицы смежности = ");

	scanf_s("%d", &secondCount);

	printf("\n");

	printf("\tM1: \n");
	allocateMatrix(&firstMatrix, firstCount, firstCount);
	fillMatrixRandomElements(firstMatrix, firstCount, firstCount);
	printMatrix(firstMatrix, firstCount, firstCount);
	printf("\n");
	printListAdjacency(firstMatrix, firstCount, firstCount);

	printf("\n\n\n\n");

	printf("\tM2: \n");
	allocateMatrix(&secondMatrix, secondCount, secondCount);
	fillMatrixRandomElements(secondMatrix, secondCount, secondCount);
	printMatrix(secondMatrix, secondCount, secondCount);
	printf("\n");
	printListAdjacency(secondMatrix, secondCount, secondCount);


	printf("\nНомер первой удаляемой вершины = ");
	scanf_s("%d", &firstVertexToDelete);

	printf("\n");

	printf("Номер второй удаляемой вершины = ");
	scanf_s("%d", &secondVertexToDelete);

	printf("\nОтождествление вершин графа:\n");

	printf("M1:\n");

	int** identificationFirstMatrix = identificationVertex(firstMatrix, firstCount, firstCount, firstVertexToDelete, secondVertexToDelete, false);
	printf(" после отождествления вершин\n");
	printMatrixAndAdjacency(identificationFirstMatrix, firstCount - 1, firstCount - 1);

	printf("\nНомер первой удаляемой вершины = ");
	scanf_s("%d", &firstVertexToDelete);

	printf("\n");

	printf("Номер второй удаляемой вершины = ");
	scanf_s("%d", &secondVertexToDelete);

	printf("\nM2: \n");

	int** identificationSecondMatrix = identificationVertex(secondMatrix, secondCount, secondCount, firstVertexToDelete, secondVertexToDelete, false);
	printf(" после отождествления вершин\n");
	printMatrixAndAdjacency(identificationSecondMatrix, secondCount - 1, secondCount - 1);
	bool isInputDone = false;
	while (!isInputDone)
	{
		printf("\n\nСтягивание ребра графа:\n");

		printf("\nИндекс удаляемого ребра М1 = ");
		scanf_s("%d %d", &firstVertexToDelete, &secondVertexToDelete);
		printf("\n");

		if (checkIsVertertexAdjacent(firstMatrix, firstVertexToDelete, secondVertexToDelete)) {
			int** EdgeContractionFirstMatrix = identificationVertex(firstMatrix, firstCount, firstCount, firstVertexToDelete, secondVertexToDelete, true);
			printMatrixAndAdjacency(EdgeContractionFirstMatrix, firstCount - 1, firstCount - 1);
			isInputDone = true;
			free(EdgeContractionFirstMatrix);
		}
		else {
			printf("\nВершины не смежны\n");
			isInputDone = false;
		}
	}
	isInputDone = false;
	while (!isInputDone) {
		printf("\n\nИндекс удаляемого ребра М2 = ");
		scanf_s("%d %d", &firstVertexToDelete, &secondVertexToDelete);
		printf("\n");


		if (checkIsVertertexAdjacent(secondMatrix, firstVertexToDelete, secondVertexToDelete)) {
			int** EdgeContractionSecondMatrix = identificationVertex(secondMatrix, secondCount, secondCount, firstVertexToDelete, secondVertexToDelete, true);
			printMatrixAndAdjacency(EdgeContractionSecondMatrix, secondCount - 1, secondCount - 1);
			isInputDone = true;
			free(EdgeContractionSecondMatrix);
		}
		else {
			printf("\nВершины не смежны\n");
			isInputDone = false;
		}
	}





	printf("\n\nРасщепление вершины:\n");

	printf("\nИндекс расщепляемой вершины М1 = ");
	scanf_s("%d", &userInputFirstMatrix);
	printf("\n");
	int** splitFirstMatrix = splitVertex(firstMatrix, firstCount, firstCount, userInputFirstMatrix);
	printMatrixAndAdjacency(splitFirstMatrix, firstCount + 1, firstCount + 1);


	printf("\n\nИндекс расщепляемой вершины М2 = ");
	scanf_s("%d", &userInputSecondMatrix);
	printf("\n");
	int** splitSecondMatrix = splitVertex(secondMatrix, secondCount, secondCount, userInputSecondMatrix);
	printMatrixAndAdjacency(splitSecondMatrix, secondCount + 1, secondCount + 1);




	free(firstMatrix);
	free(secondMatrix);
	free(identificationFirstMatrix);
	free(identificationSecondMatrix);
	

	free(splitFirstMatrix);
	free(splitSecondMatrix);
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

	int maxMatrixSize = 0;


	if (firstCount > secondCount) {
		maxMatrixSize = firstCount;
	}
	else {
		maxMatrixSize = secondCount;
	}



	printf("\tG1: \n");
	allocateMatrix(&firstMatrix, maxMatrixSize, maxMatrixSize);
	fillMatrixRandomElements(firstMatrix, firstCount, firstCount);
	printMatrix(firstMatrix, firstCount, firstCount);

	printf("\n");

	printf("\n\n\n\n");

	printf("\tG2: \n");
	allocateMatrix(&secondMatrix, maxMatrixSize, maxMatrixSize);
	fillMatrixRandomElements(secondMatrix, secondCount, secondCount);
	printMatrix(secondMatrix, secondCount, secondCount);
	printf("\n");

	printf("\n\nОбъединение графов: \n");
	int** resultunionOfMatrix = disjunctionGraphs(firstMatrix, secondMatrix, maxMatrixSize);
	printMatrix(resultunionOfMatrix, maxMatrixSize, maxMatrixSize);
	printf("\n");

	printf("\n\nПересечение графов: \n");
	int** resultIntersectionMatrix = conjunctionGraphs(firstMatrix, secondMatrix, maxMatrixSize);
	printMatrix(resultIntersectionMatrix, maxMatrixSize, maxMatrixSize);

	printf("\n");

	printf("\n\nКольцевая сумма графов: \n");
	int** resultXorMatrix = xorGraphs(firstMatrix, secondMatrix, maxMatrixSize);
	printMatrix(resultXorMatrix, maxMatrixSize, maxMatrixSize);
}

void thirdTask() {

	int** firstMatrix = NULL;
	int** secondMatrix = NULL;

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

	printf("\n\nДекартово произведение графов: \n");
	int** resultMatrix = cartesianProductOfGraphs(firstMatrix, secondMatrix, firstCount, secondCount);
	printMatrix(resultMatrix, countElements * secondCount, countElements * secondCount);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	//firstTask();
	//secondTask();
	//thirdTask();
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
