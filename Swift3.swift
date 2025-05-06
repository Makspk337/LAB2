import Foundation

print("Введите количество чисел: ", terminator: "")
guard let input = readLine(), let n = Int(input) else {
    fatalError("Неверный ввод")
}

var count = 0

for _ in 0.. < n{
    guard let line = readLine(), var num = Int(line) else {
        continue
    }

    num = abs(num)

    if num < 10 {
        continue
    }

    let lastDigit = num % 10
    num /= 10
    var allSame = true

    while num > 0 {
        let digit = num % 10
        if digit != lastDigit {
            allSame = false
            break
        }
        num /= 10
    }

    if allSame {
        count += 1
    }
}

print("Количество чисел с одинаковыми цифрами: \(count)")

