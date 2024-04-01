#include "functions.h"

void ReadingFlightData(ifstream &file, airplane *flights, int &amount) {

    airplane flight = {};
    for (int i = 0; i < amount; i++) {
        flight = {};

        // Чтение бортового номера
        MoveCursor(file);
        if (file.eof()) break;
        file >> flight.sideNumber;

        // Чтение номера рейса
        MoveCursor(file);
        if (file.peek() != '\n' && file.peek() != ' ') {
            file >> flight.flightNumber;
        };

        // Чтение марки ЛА
        MoveCursor(file);
        if (file.peek() != '\n' && file.peek() != ' ') {
            file >> flight.brand;
        };

        // Чтение времени входа в зону
        MoveCursor(file);
        if (file.peek() != '\n' && file.peek() != ' ') {
            file >> flight.time;
        }

        flights[i] = flight;

        file.seekg(1, ios::cur);
        while (file.peek() == '\n') {
            amount -= 1;
            file.seekg(1, ios::cur);
        }
    }


}

void CheckFlights(airplane *flights, indexItem *sortArray, int amount, int &amountCorrectFlights) {

    cout << "Список ошибок:" << endl;

    bool foundError = false;
    bool foundErrorInStr = false;
    indexItem str = {};
    int indexSort = 0;

    for (int i = 0; i < amount; i++) {

        foundErrorInStr = false;
        str = {};

        // Проверка бортового номера
        if (CheckSideNumber(flights[i].sideNumber)) {
            PrintErr({i + NUMBER_STR, 1, 1});
            foundError = true;
            foundErrorInStr = true;
        }

        // Проверка номера рейса
        if (flights[i].flightNumber[0] != '\0') {
            if (CheckFlightNumber(flights[i].flightNumber)) {
                PrintErr({i + NUMBER_STR, 2, 1});
                foundError = true;
                foundErrorInStr = true;
            }
        } else {
            PrintErr({i, 2, 0});
            foundError = true;
            foundErrorInStr = true;
        }

        // Проверка марки ЛА
        if (flights[i].brand[0] == '\0') {
            PrintErr({i + NUMBER_STR, 3, 0});
            foundError = true;
            foundErrorInStr = true;
        }

        // Проверка времени входа в зону
        if (flights[i].time[0] != '\0') {
            if (CheckTime(flights[i].time)) {
                PrintErr({i + NUMBER_STR, 4, 1});
                foundError = true;
                foundErrorInStr = true;
            }
        } else {
            PrintErr({i + NUMBER_STR, 4, 0});
            foundError = true;
            foundErrorInStr = true;
        }

        if (!foundErrorInStr) {
            str.index = i;
            for (int j = 0; flights[i].flightNumber[j] != '\0'; j++) {
                str.key[j] = flights[i].flightNumber[j];
            }
            sortArray[indexSort] = str;
            indexSort++;
        }
    }

    if (!foundError) {
        cout << "ОШИБКИ НЕ ОБНАРУЖЕНЫ";
    }

    amountCorrectFlights = indexSort;
    cout << endl;
}


int CheckFlightNumber(const char *arr) {

    int i;

    for (i = 0; i < sizeof(FLIGHT_NAME); i++) {
        if (arr[i] != FLIGHT_NAME[i]) return 1;
    }

    for (i = INDEX_START_FLIGHT_NUMBER; i < AMOUNT_OF_DIGITS_IN_FLIGHT_NUMBER + INDEX_START_FLIGHT_NUMBER; i++) {
        if (arr[i] < '0' | arr[i] > '9') return 1;
    }
    i++;
    if (arr[i] != '\0') return 1;

    return 0;
}

int CheckSideNumber(const char *arr) {

    if ((int(arr[0]) > -33) | (int(arr[0]) < -64)) return 1;
    if (arr[1] != '-') return 1;
    for (int i = 2; i < 6; i++) {
        if (arr[i] < '0' | arr[i] > '9') return 1;
    }
    if (arr[6] != '\0') return 1;

    return 0;
}

int CheckTime(const char *arr) {

    if (arr[0] > '2' || arr[0] < '0') return 1;
    if (arr[1] > '9' || arr[1] < '0') return 1;
    if ((arr[0] == '2') && (arr[1] > '3')) return 1;
    if (arr[2] != ':') return 1;
    if (arr[3] < '0' || arr[3] > '5') return 1;
    if (arr[4] < '0' || arr[4] > '9') return 1;

    if (arr[5] != '\0') return 1;

    return 0;
}

int More(const char *arr1, const char *arr2, int index, int size) {
    for (int i = index; i < index + size; i++) {
        if (arr1[i] > arr2[i]) return 1;
        if (arr1[i] < arr2[i]) return 0;
    }

    return 0;
}

void PrintArray(airplane *arr, int size) {
    setlocale(LC_ALL, "RUSSIAN");
    cout << endl << "Open file " << FILE_NAME << ":" << endl << "***************************************************************" << endl;
    for (int i = 0; i < size; i++) {
        cout << i << ")\t" << arr[i].sideNumber << "   \t" << arr[i].flightNumber << "   \t" << arr[i].brand << "  \t"
             << arr[i].time << endl;
    }
    cout << "***************************************************************" << endl << endl;
}

