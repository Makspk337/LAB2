fun main() {

        var commands = readLine() ? .toIntOrNull() ? : return
        var matches = 0

        while (commands != 1) {
            if (commands % 2 == 0) {
                matches += commands / 2
                    commands /= 2
            }
            else {
                matches += (commands - 1) / 2 + 1
                    commands = (commands - 1) / 2
            }
        }

    println("Количество сыгранных матчей: $matches")
}

