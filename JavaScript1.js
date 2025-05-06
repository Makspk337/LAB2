Листинг программы на JavaScript:
function main() {
    let s = prompt("Введите строку: ");
    let count = 0;
    let gl = "AaEeIiOoUuYy";

    for (let i = 0; i < s.length; i++) {
        let c = s[i];

        if (c != = ' ') {
            if (gl.indexOf(c) != = -1) {
                count++;
            }
            else {
                count--;
            }
        }
    }
    if (count == = 0) {
        console.log("Одинаково");
    }
    else if (count < 0) {
        console.log("Нет");
    }
    else {
        console.log("Да");
    }
}

main();

