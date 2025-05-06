import Foundation

var matches = 0

print("Введите количество команд: ", terminator: "")
if let input = readLine(), let commands = Int(input) {
    var commands = commands

        while commands != 1 {
            if commands % 2 == 0 {
                matches += commands / 2
                    commands = commands / 2
            }
            else {
                matches += (commands - 1) / 2 + 1
                    commands = (commands - 1) / 2
            }
        }

    print("Количество сыгранных матчей: \(matches)")
}
else {
    print("Ошибка: Введите корректное число")
}

