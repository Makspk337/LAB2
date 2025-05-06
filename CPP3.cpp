#include <iostream>
#include <cmath>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    int n, count = 0;
    cout << "Введите количество чисел: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        num = abs(num);

        if (num < 10) {
            continue;
        }

        int last_digit = num % 10;
        num /= 10;
        int flag = 1;

        while (num > 0) {
            int digit = num % 10;
            if (digit != last_digit) {
                flag = 0;
                break;
            }
            num /= 10;
        }

        if (flag == 1) {
            count++;
        }
    }

    cout << "Количество чисел с одинаковыми цифрами: " << count << endl;
    return 0;
}
