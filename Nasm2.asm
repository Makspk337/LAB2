section .data
    prompt db "Введите количество команд: ", 0    ; Сообщение перед вводом
    result db "Количество сыгранных матчей: ", 0  ; Сообщение перед результатом
    newline db 10, 0                               ; Символ новой строки
    char db 0                                      ; Буфер для вывода одной цифры

section .bss
    matches resd 1         ; Переменная для хранения количества матчей
    commands resd 1        ; Переменная для количества команд
    input resb 10          ; Буфер для ввода строки
    stack_space resb 10    ; Стек для хранения цифр перед выводом

section .text
    global _start

_start:
    ; Печатаем приглашение к вводу
    mov eax, 4              ; sys_write
    mov ebx, 1              ; дескриптор stdout
    mov ecx, prompt         ; адрес сообщения
    mov edx, 50             ; длина строки
    int 0x80                ; вызов ядра

    ; Читаем строку, введённую пользователем
    mov eax, 3              ; sys_read
    mov ebx, 0              ; дескриптор stdin
    mov ecx, input          ; буфер для ввода
    mov edx, 10             ; максимальная длина
    int 0x80                ; вызов ядра

    ; Конвертируем строку в целое число
    xor eax, eax            ; обнуляем регистр EAX
    xor ebx, ebx            ; индекс = 0

.convert_loop:
    mov bl, [input + ebx]   ; загружаем символ
    cmp bl, 10              ; проверяем
    je .converted           ; если да — выход
    cmp bl, 0               ; конец строки?
    je .converted           ; если да — выход
    sub bl, '0'             ; перевод ASCII-цифры в число
    imul eax, eax, 10       ; сдвигаем текущий результат влево
    add eax, ebx            ; добавляем новую цифру
    inc ebx                 ; переходим к следующему символу
    jmp .convert_loop       ; продолжаем цикл

.converted:
    mov [commands], eax     ; сохраняем результат в переменную

    ; Обнуляем счётчик матчей
    xor ebx, ebx
    mov [matches], ebx

.loop:
    ; Загружаем текущее количество команд
    mov eax, [commands]
    cmp eax, 1              ; если осталась 1 команда — конец
    je .done

    test eax, 1             ; проверка на чётность
    jz .even_case           ; если чётное — переход к .even_case

    ; Если нечётное количество команд:
    sub eax, 1              ; уменьшаем на 1
    shr eax, 1              ; делим пополам
    add ebx, eax            ; добавляем к матчам
    add ebx, 1              ; добавляем 1 дополнительный матч (нечётность)
    mov eax, [commands]     ; возвращаем исходное значение
    sub eax, 1              ; уменьшаем на 1
    shr eax, 1              ; делим пополам
    mov [commands], eax     ; сохраняем новое количество команд
    jmp .loop               ; повторяем цикл

.even_case:
    ; Если чётное количество команд:
    shr eax, 1              ; делим на 2
    add ebx, eax            ; прибавляем к матчам
    mov eax, [commands]     ; берём исходное значение
    shr eax, 1              ; делим пополам
    mov [commands], eax     ; сохраняем
    jmp .loop               ; повторяем цикл

.done:
    ; Сохраняем финальное количество матчей
    mov [matches], ebx

    ; Печатаем текст результата
    mov eax, 4              ; sys_write
    mov ebx, 1              ; stdout
    mov ecx, result         ; сообщение
    mov edx, 54             ; длина строки
    int 0x80

    ; Выводим значение переменной matches
    mov eax, [matches]      ; загружаем значение
    mov edi, stack_space    ; адрес буфера для "стека"
    call print_int          ; вызываем функцию вывода числа

    ; Печатаем символ новой строки
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80

    ; Выход из программы
    mov eax, 1              ; sys_exit
    xor ebx, ebx            ; код возврата 0
    int 0x80

; Выводит целое число в EAX на экран
print_int:
    mov ecx, 10             ; делитель (для деления на 10)
    xor edx, edx            ; остаток = 0
    mov ebx, eax            ; сохраняем оригинальное число
    mov esi, edi            ; сохраняем начало буфера

.reverse_loop:
    xor edx, edx            ; обнуляем EDX перед DIV
    div ecx                 ; делим EAX на 10
    add dl, '0'             ; переводим остаток в ASCII
    dec edi                 ; перемещаемся назад по буферу
    mov [edi], dl           ; сохраняем символ
    test eax, eax           ; проверяем, закончили ли
    jnz .reverse_loop       ; если нет — продолжаем

.print_loop:
    mov eax, 4              ; sys_write
    mov ebx, 1              ; stdout
    mov ecx, edi            ; адрес текущего символа
    mov edx, 1              ; длина = 1 символ
    int 0x80
    inc edi                 ; переходим к следующему символу
    cmp edi, esi            ; достигли конца буфера?
    jne .print_loop         ; если нет — продолжаем

    ret                     ; возврат из функции

