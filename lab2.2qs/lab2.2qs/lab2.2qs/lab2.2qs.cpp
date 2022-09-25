// lab2.2qs.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
    int i, j;
    int x, y;
    i = left; j = right;

    /* выбор компаранда */
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}


int main()
{
    clock_t start, end;
    const int maxCountElements = 20000;
;
    int* sourseArray, index = 0;


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

    qs(sourseArray, 0, (maxCountElements-1));

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
