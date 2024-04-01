#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

struct airplane {
    char sideNumber[20] = {}; // �������� ����� � ������� <��������� �����>-<�������������� �����>
    char flightNumber[20] = {}; // ����� �����
    char brand[20] = {}; // ����� ��
    char time[20] = {}; // ����� ����� � ����
};

struct error {
    int str; // ����� ������ �����
    int param; // ����� ���������, � ������� �������� ������
    int type; // ��� ������: 0 - �������� �����������, 1 - �������� ��������� �����������
};

struct indexItem {
    int index = -1; //
    char key[20] = {};
};

const char FILE_NAME[] = R"(C:\Users\daniil\CLionProjects\Practice_2\input_2.txt)";
const int NUMBER_STR = 1; // ����� ������, � ������� ���������� ������
const int AMOUNT_OF_DIGITS_IN_FLIGHT_NUMBER = 4; // ���������� ���� � ������ �����
const int INDEX_START_FLIGHT_NUMBER = 4; // ������ ������ �������� ����� ������ �����
const char FLIGHT_NAME[] = {char(208), char(197), char(201), char(209)};

/**
 * @brief ������ ������ �� �����
 * @param file - ���� �������� ������
 * @param flights - ������ ������
 * @param size - ������ �������
 * @return
 */
void ReadingFlightData(ifstream &file, airplane *flights, int &size);

/**
 * @brief �������� ������� ������
 * @param flights - ������ ������
 * @param sortArr - ������ ���������� ������ ��� ����������
 * @param amount - ���������� ������
 * @param correctAmount - ���������� ��������� ������� ������
 * @return
 */
void CheckFlights(airplane *flights, indexItem *sortArr, int amount, int &correctAmount);

/**
 * @brief �������� ������ �����
 * @param arr - ������ ������
 * @return 1 - ���� ������, 0 - ������ ���������
 */
int CheckFlightNumber(const char *arr);

/**
 * @brief �������� ��������� ������
 * @param arr - ������ ������
 * @return 1 - ���� ������, 0 - ������ ���������
 */
int CheckSideNumber(const char *arr);

/**
 * @brief �������� �������
 * @param arr - ������ ������
 * @return 1 - ���� ������, 0 - ������ ���������
 */
int CheckTime(const char *arr);

/**
 * @brief ��������� ���� �������� �������
 * @param arr1 - ������ �������� �������
 * @param arr2 - ������ �������� �������
 * @param index - ������ ������ ������ �������
 * @param size - ����� ������� �������
 * @return 1 - ������ �������� ������, 0 - ������ �������� ������ ��� �����
 */
int More(const char *arr1, const char *arr2, int index, int size);

/**
 * @brief ������ ��������� �������
 * @param arr - ������
 * @param size - ������ �������
 * @return
 */
void PrintArray(airplane *arr, int size);

/**
 * @brief ������ ���������������� �������
 * @param arr - ������ �������� ������
 * @param sortArr - ������ ����������
 * @param size - ���������� ���������� �������
 * @return
 */
void PrintSortFlights(airplane *arr, indexItem *sortArr, int size);

/**
 * @brief ������ ������
 * @param error - ��� ������
 * @return
 */
void PrintErr(error);

/**
 * @brief ������� ���������� �����
 * @param file - ���� �������� ������
 * @return ���������� �����
 */
int CountLinesInFile(ifstream &file);

/**
 * @brief ������� ��������
 * @param file - ���� �������� ������
 * @return
 */
void MoveCursor(ifstream &file);

/**
 * @brief ������� ��������
 * @param arr - ������ ��� ����������
 * @param size - ������ �������
 * @return
 */
void BubbleSort(indexItem *arr, int size);