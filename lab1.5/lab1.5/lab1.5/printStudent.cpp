#include <iostream>
#include <locale.h>
#include <Windows.h>
#include "StudentStruct.h"

void printStudent(student targetStudent) {

	printf("Студент %s %s обучается на факультете %s, номер зачётной книжки %s\n", targetStudent.lastName, targetStudent.firstName, targetStudent.faculty, targetStudent.studentSerialNumber);

}