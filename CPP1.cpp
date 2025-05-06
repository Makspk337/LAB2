#include <iostream>
#include <string>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    string s;
    cout << "Введите строку: ";
    getline(cin, s);

    int count = 0;
    string gl = "AaEeIiOoUuYy";

    for (char c : s) {
        if (c != ' ') {
            if (gl.find(c) != string::npos) {
                count++;
            }
            else {
                count--;
            }
        }
    }

    if (count == 0) {
        cout << "Одинаково" << endl;
    }
    if (count < 0) {
        cout << "Нет" << endl;
    }
    if (count > 0) {
        cout << "Да" << endl;
    }

    return 0;
}
