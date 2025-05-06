#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    int matches = 0;
    int commands;

    cout << "Введите количество команд: ";
    cin >> commands;

    while (commands != 1) {
        if (commands % 2 == 0) {
            matches += commands / 2;
            commands = commands / 2;
        }
        else {
            matches += (commands - 1) / 2 + 1;
            commands = (commands - 1) / 2;
        }
    }

    cout << "Количество сыгранных матчей: " << matches << endl;
    return 0;
}
