#include <iostream>
#include <limits>
#include "Header.h"
#include <Windows.h>
#include <locale>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

void setup_console() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
}

// Структура для хранения информации о клиенте
struct ClientRecord {
    int month;      // Номер месяца
    int year;       // Год
    int clientCode; // Код клиента
    int duration;   // Продолжительность занятий (в часах)
};

// Функция для проверки и получения корректного значения
int getValidInput(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= minVal && value <= maxVal) {
                return value;
            }
            else {
                cout << "Ошибка: значение должно быть в диапазоне [" << minVal << ", " << maxVal << "]. Попробуйте снова.\n";
            }
        }
        else {
            cout << "Ошибка: введите целое число. Попробуйте снова.\n";
            cin.clear(); // Очищаем флаг ошибки
            cin.ignore(10000, '\n'); // <-- заменили numeric_limits<streamsize>::max() на 10000
        }
    }
}


void runFitnessCenterTask() {
    cout << "\n=== Задача: Фитнес-центр ===\n";

    int N = getValidInput("Введите количество записей: ", 1, 2147483647);

    ClientRecord record;
    ClientRecord maxRecord = { 0, 0, 0, -1 }; // Инициализируем минимальным значением для продолжительности

    for (int i = 0; i < N; i++) {
        cout << "\nЗапись #" << (i + 1) << ":" << endl;
        record.month = getValidInput("Введите месяц (1-12): ", 1, 12);
        record.year = getValidInput("Введите год (2000-2010): ", 2000, 2010);
        record.clientCode = getValidInput("Введите код клиента (10-99): ", 10, 99);
        record.duration = getValidInput("Введите продолжительность занятий (1-30 часов): ", 1, 30);

        // Проверяем, является ли текущая запись "лучшей"
        // 1. Продолжительность больше
        if (record.duration > maxRecord.duration) {
            maxRecord = record;
        }
        // 2. Продолжительность равна, но дата позже
        else if (record.duration == maxRecord.duration) {
            // Сравниваем даты: сначала по году, потом по месяцу
            if ((record.year > maxRecord.year) ||
                (record.year == maxRecord.year && record.month > maxRecord.month)) {
                maxRecord = record;
            }
        }
    }

    // Выводим результат
    cout << "\n=== Результат ===" << endl;
    cout << "Максимальная продолжительность занятий: " << maxRecord.duration << " часов" << endl;
    cout << "Год: " << maxRecord.year << endl;
    cout << "Месяц: " << maxRecord.month << endl;
}

union StudentData {
    short readingSpeed;     // для 1-го класса (слов в минуту)
    float testScore;        // для 4-го класса (баллы от 1 до 100)
    short mathScore;        // для 2-го и 3-го классов (от 1 до 10)
};

// Структура для ученика
struct Student {
    string lastName;
    string firstName;
    int grade;              // 1, 2, 3 или 4
    StudentData data;       // зависит от класса
};

// Функция для ввода данных одного ученика
Student inputStudent() {
    Student s;
    cout << "Введите фамилию: ";
    cin >> s.lastName;
    cout << "Введите имя: ";
    cin >> s.firstName;
    cout << "Введите класс (1-4): ";

    int grade;
    while (true) {
        cin >> grade;
        if (grade >= 1 && grade <= 4) {
            s.grade = grade;
            break;
        }
        else {
            cout << "Ошибка: класс должен быть от 1 до 4. Повторите ввод: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    switch (s.grade) {
    case 1:
        cout << "Введите скорость чтения (слов в минуту): ";
        while (true) {
            if (cin >> s.data.readingSpeed) {
                if (s.data.readingSpeed >= 0) {
                    break;
                }
                else {
                    cout << "Ошибка: скорость чтения не может быть отрицательной. Повторите ввод: ";
                }
            }
            else {
                cout << "Ошибка: введите целое число. Повторите ввод: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        break;
    case 2:
    case 3:
        cout << "Введите оценку по математике (1-10): ";
        while (true) {
            if (cin >> s.data.mathScore) {
                if (s.data.mathScore >= 1 && s.data.mathScore <= 10) {
                    break;
                }
                else {
                    cout << "Ошибка: оценка должна быть от 1 до 10. Повторите ввод: ";
                }
            }
            else {
                cout << "Ошибка: введите целое число. Повторите ввод: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        break;
    case 4:
        cout << "Введите баллы муниципального теста (1-100): ";
        while (true) {
            if (cin >> s.data.testScore) {
                if (s.data.testScore >= 1.0f && s.data.testScore <= 100.0f) {
                    break;
                }
                else {
                    cout << "Ошибка: баллы должны быть от 1 до 100. Повторите ввод: ";
                }
            }
            else {
                cout << "Ошибка: введите число. Повторите ввод: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        break;
    }
    return s;
}

void runStudentTask() {
    cout << "\n=== Задача: Ученики младшей школы ===\n";

    int N;
    cout << "Введите количество учеников: ";
    while (true) {
        if (cin >> N && N > 0) {
            break;
        }
        else {
            cout << "Ошибка: введите положительное число. Повторите: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    vector<Student> students(N);
    for (int i = 0; i < N; i++) {
        cout << "\n--- Ввод данных для ученика #" << (i + 1) << " ---\n";
        students[i] = inputStudent();
    }

    // Сохранение в файл
    ofstream file("students.txt");
    if (!file.is_open()) {
        cout << "Ошибка: не удалось создать файл students.txt\n";
        return;
    }

    // Заголовок таблицы
    file << left << setw(15) << "Фамилия" << setw(15) << "Имя" << setw(8) << "Класс" << setw(20) << "Данные" << "\n";
    file << string(60, '-') << "\n";

    for (const auto& s : students) {
        file << left << setw(15) << s.lastName << setw(15) << s.firstName << setw(8) << s.grade;

        switch (s.grade) {
        case 1:
            file << setw(20) << s.data.readingSpeed << "\n";
            break;
        case 2:
        case 3:
            file << setw(20) << s.data.mathScore << "\n";
            break;
        case 4:
            file << setw(20) << fixed << setprecision(2) << s.data.testScore << "\n";
            break;
        }
    }
    file.close();
    cout << "\nДанные успешно сохранены в файл students.txt\n";

    // Чтение и вывод содержимого файла на экран
    ifstream read_file("students.txt");
    if (!read_file.is_open()) {
        cout << "Ошибка: не удалось открыть файл для чтения\n";
        return;
    }

    cout << "\n=== Содержимое файла students.txt ===\n";
    string line;
    while (getline(read_file, line)) {
        cout << line << "\n";
    }
    read_file.close();
}