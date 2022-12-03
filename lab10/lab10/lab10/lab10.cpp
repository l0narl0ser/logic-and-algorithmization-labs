// lab10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <queue>
#include <vector>
using namespace std;

struct Eccentricity {
	int vertexNumber;
	int max;
};

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
				sourseMatrix[i][j] = rand() % 10;
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

Eccentricity* breadthFirstSearch(int** sourceMatrix, int matrixSize, int inputVertix) {

	int* visitedVertexs = (int*)calloc(matrixSize, sizeof(int));

	queue<int> vertexQueue;
	vertexQueue.push(inputVertix);

	for (int i = 0; i < matrixSize; i++)
	{
		visitedVertexs[i] = -1;
	}


	visitedVertexs[inputVertix] = 0;
	printf("Маршрут: ");
	while (!vertexQueue.empty())
	{
		int vertex = vertexQueue.front();

		vertexQueue.pop();

		printf("%d", vertex);

		for (int i = 0; i < matrixSize; i++)
		{
			if (sourceMatrix[vertex][i] > 0 && visitedVertexs[i] == -1) {

				vertexQueue.push(i);
				visitedVertexs[i] = visitedVertexs[vertex] + sourceMatrix[vertex][i];
			}

		}
	}

	printf("\nДистанция: ");
	for (int i = 0; i < matrixSize; i++)
	{

		printf("%d", visitedVertexs[i]);

	}

	int maxDistance = INT16_MIN;	

	for (int i = 0; i < matrixSize; i++)
	{
		if (visitedVertexs[i] > maxDistance)
		{
			maxDistance = visitedVertexs[i];
		}
	}

	Eccentricity* minmax = new Eccentricity();//(Eccentricity*)malloc(sizeof(Eccentricity));

	minmax->max = maxDistance;
	minmax->vertexNumber = inputVertix;

	
	return minmax;

}

void main()
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
	printf("\n\n\n");

	vector<Eccentricity> allEccentricity;
	for (int i = 0; i < matrixSize; i++)
	{
		Eccentricity* minMax = breadthFirstSearch(sourceMatrix, matrixSize, i);
		printf("\nЭксцентриситет вершины:%d  = %d \n",i, minMax->max);
		printf("\n\n");
		allEccentricity.push_back(*minMax);
	}

	Eccentricity diameter = allEccentricity.at(0);
	Eccentricity radius = allEccentricity.at(0);
	for (int i = 1; i < matrixSize; i++)
	{
		Eccentricity element = allEccentricity.at(i);
		if (diameter.max < element.max)
		{
			diameter = element;
		}
		if (radius.max > element.max)
		{
			radius = element;
		}
	}
	printf("Диаметр графа: %d", diameter.max);
	printf("\nРадиус графа: %d", radius.max);
	
	
	printf("\n\n");
	for (int i = 0; i < matrixSize; i++)
	{
		Eccentricity element = allEccentricity.at(i);
		if (element.max == diameter.max)
		{
			printf("\nПериферийная вершина %d", element.vertexNumber);
		}
		if (element.max == radius.max)
		{
			printf("\nЦентральная вершина %d", element.vertexNumber);
		}
	}
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
