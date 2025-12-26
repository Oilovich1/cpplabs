#include "Header.h"
#include <iostream>

using namespace std;

int main() {
	setup_console();
	cout << "Меню: \n";
	cout << "1) Соритровка по убыванию пузырьком\n";
	cout << "2) Сортировка данных о клиентах фитнес-центра\n";
	cout << "3) Сортировка данных учеников по ЕГЭ\n";
	cout << "0) Выход\n";
	int choise;
	while (true) {
		cout << "Введите номер задания: ";
		cin >> choise;
		switch (choise) {
		case 1: {
			task1();
			break;
		}
		case 2: {
			task2();
			break;
		}
		case 3: {
			task3();
			break;
		}
		case 0:{
			cout << "До свидания!";
			return 0;
		}
		default: {
			cout << "Неверный выбор задания! Попробуйте ещё раз\n";
			break;
		}
		}
	}
}