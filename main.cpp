/*****************************************************************************
 * ������� �304 1 ����                                                       *
 * --------------------------------------------------------------------------*
 * Project Type: Win32 Console Application                                   *
 * Project Name: Practice                                                    *
 * File Name: main.cpp                                                       *
 * Language: C++                                                             *
 * Programmer(s): Bobrov                                                     *
 * Modified by: 26/05/23                                                     *
 * Created: 15/04/23                                                         *
 * Last Revision: 11/05/23                                                   *
 * Comment(s): ������������ �������                                          *
 *****************************************************************************/

#include <iostream>
#include <fstream>
#include "functions.h"

using namespace std;

int main() {
    int amountFlights = 0; // ���������� ������
    int amountCorrectFlights = 0;
    error errCode = {0, 0, 0}; // ��� ������

    ifstream file(FILE_NAME);

    setlocale(LC_ALL, "RUSSIAN");
    // �������� �������� �����
    if (!file) {
        cout << "���� " << FILE_NAME << " �� ������" << endl;
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
        // ����� ���������������� �������
        setlocale(LC_ALL, "RUSSIAN");
        BubbleSort(sortArray, amountCorrectFlights);
        cout << endl << "��������������� ������ �� ��������� \"����� �����\":" << endl;
        PrintSortFlights(flights, sortArray, amountCorrectFlights);
    } else {
        cout << "���������� ����������.\n����������� ���������� ������." << endl;
    }

    system("PAUSE");
    return 0;
}
