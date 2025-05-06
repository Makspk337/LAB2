fun main() {
    var count = 0
        val n = readLine()!!.toInt()

        for (i in 0 until n) {
            var num = readLine()!!.toInt()
                num = Math.abs(num)

                if (num < 10) {
                    continue
                }

            val lastDigit = num % 10
                num /= 10
                var flag = 1

                while (num > 0) {
                    val digit = num % 10
                        if (digit != lastDigit) {
                            flag = 0
                                break
                        }
                    num /= 10
                }

            if (flag == 1) {
                count++
            }
        }

    println("Количество чисел с одинаковыми цифрами: $count")
}

