// lab2.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <iomanip>

void shellSort(int* items, int count) {
    register int i, j, gap, k;
    char x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
            {
                items[j + gap] = items[j];

                items[j + gap] = x;
            }
        }
    }
}


int main()
{
    clock_t start, end;
    const int maxCountElements = 20000;
    int *sourseArray, index = 0;
  
   
    //srand(time(NULL));

    sourseArray = (int*)calloc(maxCountElements, sizeof(int));

    for (index = 0; index < maxCountElements; index++)
    {
        //sourseArray[index] = rand()%100; //случайное заполнение

        //sourseArray[index] = index; //монотонно возрастающая

        //sourseArray[index] = -index; // монотонно убывающая

        //printf("%-3d", sourseArray[index]);

        if (index < (maxCountElements / 2)) {

            sourseArray[index] = index;
        }
        else
        {
            sourseArray[index] = -index;
        }

    }
    start = clock();

    shellSort(sourseArray, maxCountElements);

    end = clock();

    double diff = (end - start);

    printf(" time: %lf", diff);

    free(sourseArray);
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
