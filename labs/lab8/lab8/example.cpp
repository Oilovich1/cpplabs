#include <iostream>
#include <locale>
#include <string>
#include "backrec10.h"
#include "HomeDyn4.h"
#include "HomeDyn16.h"

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
			std::cout << "Ввдите ввходной и название выходного файлов\n";
			std::string infile, outfile;
			std::cin >> infile >> outfile;
			lameKing(infile, outfile);
			std::cout << "Решение записано в файл " << outfile << std::endl;
		}
		case 3: {
			Kichnie();
			std::cout << std::endl;
		}
		default: {
		std::cout << "Введен неверный номер задачи\n";
		}
		}
	}
	return 0;
}