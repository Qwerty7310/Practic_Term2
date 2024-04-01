/*****************************************************************************
 * Кафедра №304 1 курс                                                       *
 * --------------------------------------------------------------------------*
 * Project Type: Win32 Console Application                                   *
 * Project Name: Practice                                                    *
 * File Name: main.cpp                                                       *
 * Language: C++                                                             *
 * Programmer(s): Bobrov                                                     *
 * Modified by: 26/05/23                                                     *
 * Created: 15/04/23                                                         *
 * Last Revision: 11/05/23                                                   *
 * Comment(s): Практическое задание                                          *
 *****************************************************************************/

#include <iostream>
#include <fstream>
#include "functions.h"

using namespace std;

int main() {
    int amountFlights = 0; // Количество рейсов
    int amountCorrectFlights = 0;
    error errCode = {0, 0, 0}; // Код ошибки

    ifstream file(FILE_NAME);

    setlocale(LC_ALL, "RUSSIAN");
    // Проверка открытия файла
    if (!file) {
        cout << "ФАЙЛ " << FILE_NAME << " НЕ НАЙДЕН" << endl;
        system("PAUSE");
        return -1;
    }

    amountFlights = CountLinesInFile(file);
    auto *flights = new airplane[amountFlights];
    auto *sortArray = new indexItem[amountFlights];

    ReadingFlightData(file, flights, amountFlights);
    PrintArray(flights, amountFlights);

    CheckFlights(flights, sortArray, amountFlights, amountCorrectFlights);

    if (amountCorrectFlights != 0) {
        // Вывод отсортированного массива
        setlocale(LC_ALL, "RUSSIAN");
        BubbleSort(sortArray, amountCorrectFlights);
        cout << endl << "Отсортированный массив по параметру \"Номер рейса\":" << endl;
        PrintSortFlights(flights, sortArray, amountCorrectFlights);
    } else {
        cout << "Сортировка невозможна.\nОтсутствуют корректные записи." << endl;
    }

    system("PAUSE");
    return 0;
}
