#include <iostream>
#include <locale>
#include <string>
#include "backrec10.h"

int main() {
	setlocale(LC_ALL, "rus");
	while (true) {
		std::cout << "Задачи \n1) Артефакты \n2) Хромой король \n3) К-ичные числа\n";
		std::cout << "Введите номер задачи: ";
		int choise;
		std::cin >> choise;
		switch (choise) {
		case 1: {
			std::cout << "Введите файл с весами и налогами: ";
			std::string filename;
			std::cin >> filename;
			BackRec10(filename);
		}
		case 2: {

		}
		}
	}
	return 0;
}