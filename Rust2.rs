use std::io;

fn main() {
    let mut matches = 0;

    println!("Введите количество команд: ");

    let mut commands_str = String::new();
    io::stdin().read_line(&mut commands_str).expect("Не удалось прочитать строку");

    let mut commands : i32 = commands_str.trim().parse().expect("Пожалуйста, введите число");

    while commands != 1 {
        if commands % 2 == 0 {
            matches += commands / 2;
            commands /= 2;
        }
        else {
            matches += (commands - 1) / 2 + 1;
            commands = (commands - 1) / 2;
        }
    }

    println!("Количество сыгранных матчей: {}", matches);
}

