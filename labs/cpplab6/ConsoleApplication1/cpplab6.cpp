#include <iostream>
#include "Header.h"
#include <limits>

using namespace std;

// Прототипы других задач (добавляйте по мере создания)
void runFitnessCenterTask();

// Функция для выбора задачи
void showMenu() {
    cout << "=== Меню выбора задач ===\n";
    cout << "1. Фитнес-центр\n";
    cout << "2. Ученики младшей школы\n";
    cout << "3. Работа с книгами\n";
    cout << "0. Выход\n";
    cout << "Выберите задачу (0-3): ";
}

int main() {
    setup_console();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int choice;
    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            runFitnessCenterTask();
            break;
        case 2:
            runStudentTask();
            break;
        case 3:
            runLibraryTask();
            break;
        case 0:
            cout << "Выход из программы.\n";
            return 0;
        default:
            cout << "Некорректный выбор. Попробуйте снова.\n";
            break;
        }
    }

    return 0;
}