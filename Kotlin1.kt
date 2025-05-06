fun main()
        val s = readLine() ? : ""

        var count = 0
        val gl = "AaEeIiOoUuYy"

        for (c in s) {
            if (c != ' ') {
                if (gl.contains(c)) {
                    count++
                }
                else {
                    count--
                }
            }
        }

    when{
        count == 0->println("Одинаково")
        count < 0->println("Нет")
        count > 0->println("Да")
    }
}

