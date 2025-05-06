function main() {
    const s = prompt("Введите строку: ") || "";

    let count = 0;
    const gl = "AaEeIiOoUuYy";

    for (let i = 0; i < s.length; i++) {
        const char = s[i];

        if (char != = " ") {
            if (gl.includes(char)) {
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

