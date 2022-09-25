// lab2.2qsort.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void* x1, const void* x2)   // функция сравнения элементов массива
{
    return (*(int*)x1 - *(int*)x2);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

int main()
{
    clock_t start, end;
    const int maxCountElements = 20000;
    int* sourseArray, index = 0;


    //srand(time(NULL));

    sourseArray = (int*)calloc(maxCountElements, sizeof(int));

    for (index = 0; index < maxCountElements; index++)
    {
        //sourseArray[index] = rand() % 100;
        // 
        //sourseArray[index] = index;
        // 
        //sourseArray[index] = -index;

    /* if (index < (maxCountElements / 2)) {

            sourseArray[index] = index;
        }
        else
        {
            sourseArray[index] = -index;
        }
  */
       
    }

    start = clock();

    qsort(sourseArray, maxCountElements, sizeof(int), compare);

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
