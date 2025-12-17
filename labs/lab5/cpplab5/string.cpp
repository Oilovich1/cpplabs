#include <iostream>
#include <string>
#include <cstdlib> // Для rand() и srand()
#include <ctime>   // Для time()
#include <fstream>
#include <sstream>
#include "Source.h"
#include <Windows.h>
#include <locale>


using namespace std;

void setup_console() {
    SetConsoleCP(1251);      
    SetConsoleOutputCP(1251); 
    setlocale(LC_ALL, "Russian");
}

void random_str(string& random_string) {
    srand(static_cast<unsigned int>(time(0)));

    int length;
    cout << "Введите кол-во символов\n";
    cin >> length;
    string russian_alphabet_upper = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ ";
    string english_alphabet_upper = "QWERTYUIOPASDFGHJKLZXCVBNM ";
    int choise;
    cout << "Выберете алфавит: \n 1)русский\n2)английский";
    cin >> choise;
    switch (choise) {
    case 1: {
        for (int i = 0; i < length; ++i) {
            int random_index = rand() % russian_alphabet_upper.length();
            random_string += russian_alphabet_upper[random_index];
        }
        break;
    }
    case 2: {
        for (int i = 0; i < length; ++i) {
            int random_index = rand() % english_alphabet_upper.length();
            random_string += english_alphabet_upper[random_index];
        }
        break;
    }
    default:
        cout << "Неправильный выбор алфавита";
        return;
    }
}
void console_str(string& console_str) {
    cin.ignore();

    cout << "Введите строку: ";
    getline(cin, console_str);
}
void file_str(string& file_str){
    cout << "Введите название файла: ";
    string name;
    cin >> name;
    ifstream file(name);
    while (getline(file, file_str)) {
        cout << file_str << endl;
    }
    file.close();
}

void task1(string stroka) {
    char searsh_a = 'А';
    char reset = ' ';
    stroka += ' ';
    int count_a = 0, count_word = 0;
    for (char c : stroka) {
        if (c == searsh_a)
            count_a++;
        if (c == reset) {
            if (count_a == 3) {
                count_word++;
                count_a = 0;
            }
            else
                count_a = 0;
        }
    }
    cout << count_word;
}

void task2(string stroka) {
    char asi35 = 35, asi33 = 33;
    char probel = ' ';
    for (char &c : stroka) {
        if (c == probel)
            c = asi35;
    }
    stroka += asi33;
    cout << stroka;
}

bool tryParseInt(const std::string& s, long long& out) {
    if (s.empty()) return false;

    std::string trimmed;
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return false;
    size_t end = s.find_last_not_of(" \t\r\n");
    trimmed = s.substr(start, end - start + 1);

    std::istringstream iss(trimmed);
    long long num;
    char leftover;

    if (iss >> num && !(iss >> leftover)) { // успешно прочитано число, и больше ничего нет
        out = num;
        return true;
    }
    return false;
}

void task3(string stroka) {
    long long num;
    tryParseInt(stroka, num);
    if (!tryParseInt(stroka, num)) {
        cout << "В строке не число";
        return;
    }
    bool isNegative = false;
    string digits = stroka;

    if (digits[0] == '-') {
        isNegative = true;
        digits = digits.substr(1);  // Убираем минус
    }
    int count = 0;
    string formated = "";
    for (int i = digits.length()-1; i >= 0; i--) {
        formated = digits[i] + formated;
        count++;
        if (count % 3 == 0 && i != 0) {
            formated = " " + formated;
        }
    }
    if (isNegative) {
        formated = "-" + formated;
    }
    cout << "Триады числа:\n";
    cout << formated;
}

void task4(string stroka) {
    string result2;
    for (size_t i = 0; i < stroka.size(); ++i) {
        bool unique = true;
        for (size_t j = 0; j < stroka.size(); ++j) {
            if (i != j && stroka[i] == stroka[j]) {
                unique = false;
                break;
            }
        }
        if (unique) {
            result2 += stroka[i];
			result2 += ' ';
        }
    }
    cout << "Уникальные строчки: " << result2;
}

void task5(string stroka) {
    if (stroka.empty()) {
        cout << "Ошибка: пустая строка.\n";
        return;
    }

    const string hex_map[16] = {
        "0000","0001","0010","0011",
        "0100","0101","0110","0111",
        "1000","1001","1010","1011",
        "1100","1101","1110","1111"
    };

    string bin;
    for (char c : stroka) {
        if (isspace(static_cast<unsigned char>(c))) continue; 
        int val = -1;
        if (c >= '0' && c <= '9') val = c - '0';
        else {
            char up = static_cast<char>(toupper(static_cast<unsigned char>(c)));
            if (up >= 'A' && up <= 'F') val = 10 + (up - 'A');
        }
        if (val == -1) {
            cout << "Ошибка: недопустимый символ в шестнадцатеричном числе: '" << c << "'\n";
            return;
        }
        bin += hex_map[val];
    }

    // Убрать ведущие нули (оставить хотя бы один символ)
    size_t pos = bin.find_first_not_of('0');
    if (pos == string::npos) {
        cout << "0\n";
    }
    else {
        cout << bin.substr(pos) << "\n";
    }
}

void task6(string stroka) {
    cout << "Выберите уровень сложности пароля:\n";
    cout << "1) Лёгкий  — 8 символов (только строчные буквы)\n";
    cout << "2) Средний — 12 символов (строчные+прописные+цифры)\n";
    cout << "3) Сложный — 16 символов (строчные+прописные+цифры+символы)\n";
    int level;
    if (!(cin >> level)) {
        cout << "Неверный ввод\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    int length = 0;
    string charset;
    const string lowers = "abcdefghijklmnopqrstuvwxyz";
    const string uppers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digits = "0123456789";
    const string symbols = "!@#$%^&*()-_=+[]{};:,.<>?/\\|";

    switch (level) {
    case 1:
        length = 8;
        charset = lowers;
        break;
    case 2:
        length = 12;
        charset = lowers + uppers + digits;
        break;
    case 3:
        length = 16;
        charset = lowers + uppers + digits + symbols;
        break;
    default:
        cout << "Неверный уровень сложности.\n";
        return;
    }

    if (charset.empty()) {
        cout << "Ошибка: пустой набор символов.\n";
        return;
    }

    // Инициализация генератора случайных чисел
    string password;
    password.reserve(length);
    int charsetSize = static_cast<int>(charset.length());
    for (int i = 0; i < length; ++i) {
        int idx = rand() % charsetSize;
        password += charset[idx];
    }

    cout << "Сгенерированный пароль: " << password << "\n";
}

void task7(string stroka) {

}
