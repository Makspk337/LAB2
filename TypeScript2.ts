function main() {
    let matches = 0;

    const commands : number = parseInt(prompt("Введите количество команд:") || "0");

    let currentCommands = commands;

    while (currentCommands != = 1) {
        if (currentCommands % 2 == = 0) {
            matches += currentCommands / 2;
            currentCommands = currentCommands / 2;
        }
        else {
            matches += Math.floor((currentCommands - 1) / 2) + 1;
            currentCommands = Math.floor((currentCommands - 1) / 2);
        }
    }

    console.log("Количество сыгранных матчей: " + matches);
}

main();

