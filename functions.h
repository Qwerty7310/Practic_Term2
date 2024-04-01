#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

struct airplane {
    char sideNumber[20] = {}; // Бортовой номер в формате <Заглавная буква>-<Четырехзначное число>
    char flightNumber[20] = {}; // Номер рейса
    char brand[20] = {}; // Марка ЛА
    char time[20] = {}; // Время входа в зону
};

struct error {
    int str; // Номер строки файла
    int param; // Номер параметра, в котором допущена ошибка
    int type; // Тип ошибки: 0 - параметр отсутствует, 1 - значение параметра некорректно
};

struct indexItem {
    int index = -1; //
    char key[20] = {};
};

const char FILE_NAME[] = R"(C:\Users\daniil\CLionProjects\Practice_2\input_2.txt)";
const int NUMBER_STR = 1; // Номер строки, с которой начинаются записи
const int AMOUNT_OF_DIGITS_IN_FLIGHT_NUMBER = 4; // Количество цифр в номере рейса
const int INDEX_START_FLIGHT_NUMBER = 4; // Индекс начала цифровой части номера рейса
const char FLIGHT_NAME[] = {char(208), char(197), char(201), char(209)};

/**
 * @brief Чтение данных из файла
 * @param file - файл исходных данных
 * @param flights - массив рейсов
 * @param size - размер массива
 * @return
 */
void ReadingFlightData(ifstream &file, airplane *flights, int &size);

/**
 * @brief Проверка записей рейсов
 * @param flights - массив рейсов
 * @param sortArr - массив корректных рейсов для сортировки
 * @param amount - количество рейсов
 * @param correctAmount - количество коррекных записей рейсов
 * @return
 */
void CheckFlights(airplane *flights, indexItem *sortArr, int amount, int &correctAmount);

/**
 * @brief Проверка номера рейса
 * @param arr - массив данных
 * @return 1 - есть ошибка, 0 - данные корректны
 */
int CheckFlightNumber(const char *arr);

/**
 * @brief Проверка бортового номера
 * @param arr - массив данных
 * @return 1 - есть ошибка, 0 - данные корректны
 */
int CheckSideNumber(const char *arr);

/**
 * @brief Проверка времени
 * @param arr - массив данных
 * @return 1 - есть ошибка, 0 - данные корректны
 */
int CheckTime(const char *arr);

/**
 * @brief Сравнение двух значений времени
 * @param arr1 - первое значение времени
 * @param arr2 - второе значение времени
 * @param index - индекс начала записи времени
 * @param size - длина массива времени
 * @return 1 - первое значение больше, 0 - второе значение больше или равны
 */
int More(const char *arr1, const char *arr2, int index, int size);

/**
 * @brief Печать исходного массива
 * @param arr - массив
 * @param size - размер массива
 * @return
 */
void PrintArray(airplane *arr, int size);

/**
 * @brief Печать отсортированного массива
 * @param arr - массив исходных данных
 * @param sortArr - массив сортировки
 * @param size - количество корректных записей
 * @return
 */
void PrintSortFlights(airplane *arr, indexItem *sortArr, int size);

/**
 * @brief Печать ошибки
 * @param error - код ошибки
 * @return
 */
void PrintErr(error);

/**
 * @brief Подсчет количество строк
 * @param file - файл исходных данных
 * @return количество строк
 */
int CountLinesInFile(ifstream &file);

/**
 * @brief Пропуск пробелов
 * @param file - файл исходных данных
 * @return
 */
void MoveCursor(ifstream &file);

/**
 * @brief Пропуск пробелов
 * @param arr - массив для сортировки
 * @param size - размер массива
 * @return
 */
void BubbleSort(indexItem *arr, int size);