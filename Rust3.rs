use std::io;

fn main() {
    let mut input = String::new();
    println!("Введите количество чисел: ");
    io::stdin().read_line(&mut input).unwrap();
    let n : i32 = input.trim().parse().unwrap();

    let mut count = 0;

    for _ in 0..n{
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let mut num : i32 = input.trim().parse().unwrap();
        num = num.abs();

        if num < 10 {
            continue;
        }

        let last_digit = num % 10;
        num /= 10;
        let mut same = true;

        while num > 0 {
            let digit = num % 10;
            if digit != last_digit {
                same = false;
                break;
            }
            num /= 10;
        }

        if same {
            count += 1;
        }
    }

    println!("Количество чисел с одинаковыми цифрами: {}", count);
}

