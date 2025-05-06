n = int(input("Введите количество чисел: "))
count = 0
for i in range(n):
    num = int(input())
    num = abs(num)
    if num < 10:
        continue
    last = num % 10
    num = num // 10
    flag = 1
    while num > 0:
        if num % 10 != last:
            flag = 0
            break
        num = num // 10
    if flag == 1:
        count +=1
print("Количество чисел с одинаковыми цифрами:" , count)

