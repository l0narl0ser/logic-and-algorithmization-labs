// lab3.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <Windows.h>


struct node
{
	int priority;
	char inf[256];  // полезная информация
	struct node* next; // ссылка на следующий элемент 
};

struct node* head = NULL, * last = NULL, * f = NULL; // указатели на первый и последний элементы списка
int dlinna = 0;

void addElementToStack(node* element) { //последний зашёл - первый вышел
	
	if (head == NULL)
	{
		head = element;
		return;
	}
	else
	{
		element->next = head;
		head = element;
	}
}

node* getElementFromStack() {
	node* item;
	if (head == NULL)
	{
		return NULL;
	}
	else
	{
		item = head;
		head = head->next;
		return item;
	}
}
//https://stackoverflow.com/questions/22179169/delete-struct-from-stack-memory

void addElementToQueueWithPriority(node* element) { //приоритетная очередь 
	node* item = head;
	node* previuseElem = NULL;

	while (item != NULL) //вставка между элементами
	{

		if (item->priority < element->priority) {

			if (previuseElem == NULL) {
				element->next = item;
				head = element;				
			}
			else {
				struct node* temp = previuseElem->next;
				previuseElem->next = element;
				element->next = item;
			}
			return;
		}
		else {
			previuseElem = item; 
			item = item->next;			
		}
	}

	if (head == NULL) {
		head = element;
	}
	else {
		previuseElem->next = element;
	}

}


void addElementToQueue(node* element) { //последний пришел - последний вышел 
	node* item = head;
	
	if (head == NULL)
	{
		head = element;
		return;
	}

	while (item->next != NULL) 
	{
		item = item->next;
	}
	item->next = element;

}

node* getElementFromQueue() {
	node* item;
	if (head == NULL)
	{
		return NULL;
	}
	else
	{
		item = head;
		head = head->next;
		return item;
	}

}


// Функции добавления элемента, просмотра списка
void spstore(void), printQueue(void), del(char* name);

void WorkWithPriorityQueue();

char find_el[256];
struct node* findElementInGeneralStruct(char* name); // функция нахождения элемента
struct node* createStruct(); // функция создания элемента



 node* createStruct()
{
	struct node* p = NULL;
	char s[256];
	int prioprity = 0;

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите название объекта: \n");   // вводим данные
	scanf("%s", s);
	printf("Введите приоритет: \n");   // вводим данные
	scanf("%d", &prioprity);

	p->priority = prioprity;

	if (*s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->inf, s);

	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}

/* Последовательное добавление в список элемента (в конец)*/
void spstore(void)
{
	struct node* p = NULL;
	p = createStruct();
	if (head == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
	{
		head = p;
		last = p;
	}
	else if (head != NULL && p != NULL) // список уже есть, то вставляем в конец
	{
		last->next = p;
		last = p;
	}
	return;
}


/* Просмотр содержимого списка. */
void printQueue()
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc != NULL)
	{
		printf("Имя - %s, Приоритет = %d \n", struc->inf, struc->priority);
		struc = struc->next;
	}
}




/* Поиск элемента по содержимому. */
struct node* findElementInGeneralStruct(char* name)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			return struc;
		}
		struc = struc->next;
	}
	printf("Элемент не найден\n");
	return NULL;
}

