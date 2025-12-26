#include <iostream>
#include <Windows.h>
#include <locale>
#include <vector>
#include <map>
#include <climits>
#include <fstream>
#include <limits>
#include <iomanip>
#include <algorithm> 
#include <string>

using namespace std;
void setup_console() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
}


void sort_bubble(vector<int>& array, int n) {
    // Если массив пустой или из одного элемента
    if (n <= 1) {
        if (n == 1) cout << array[0] << '\n';
        return;
    }

    for (int i = n - 1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            if (array[j] < array[j + 1]) {
                swap(array[j], array[j + 1]);
            }
        }

        for (int k = 0; k < n; ++k) {
            if (k == i) cout << "| ";
            cout << array[k];
            if (k < n - 1) cout << ' ';
        }
        cout << '\n';
    }
}

void task1() {
    cout << "Введите размерность массива: ";
    int n;
    cin >> n;
    cout << "Вводите элементы массива: ";
    vector<int> array;
    for (int i = 0; i < n; i++) {
        int element;
        cin >> element;
        array.push_back(element);
    }
    sort_bubble(array, n);
    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

struct Visit {
    int year;
    int month;
    int client;
    int hours;
};

bool inputInt(int& value, const string& prompt, int minVal = INT_MIN, int maxVal = INT_MAX) {
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= minVal && value <= maxVal) {
                return true;
            }
            else {
                cout << "Ошибка: значение должно быть в диапазоне[" << minVal << ", " << maxVal << "]. Попробуйте снова.\n";
            }
        }
        else {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Ошибка: введено не целое число. Попробуйте снова.\n";
        }
    }
}

void task2() {

    int K;
    if (!inputInt(K, "Введите код клиента K (10–99): ", 10, 99)) return;

    int N;
    if (!inputInt(N, "Введите количество записей N (>=0): ", 0, 1000000)) return;

    vector<Visit> visits;
    visits.reserve(N);

    for (int i = 0; i < N; ++i) {
        cout << "Запись #" << (i + 1) << ":\n";
        Visit v;

        if (!inputInt(v.year, "  Год (2000–2010): ", 2000, 2010)) return;
        if (!inputInt(v.month, "  Месяц (1–12): ", 1, 12)) return;
        if (!inputInt(v.client, "  Код клиента (10–99): ", 10, 99)) return;
        if (!inputInt(v.hours, "  Продолжительность (1–30 ч): ", 1, 30)) return;

        visits.push_back(v);
    }

    // Группировка данных по годам для клиента K
    map<int, vector<pair<int, int>>> yearData; // год → список (месяц, часы)

    for (const Visit& v : visits) {
        if (v.client == K && v.hours > 0) {
            yearData[v.year].emplace_back(v.month, v.hours);
        }
    }

    // Вывод результата
    cout << "\n--- Результаты для клиента " << K << " ---\n";
    if (yearData.empty()) {
        cout << "Нет данных\n";
        return;
    }

    bool first = true;
    for (const auto& entry : yearData) {
        int year = entry.first;
        const vector<pair<int, int> >& records = entry.second;

        if (first) {
            cout << "Год | Месяц | Продолжительность\n";
            cout << "----+-------+--------------------\n";
            first = false;
        }

        int minHours = INT_MAX;
        for (size_t j = 0; j < records.size(); ++j) {
            if (records[j].second < minHours) {
                minHours = records[j].second;
            }
        }

        int bestMonth = 0;
        for (size_t j = 0; j < records.size(); ++j) {
            int m = records[j].first;
            int h = records[j].second;
            if (h == minHours && m > bestMonth) {
                bestMonth = m;
            }
        }

        cout << year << " | " << bestMonth << "     | " << minHours << "\n";
    }
}

struct Student {
    string surname;
    int score;
};

bool shouldGoBefore(const Student& a, const Student& b) {
    if (a.score != b.score) {
        return a.score > b.score;   // по баллу — убывание
    }
    return a.surname < b.surname;   // по фамилии — возрастание
}

void cocktailSort(vector<Student>& arr) {
    if (arr.empty()) return;
    int left = 0;
    int right = arr.size() - 1;

    while (left < right) {
        bool swapped = false;

        // Слева направо
        for (int i = left; i < right; ++i) {
            if (!shouldGoBefore(arr[i], arr[i + 1])) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        right--;

        swapped = false;

        // Справа налево
        for (int i = right; i > left; --i) {
            if (!shouldGoBefore(arr[i - 1], arr[i])) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        if (!swapped) break;
        left++;
    }
}


void task3() {

    string inFilename, outFilename;

    cin.ignore(32767, '\n');

    cout << "Введите имя входного файла (список учеников): ";
    getline(cin, inFilename);

    cout << "Введите имя выходного файла (результат): ";
    getline(cin, outFilename);

    vector<Student> students;
    ifstream in(inFilename.c_str());
    if (!in.is_open()) {
        cout << "Ошибка: не удалось открыть файл \"" << inFilename << "\"\n";
        return;
    }

    string surname;
    int score;
    while (in >> surname >> score) {
        students.push_back(Student());
        students.back().surname = surname;
        students.back().score = score;
    }
    in.close();

    if (students.empty()) {
        cout << "Входной файл пуст или не содержит данных в формате \"Фамилия Балл\".\n";
        return;
    }

    cocktailSort(students);

    ofstream out(outFilename.c_str());
    if (!out.is_open()) {
        cout << "Ошибка: не удалось создать файл \"" << outFilename << "\"\n";
        return;
    }

    for (int i = 0; i < (int)students.size(); ++i) {
        out << left << setw(15) << students[i].surname << right << setw(3) << students[i].score << '\n';
    }
    out.close();

    cout << "Сортировка завершена. Результат записан в \"" << outFilename << "\"\n";
}