matches = 0
commands = int(input("Введите количество команд: "))

while commands != 1:
    if commands % 2 == 0:
        matches += commands // 2
        commands = commands // 2
    else:
        matches += (commands - 1) // 2 + 1
        commands = (commands - 1) // 2

print("Количество сыгранных матчей:" , matches)

