< ? php

    echo "Введите строку: ";
$s = trim(fgets(STDIN));
$count = 0;
$gl = "AaEeIiOoUuYy";

for ($i = 0; $i < strlen($s); $i++) {
    $char = $s[$i];

    if ($char != " ") {
        if (strpos($gl, $char) != = false) {
            $count++;
        }
        else {
            $count--;
        }
    }
}

if ($count == 0) {
    echo "Одинаково\n";
} elseif($count < 0) {
    echo "Нет\n";
}
else {
    echo "Да\n";
}

? >

