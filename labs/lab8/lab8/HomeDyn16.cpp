#include <iostream>
#include "HomeDyn16.h"

void Kichnie() {
	int k, n; 
	long long nullz, _nullz, onez, _onez, twoz, _twoz, threez, _threez, morez, _morez;
	do {
		std::cout << "Введите основание k (2<=k<=10)\n";
		do {
			std::cin >> k;
		} while (k < 2 || k>10);
		do {
			std::cout << "Введите кол-во рарядов n (1<n<20, n+k<26)\n";
			std::cin >> n;
		} while (n <= 1 || n >= 20);
		if (n + k > 26) {
			std::cout << "Введено неверное значение основаия и разрядов! Попробуйте занаво\n";
		}
	} while (n + k > 26);
	nullz = k - 1;
	onez = 1;
	twoz = 0; threez = 0; morez = 0;
	for (int i = 2; i <= n; i++) {
		_nullz = nullz;
		_onez = onez;
		_twoz = twoz;
		_threez = threez;
		_morez = morez;
		nullz = _nullz * (k - 1) + _onez * (k - 1) + _twoz * (k - 1) + _threez * (k - 1);
		onez = _nullz;
		twoz = _onez;
		threez = _twoz;
		morez = _morez * k + _threez;
	}
	std::cout << "кол-во чисел, в которых более 3 подряд нулей = " << morez << std::endl;
}