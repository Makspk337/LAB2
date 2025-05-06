count = 0
n = gets.to_i

n.times do
num = gets.to_i
num = num.abs  # Работаем с модулем числа

if num < 10
    next  # Пропускаем однозначные числа
    end

    last_digit = num % 10
    num /= 10
    flag = 1  # Предполагаем, что все цифры одинаковые

    while num > 0
        digit = num % 10
        if digit != last_digit
            flag = 0  # Найдена отличающаяся цифра
            break
            end
            num /= 10
            end

            if flag == 1
                count += 1
                end
                end

                puts "Количество чисел с одинаковыми цифрами: #{count}"

