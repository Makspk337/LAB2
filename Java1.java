import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Введите строку: ");
        String s = scanner.nextLine();

        int count = 0;
        String gl = "AaEeIiOoUuYy";

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);

            if (c != ' ') {
                if (gl.indexOf(c) != -1) {
                    count++;
                }
                else {
                    count--;
                }
            }
        }
        if (count == 0) {
            System.out.println("Одинаково");
        }
        else if (count < 0) {
            System.out.println("Нет");
        }
        else {
            System.out.println("Да");
        }

        scanner.close();
    }
}

