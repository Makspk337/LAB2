s =input("Введите строку: ")
count = 0
gl = "AaEeIiOoUuYy"
for i in s:
    if i != " ":
        if i in gl:
            count+=1
        else:
            count -= 1
if count == 0:
    print("Одинаково")
if count < 0:
    print("Нет")
if count > 0:
    print("Да")

