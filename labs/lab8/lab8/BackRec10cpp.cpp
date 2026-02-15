#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <algorithm>
#include <string>
#include "backrec10.h"
void BackRec10(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }

    int N, Z;
    fin >> N >> Z;

    std::vector<int> c(N);
    std::vector<int> d(N);

    for (int i = 0; i < N; ++i) {
        fin >> c[i];
    }
    for (int i = 0; i < N; ++i) {
        fin >> d[i];
    }
    fin.close();

    int totalWeight = 0;
    for (int x : c) totalWeight += x;

    const int INF = 1e9;
    std::vector<int> dp(totalWeight + 1, INF);
    std::vector<std::vector<int>> choice(totalWeight + 1);

    dp[0] = 0;

    for (int i = 0; i < N; ++i) {
        std::vector<int> newDp = dp;
        std::vector<std::vector<int>> newChoice = choice;

        for (int w = totalWeight; w >= c[i]; --w) {
            if (dp[w - c[i]] != INF && dp[w - c[i]] + d[i] < newDp[w]) {
                newDp[w] = dp[w - c[i]] + d[i];
                newChoice[w] = choice[w - c[i]];
                newChoice[w].push_back(i);
            }
        }

        dp = newDp;
        choice = newChoice;
    }

    int bestW = -1;
    int minTax = INF;

    for (int w = Z + 1; w <= totalWeight; ++w) {
        if (dp[w] < minTax) {
            minTax = dp[w];
            bestW = w;
        }
    }

    if (bestW == -1) {
        std::cout << "Нет решения\n";
        return;
    }

    std::cout << "Веса артефактов: ";
    for (int idx : choice[bestW]) {
        std::cout << idx + 1 << " "; // Нумерация с 1
    }
    std::cout << "\nОбщий вес: " << bestW << "\n";
    std::cout << "Общий налог: " << minTax << "\n";
}