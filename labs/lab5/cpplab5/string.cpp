#include <iostream>
#include <string>
#include <cstdlib> // ƒл€ rand() и srand()
#include <ctime>   // ƒл€ time()
#include <fstream>
#include <sstream>
#include "Source.h"

using namespace std;

void random_str(string& random_string) {
    srand(static_cast<unsigned int>(time(0)));

    int length;
    cout << "¬ведите кол-во символов\n";
    cin >> length;
    string russian_alphabet_upper = "јЅ¬√ƒ≈®∆«»… ЋћЌќѕ–—“”‘’÷„ЎўЏџ№Ёёя ";

    for (int i = 0; i < length; ++i) {
        int random_index = rand() % russian_alphabet_upper.length();
        random_string += russian_alphabet_upper[random_index];
    }
}
void console_str(string& console_str){
    cout << "¬ведите строку: ";
    cin >> console_str;
}
void file_str(string& file_str)
{
    cout << "¬ведите название файла: ";
    string name;
    cin >> name;
    ifstream file(name);
    while (getline(file, file_str)) {
        cout << file_str << endl;
    }
    file.close();
}

void task1(string stroka) {
    char searsh_a = 'ј';
    char reset = ' ';
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
    cout << asi35 << endl;
    for (char &c : stroka) {
        if (c == probel)
            c = asi35;
    }
    stroka += asi33;
    cout << stroka;
}

void task3(string stroka) {
    int num;
    while (true) {
        istringstream iss(stroka);
        if (iss >> num && iss.eof()) {
            break;
        }
        cout << "ќшибка: введено не целое число. ѕопробуйте снова.\n";
        cout << "¬ведите целое число: ";
        getline(cin, stroka);
    }
    bool isNegative = false;
    string digits = stroka;

    if (digits[0] == '-') {
        isNegative = true;
        digits = digits.substr(1);  // ”бираем минус
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
    cout << "“риады числа:\n";
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
    cout << "”никальные строчки: " << result2;
}

void task5(string stroka) {
    if (stroka.empty()) {
        cout << "ќшибка: пуста€ строка.\n";
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
        if (isspace(static_cast<unsigned char>(c))) continue; // пропускаем пробелы внутри строки
        int val = -1;
        if (c >= '0' && c <= '9') val = c - '0';
        else {
            char up = static_cast<char>(toupper(static_cast<unsigned char>(c)));
            if (up >= 'A' && up <= 'F') val = 10 + (up - 'A');
        }
        if (val == -1) {
            cout << "ќшибка: недопустимый символ в шестнадцатеричном числе: '" << c << "'\n";
            return;
        }
        bin += hex_map[val];
    }

    // ”брать ведущие нули (оставить хот€ бы один символ)
    size_t pos = bin.find_first_not_of('0');
    if (pos == string::npos) {
        cout << "0\n";
    }
    else {
        cout << bin.substr(pos) << "\n";
    }
}
