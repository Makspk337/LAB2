function isAllDigitsSame(num: number) : boolean{
    num = Math.abs(num);

    if (num < 10) {
        return false;
    }

    const lastDigit = num % 10;
    num = Math.floor(num / 10);

    while (num > 0) {
        const digit = num % 10;
        if (digit != = lastDigit) {
            return false;
        }
        num = Math.floor(num / 10);
    }

    return true;
}

function main() : void {
    const n = Number(prompt("Введите количество чисел: "));
    let count = 0;

    for (let i = 0; i < n; i++) {
        const input = prompt();
        const num = Number(input);

        if (isAllDigitsSame(num)) {
            count++;
        }
    }

    alert("Количество чисел с одинаковыми цифрами: " + count);
}