/* Удаление элемента по содержимому. */
void del(char* name)
{
	struct node* struc = head; // указатель, проходящий по списку установлен на начало списка
	struct node* prev = NULL;// указатель на предшествующий удаляемому элемент
	int flag = 0;      // индикатор отсутствия удаляемого элемента в списке

	if (head == NULL) // если голова списка равна NULL, то список пуст
	{
		printf("Список пуст\n");
		return;
	}

	if (strcmp(name, struc->inf) == 0) // если удаляемый элемент - первый
	{
		flag = 1;
		head = struc->next; // установливаем голову на следующий элемент
		free(struc);  // удаляем первый элемент
		struc = head; // устанавливаем указатель для продолжения поиска
	}
	else
	{
		prev = struc;
		struc = struc->next;
	}

	while (struc) // проход по списку и поиск удаляемого элемента
	{
		if (strcmp(name, struc->inf) == 0) // если нашли, то
		{
			flag = 1;         // выставляем индикатор
			if (struc->next)  // если найденный элемент не последний в списке
			{
				prev->next = struc->next; // меняем указатели
				free(struc);		    // удаляем  элемент
				struc = prev->next; // устанавливаем указатель для продолжения поиска
			}
			else			// если найденный элемент последний в списке
			{
				prev->next = NULL; // обнуляем указатель предшествующего элемента
				free(struc);	// удаляем  элемент
				return;
			}
		}
		else
		{
			prev = struc; // устанавливаем указатели для продолжения поиска
			struc = struc->next;
		}
	}

	if (flag == 0)				// если флаг = 0, значит нужный элемент не найден
	{
		printf("Элемент не найден\n");
		return;
	}
}


void clearAllNodes() {

	if (head == NULL) {
		return;
	}

	node* element = head;
	while (element != NULL)
	{
		node* nodeTodDelite = element;
		element = element->next;
		free(nodeTodDelite);
	}

	head = NULL;
}

void WorkWithPriorityQueue()
{
	int userInput = 1;

	printf("Работа с приоритетной очередью\n");

	while (userInput > 0)
	{
		node* inputElement = createStruct();
		addElementToQueueWithPriority(inputElement);
		printf("Введите 0, чтобы закончить \t или 1 , чтобы продолжить\n");
		scanf("%d", &userInput);
	}
	printQueue();

	char inputString[250];
	printf("\nВведите название искомого объекта\n");
	scanf("%s", inputString);

	node* findedElement = findElementInGeneralStruct(inputString);

	if (findedElement != NULL) {
		printf("\nЭлемент найден name = %s priority = %d\n", findedElement->inf, findedElement->priority);
	}
	clearAllNodes();
}


void WorkWithQueue() {
	int userInput = 1;

	printf("Работа с обычыной очередью\n");
	while (userInput > 0)
	{
		node* inputElement = createStruct();
		addElementToQueue(inputElement);
		printf("Введите 0, чтобы закончить или 1 , чтобы продолжить\n");
		scanf("%d", &userInput);
	}

	char inputString[250];
	printf("\nВведите название искомого объекта\n");
	scanf("%s", inputString);

	node* findedElement = findElementInGeneralStruct(inputString);

	if (findedElement != NULL) {
		printf("\nЭлемент найден name = %s priority = %d\n", findedElement->inf, findedElement->priority);
	}

	printf("\nВсе  элементы\n");
	node* elementToPrint = head;
	while (elementToPrint != NULL)
	{
		elementToPrint = getElementFromQueue();
		if (elementToPrint == NULL) {
			return;
		}
		printf("Имя = %s \n", elementToPrint->inf);
	}

}

void WorkWithStack() {
	int userInput = 1;
	node* elementToPrint = head;
	printf("Работа с стеком\n");

	while (userInput > 0)
	{
		node* inputElement = createStruct();
		addElementToStack(inputElement);
		printf("Введите 0, чтобы закончить \t или 1 , чтобы продолжить\n");
		scanf("%d", &userInput);
	}

	char inputString[250];
	printf("\nВведите название искомого объекта\n");
	scanf("%s", inputString);

	node* findedElement = findElementInGeneralStruct(inputString);

	if (findedElement != NULL) {
		printf("\nЭлемент найден name = %s priority = %d\n", findedElement->inf, findedElement->priority);
	}

	printf("\nВсе  элементы\n");


	elementToPrint = head;
	while (elementToPrint != NULL)
	{
		elementToPrint = getElementFromStack();
		if (elementToPrint == NULL) {
			return;
		}
		printf("Имя = %s \n", elementToPrint->inf);
	}
}

void main() {
	setlocale(LC_ALL, "Rus");
	
	WorkWithPriorityQueue();
	WorkWithQueue();
	WorkWithStack();

}
