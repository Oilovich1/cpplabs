#include <iostream>
#include <locale>
#include <string>
#include "Source.h"

using namespace std;

int main() {
	setup_console();
	cout << "Выберете способ ввода:\n1) рандом\n2) ручной ввод\n3) из файла\n0) выход\n";
	int n;
	cin >> n;
	string stroka;
	switch (n) {
	case (1): {
		random_str(stroka);
		cout << stroka << endl;
		break;
	}
	case 2: {
		console_str(stroka);
		break;
	}
	case 3: {
		file_str(stroka);
		cout << endl;
		break;
	}
	default: {
		cout << "Неправильный способ ввода";
		break;
	}
	}
	if (n != 1 && n != 2 && n != 3)
		return 1;
	cout << "Введите номер задания:\n 1) AAA\n 2) ASCII\n 3) триады\n 4) уникальные строчки\n 5) Из 16-ричной в 2-ичную\n 6) генерация пароля\n";
	int task;
	cin >> task;
	switch (task) {
	case 1: {
		task1(stroka);
		break;
	}
	case 2: {
		task2(stroka);
		break;
	}
	case 3: {
		task3(stroka);
		break;
	}
	case 4: {
		task4(stroka);
		break;
	}
	case 5: {
		task5(stroka);
		break;
	}
	case 6: {
		task6(stroka);
		break;
	}

	}
	return 0;
}