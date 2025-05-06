import Foundation

print("Введите строку: ", terminator: "")
if let s = readLine() {
    var count = 0
        let gl = "AaEeIiOoUuYy"

        for char in s{
            if char != " " {
                if gl.contains(char) {
                    count += 1
                }
     else {
      count -= 1
  }
}
        }

            if count == 0 {
                print("Одинаково")
            }
            else if count < 0 {
                print("Нет")
            }
            else {
                print("Да")
            }
}

