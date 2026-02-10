#include <iostream>
#include <string>
#include <cstdlib> 
#include <ctime> 
#include <fstream>
#include <sstream>
#include "Source.h"
#include <Windows.h>
#include <locale>
#include <vector>
#include <cctype>


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
    if (!tryParseInt(stroka, num)) {
        cout << "В строке не число";
        return;
    }
    bool isNegative = false;
    string digits = stroka;

    if (digits[0] == '-') {
        isNegative = true;
        digits = digits.substr(1);
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

void task6() {
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

bool parseNumber(const std::string& s, int& num, std::string& rest) {
    if (s.empty()) return false;
    size_t i = 0;
    // Пропускаем начальные пробелы
    while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i]))) ++i;
    if (i == s.size()) return false;

    // Число должно начинаться с цифры (натуральное → без +/-)
    if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;

    size_t start = i;
    while (i < s.size() && std::isdigit(static_cast<unsigned char>(s[i]))) ++i;

    std::string numStr = s.substr(start, i - start);
    // Ограничение: не более 3 цифр
    if (numStr.size() > 3) return false;

    try {
        num = std::stoi(numStr);
        if (num < 1 || num > 999) return false; // натуральные ≤ 999
    }
    catch (...) {
        return false;
    }

    // Остаток строки (после числа)
    rest = s.substr(i);
    return true;
}

void task7() {
    std::string FN1, FN2;
    std::cout << "Введите имя входного файла (FN1): ";
    std::cin >> FN1;
    std::cout << "Введите имя выходного файла (FN2): ";
    std::cin >> FN2;

    std::ifstream in(FN1);
    std::ofstream out(FN2);

    if (!in.is_open()) {
        std::cerr << "Ошибка: не удалось открыть входной файл \"" << FN1 << "\"\n";
        return;
    }
    if (!out.is_open()) {
        std::cerr << "Ошибка: не удалось создать выходной файл \"" << FN2 << "\"\n";
        in.close();
        return;
    }

    std::string line;
    int lineNum = 0;

    while (std::getline(in, line)) {
        ++lineNum;
        std::string origLine = line; // для вывода

        // Удалим комментарии и лишнее (оставим только [0-9:*=\s])
        std::string clean;
        for (char c : line) {
            if (std::isdigit(c) || c == '*' || c == ':' || c == '=' || std::isspace(static_cast<unsigned char>(c))) {
                clean += c;
            }
        }
        if (clean.empty()) {
            out << line << "\n"; // пустая/комментарий — копируем как есть
            continue;
        }

        // ---------- Парсинг: A op B = ans ----------
        int A = 0, B = 0, ans = 0;
        char op = 0;
        std::string rest;

        // 1. Число A
        if (!parseNumber(clean, A, rest)) {
            out << line << " !\n"; // некорректный формат → считаем ошибкой
            continue;
        }

        // 2. Операция (* или :)
        while (!rest.empty() && std::isspace(static_cast<unsigned char>(rest[0]))) rest.erase(0, 1);
        if (rest.empty() || (rest[0] != '*' && rest[0] != ':')) {
            out << line << " !\n";
            continue;
        }
        op = rest[0];
        rest = rest.substr(1);

        // 3. Число B
        if (!parseNumber(rest, B, rest)) {
            out << line << " !\n";
            continue;
        }

        // 4. Знак '='
        while (!rest.empty() && std::isspace(static_cast<unsigned char>(rest[0]))) rest.erase(0, 1);
        if (rest.empty() || rest[0] != '=') {
            out << line << " !\n";
            continue;
        }
        rest = rest.substr(1);

        // 5. Ответ (ans)
        if (!parseNumber(rest, ans, rest)) {
            out << line << " !\n";
            continue;
        }

        // Проверим, что после ответа — только пробелы/конец
        while (!rest.empty() && std::isspace(static_cast<unsigned char>(rest[0]))) rest.erase(0, 1);
        if (!rest.empty()) {
            out << line << " !\n"; // мусор в конце
            continue;
        }

        // ---------- Проверка вычисления ----------
        bool correct = false;

        if (op == '*') {
            long long expected = 1LL * A * B;
            if (expected <= 999999 && expected == ans) { // 999*999 = 998001 — влезает в int, но для надёжности long long
                correct = true;
            }
        }
        else if (op == ':') {
            if (B == 0) {
                correct = false; // хотя по условию B ≥ 1, но на всякий
            }
            else if (A % B == 0) {
                int expected = A / B;
                if (expected == ans) {
                    correct = true;
                }
            }
            // если A % B != 0 - деление с остатком - в 3 классе — неверно
        }

        // ---------- Запись в выходной файл ----------
        out << line;
        if (!correct) {
            out << " !";
        }
        out << "\n";
    }

    in.close();
    out.close();
    std::cout << "Проверка завершена. Результат записан в \"" << FN2 << "\".\n";
}
