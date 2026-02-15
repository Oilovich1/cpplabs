#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <climits>
#include "HomeDyn4.h"

void lameKing(const std::string& inputFilename, const std::string& outputFilename) {
    std::ifstream fin(inputFilename);
    std::ofstream fout(outputFilename);

    if (!fin.is_open()) {
        std::cerr << "Error: cannot open input file '" << inputFilename << "'\n";
        return;
    }
    if (!fout.is_open()) {
        std::cerr << "Error: cannot open output file '" << outputFilename << "'\n";
        return;
    }

    int N;
    fin >> N;

    std::vector<std::vector<int>> grid(N, std::vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            fin >> grid[i][j];
        }
    }
    fin.close();

    std::vector<std::vector<long long>> minCost(N, std::vector<long long>(N, LLONG_MAX));

 
    minCost[0][N - 1] = grid[0][N - 1];

    for (int c = N - 2; c >= 0; --c) {
        minCost[0][c] = minCost[0][c + 1] + grid[0][c];
    }
    for (int r = 1; r < N; ++r) {
        minCost[r][N - 1] = minCost[r - 1][N - 1] + grid[r][N - 1];
    }
    for (int r = 1; r < N; ++r) {
        for (int c = N - 2; c >= 0; --c) {
            long long fromTop = minCost[r - 1][c];
            long long fromRight = minCost[r][c + 1];
            if (fromTop != LLONG_MAX && fromRight != LLONG_MAX) {
                minCost[r][c] = grid[r][c] + std::min(fromTop, fromRight);
            }
            else if (fromTop != LLONG_MAX) {
                minCost[r][c] = grid[r][c] + fromTop;
            }
            else if (fromRight != LLONG_MAX) {
                minCost[r][c] = grid[r][c] + fromRight;
            }
        }
    }

    long long resultSum = minCost[N - 1][0];

    std::string path;
    int r = N - 1, c = 0;

    while (r != 0 || c != N - 1) {
        if (r > 0 && minCost[r][c] == minCost[r - 1][c] + grid[r][c]) {
            path += 'D';
            --r;
        }
        else if (c < N - 1 && minCost[r][c] == minCost[r][c + 1] + grid[r][c]) {
            path += 'L';
            ++c;
        }
    }

    std::reverse(path.begin(), path.end());

    fout << resultSum << "\n";
    fout << path << "\n";

    fout.close();
}