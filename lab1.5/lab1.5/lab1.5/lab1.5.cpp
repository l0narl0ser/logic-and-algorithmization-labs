// lab1.5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <Windows.h>
#include "StudentStruct.h"
#include "printStudent.h"


int main()
{
	int i;

	const int maxCountStudents = 3;

	setlocale(LC_ALL, "Rus");

	SetConsoleCP(1251);

	SetConsoleOutputCP(1251);
	struct student stud[maxCountStudents];
	
	

	for (i = 0; i < maxCountStudents; i++)
	{
		printf("Введите фамилию студента: ");

		scanf("%s", stud[i].lastName);
		printf("Введите имя студента: ");

		scanf("%s", stud[i].firstName);
		printf("Введите факультет студента: ");

		scanf("%s", stud[i].faculty);
		printf("Введите номер зачеткой книжки студента: ");

		scanf("%s", stud[i].studentSerialNumber);
	}


	for (i = 0; i < maxCountStudents; i++)
	{
		printStudent(stud[i]);
	}
	char targetString[20];

	printf("Введите ключевое слово: ");

	scanf("%s", targetString);
	
	for ( i = 0; i < maxCountStudents; i++)
	{


		if (strcmp(targetString, stud[i].lastName) == 0) {

			printf("Найден студента :\n");

			printStudent(stud[i]);

		}

		if (strcmp(targetString, stud[i].firstName) == 0) {

			printf("Найден студента :\n");

			printStudent(stud[i]);

		}

		if (strcmp(targetString, stud[i].faculty) == 0) {

			printf("Найден студента :\n");

			printStudent(stud[i]);

		}

		if (strcmp(targetString, stud[i].studentSerialNumber) == 0) {

			printf("Найден студента :\n");

			printStudent(stud[i]);
			
		}

	}

	getchar();

	getchar();

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
