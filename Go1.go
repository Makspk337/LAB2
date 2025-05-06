package main
import (
	"bufio"
	"fmt"
	"os"
	"strings"
	)
	func main() {
	fmt.Print("Введите строку: ")
		scanner : = bufio.NewScanner(os.Stdin)
		scanner.Scan()
		s : = scanner.Text()

		count : = 0
		gl : = "AaEeIiOoUuYy"

		for _, i : = range s{
			if i != ' ' {
				if strings.ContainsRune(gl, i) {
					count++
				}
	 else {
	  count--
  }
}
		}
			if count == 0 {
				fmt.Println("Одинаково")
			}
			else if count < 0 {
				fmt.Println("Нет")
			}
			else {
				fmt.Println("Да")
			}
}

