package main

import (
	"fmt"
	)

	func main() {
	var matches int
		var commands int

		fmt.Print("Введите количество команд: ")
		fmt.Scan(&commands)

		for commands != 1 {
			if commands % 2 == 0 {
				matches += commands / 2
					commands = commands / 2
			}
			else {
				matches += (commands - 1) / 2 + 1
					commands = (commands - 1) / 2
			}
		}

	fmt.Println("Количество сыгранных матчей:", matches)
}