void PrintSortFlights(airplane *arr, indexItem *sortArr, int amount) {
    int index;
    setlocale(LC_ALL, "C");

    // Первая строка "шапки" таблицы
    cout << char(218) << setfill(char(196)) << setw(17)
         << char(194) << setfill(char(196)) << setw(17)
         << char(194) << setfill(char(196)) << setw(17)
         << char(194) << setfill(char(196)) << setw(16)
         << char(191) << endl;

    // Вторая строка  "шапки" таблицы
    cout << setfill(' ') << char(179) << setw(16);
    setlocale(LC_ALL, "RUSSIAN");
    cout << "Бортовой номер " << setfill(' '); //7
    setlocale(LC_ALL, "C");
    cout << char(179) << setw(16);
    setlocale(LC_ALL, "RUSSIAN");
    cout << "Номер рейса  " << setfill(' ');  //7
    setlocale(LC_ALL, "C");
    cout << char(179) << setw(16);
    setlocale(LC_ALL, "RUSSIAN");
    cout << "Марка ЛА    " << setfill(' ');  //9
    setlocale(LC_ALL, "C");
    cout << char(179) << setw(15);
    setlocale(LC_ALL, "RUSSIAN");
    cout << "Время     " << setfill(' '); //9
    setlocale(LC_ALL, "C");
    cout << char(179) << endl;

    // Третья строка  "шапки" таблицы
    cout << char(195) << setfill(char(196)) << setw(17)
         << char(197) << setfill(char(196)) << setw(17)
         << char(197) << setw(17)
         << char(197) << setw(16) << char(180) << endl;

    for (int i = 0; i < amount; i++) {
        index = sortArr[i].index;
        cout << char(179);
        setlocale(LC_ALL, "RUSSIAN");
        cout << setfill(' ') << setw(11) << arr[index].sideNumber << "     ";
        setlocale(LC_ALL, "C");
        cout << char(179);
        setlocale(LC_ALL, "RUSSIAN");
        cout << setfill(' ') << setw(12) << arr[index].flightNumber << "    ";
        setlocale(LC_ALL, "C");
        cout << char(179);
        setlocale(LC_ALL, "RUSSIAN");
        cout << setfill(' ') << setw(12) << arr[index].brand << "    ";
        setlocale(LC_ALL, "C");
        cout << char(179);
        setlocale(LC_ALL, "RUSSIAN");
        cout << setfill(' ') << setw(10) << arr[index].time << "     ";

        setlocale(LC_ALL, "C");
        cout << char(179) << endl;
        if (i == amount - 1) {
            // Последняя строка таблицы
            cout << char(192) << setfill(char(196)) << setw(17)
                 << char(193) << setfill(char(196)) << setw(17)
                 << char(193) << setfill(char(196)) << setw(17)
                 << char(193) << setfill(char(196)) << setw(16)
                 << char(217) << endl;
        } else {
            // Между строками таблицы
            cout << char(195) << setfill(char(196)) << setw(17)
                 << char(197) << setfill(char(196)) << setw(17)
                 << char(197) << setw(17)
                 << char(197) << setw(16) << char(180) << endl;
        }
    }
}

void PrintErr(error code) {
    if (code.str) {
        cout << "В строке " << code.str - NUMBER_STR << " параметр ";
        switch (code.param) {
            case 1:
                cout << "\"Бортовой номер\"";
                break;
            case 2:
                cout << "\"Номер рейса\"";
                break;
            case 3:
                cout << "\"Марка ЛА\"\t";
                break;
            case 4:
                cout << "\"Время\"\t";
                break;
            default:
                cout << "НЕПРЕДВИДЕННАЯ ОШИБКА" << endl;
        }

        switch (code.type) {
            case 0:
                if (code.param != 4) {
                    cout << "\tи остальные отсутствуют" << endl;
                } else {
                    cout << "\tне найден" << endl;
                }
//                if (code.param == 1) exit(9);
                break;
            case 1:
                cout << "\tне корректен" << endl;
                break;
            case 2:
                cout << "\tне корректен: количество символов не равно 7" << endl;
                break;
        }
    }
}

int CountLinesInFile(ifstream &file) {
    int count = 1;
    char c;
    for (int i = 0; !file.eof(); i++) {
        c = file.get();
        if (c == '\n') count++;
    }
    file.clear();
    file.seekg(0, ios::beg);
    return count;
}

void MoveCursor(ifstream &file) {
    while (file.peek() == ' ') {
        file.seekg(1, ios::cur);
    }
}

void BubbleSort(indexItem *arr, int size) {
    bool flag = false;

    for (int i = 0; i < size; i++) {
        flag = false;
        for (int j = 0; j < size - 1; j++) {
            if (More(arr[j].key, arr[j + 1].key, INDEX_START_FLIGHT_NUMBER, AMOUNT_OF_DIGITS_IN_FLIGHT_NUMBER)) {
                indexItem tmp = arr[j]; // создали дополнительную переменную
                arr[j] = arr[j + 1]; // меняем местами
                arr[j + 1] = tmp; // значения элементов
                flag = true;
            }
        }
        if (!flag) break;
    }
}