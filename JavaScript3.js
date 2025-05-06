function main() {
    let count = 0;
    let n = parseInt(prompt("Введите количество чисел: "));

    for (let i = 0; i < n; i++) {
        let num = parseInt(prompt());
        num = Math.abs(num);

        if (num < 10) {
            continue;
        }

        let lastDigit = num % 10;
        num = Math.floor(num / 10);
        let flag = 1;

        while (num > 0) {
            let digit = num % 10;
            if (digit != = lastDigit) {
                flag = 0;
                break;
            }
            num = Math.floor(num / 10);
        }

        if (flag == = 1) {
            count++;
        }
    }

    console.log("Количество чисел с одинаковыми цифрами:", count);
}

main();

