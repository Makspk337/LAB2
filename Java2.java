import java.util.Scanner;

public class TournamentMatches {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int matches = 0;

        System.out.print("Введите количество команд: ");
        int commands = scanner.nextInt();

        while (commands != 1) {
            if (commands % 2 == 0) {
                matches += commands / 2;
                commands = commands / 2;
            }
            else {
                matches += (commands - 1) / 2 + 1;
                commands = (commands - 1) / 2;
            }
        }

        System.out.println("Количество сыгранных матчей: " + matches);
    }
}

