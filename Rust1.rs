use std::io;

fn main() {
    println!("Введите строку: ");
    let mut s = String::new();
    io::stdin().read_line(&mut s).expect("Не удалось прочитать строку");
    let s = s.trim();

    let mut count = 0;
    let gl = "AaEeIiOoUuYy";

    for c in s.chars() {
        if c != ' ' {
            if gl.contains(c) {
                count += 1;
            }
            else {
                count -= 1;
            }
        }
    }

    if count == 0 {
        println!("Одинаково");
    }
    else if count < 0 {
        println!("Нет");
    }
    else {
        println!("Да");
    }
}

