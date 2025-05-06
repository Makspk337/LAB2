package main

import (
	"fmt"
	"math"
	)

	func main() {
	var n, count int
		fmt.Print("Введите количество чисел: ")
		fmt.Scan(&n)

		for i : = 0; i < n; i++ {
			var num int
				fmt.Scan(&num)
				num = int(math.Abs(float64(num)))

				if num < 10 {
					continue
				}

		lastDigit: = num % 10
			num /= 10
			flag : = 1

			for num > 0 {
			digit: = num % 10
				if digit != lastDigit{
					flag = 0
					break
				}
					num /= 10
			}

		if flag == 1 {
			count++
		}
		}

	fmt.Println("Количество чисел с одинаковыми цифрами:", count)
}

