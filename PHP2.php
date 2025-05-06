< ? php

    $matches = 0;

echo "Введите количество команд: ";
$commands = (int)trim(fgets(STDIN));

while ($commands != 1) {
    if ($commands % 2 == 0) {
        $matches += $commands / 2;
        $commands = $commands / 2;
    }
    else {
        $matches += (($commands - 1) / 2) + 1;
        $commands = ($commands - 1) / 2;
    }
}

echo "Количество сыгранных матчей: ".$matches.PHP_EOL;

